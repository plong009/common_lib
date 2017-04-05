#ifndef __PLATFORM_H_69910456_5F35_4555_8CDA_D2638751918C__
#define __PLATFORM_H_69910456_5F35_4555_8CDA_D2638751918C__


#ifdef linux
	#include <unistd.h>
	#include <semaphore.h>
	#include <sys/time.h>
	#include <sys/eventfd.h> /* EFD_NONBLOCK available from 2.6.27*/
	#include <pthread.h>
	#include <poll.h>
	#include <cpuid.h>
	#define MFENCE                     __sync_synchronize()
	#define compiler_mb()              __asm__ __volatile__ ("" : : : "memory")
	#define CAS(ptr, old, value)       __sync_bool_compare_and_swap(ptr, old, value)
	#define CAS32(ptr, old, value)     __sync_bool_compare_and_swap(ptr, old, value)
	#define atomic_inc(data)		   __sync_add_and_fetch(&(data), 1)
	#define atomic_dec(data)		   __sync_sub_and_fetch(&(data), 1)
	#define __cpuid(a,l)			   __cpuid(l, &a[0], &a[1], &a[2], &a[3])
	#define SOCKET                     int
	#define closesocket(s)             close(s)
	#define TRANSLATE_PTHREAD_ROUTINE(c)

	#define fd_t                       int
	int eventfd_poll(int fd, int milliseconds) {struct pollfd p={fd, POLLIN, 0}; return poll(&p, 1, milliseconds);} 

	/* do not using gettimeofday() to implement get_microsecond(), it is affected by discontinuous jumps in the system time*/
	inline unsigned long long get_millisecond(void) {struct timespec now; clock_gettime(CLOCK_MONOTONIC, &now); return (1000LL*now.tv_sec + (now.tv_nsec/1000000)); }
	inline unsigned long long get_microsecond(void) {struct timespec now; clock_gettime(CLOCK_MONOTONIC, &now); return (1000LL*1000*now.tv_sec + (now.tv_nsec/1000)); }


#elif defined IOS
	#include <libkern/OSAtomic.h>
	#define MFENCE                     OSMemoryBarrier()
	#define CAS(ptr, old, value)       OSCompareAndSwapPtr(old, value, ptr)
	#define CAS32(ptr, old, value)     OSCompareAndSwap(old, value, ptr)
	#define atomic_inc(data)           OSAtomicIncrement32(&(data))
	#define atomic_dec(data)		   OSAtomicDecrement32(&(data))

	#define eventfd(a,b)               NSPipe

	inline unsigned long long get_millisecond(void) {struct timespec now; clock_gettime(CLOCK_MONOTONIC, &now); return (1000LL*now.tv_sec + (now.tv_nsec/1000000)); }
	inline unsigned long long get_microsecond(void) {struct timespec now; clock_gettime(CLOCK_MONOTONIC, &now); return (1000LL*1000*now.tv_sec + (now.tv_nsec/1000)); }

#elif defined DDK
	/*????*/
	#define MFENCE                              KeMemoryBarrier()
	#define atomic_inc(data)                    InterlockedIncrement(&(data))
	#define sem_t                               PRKSEMAPHORE
	#define sem_init(h, b, c)                   ( (((*h)=KeInitializeSemaphore(NULL, c, FD_SETSIZE, NULL))!=NULL )?0:-1)
	#define sem_post(h)                         KeReleaseSemaphore((*h), 1, NULL)
	#define sem_wait(h)                         KeWaitForSingleObject((*h), INFINITE)
	#define sem_trywait(h)                      ((KeWaitForSingleObject((*h),0)==WAIT_OBJECT_0)?0:-1)
	#define pthread_create(a, b, proc, d)       ((*a)=PsCreateSystemThread(NULL, 0, __##proc, d, 0, 0))
	inline BOOL CAS(void* ptr, void* old, void* value)
	{
		if (sizeof(void*) == 8)
			return InterlockedCompareExchange64((LONG64*)ptr, (LONG64)value, (LONG64)old) == (LONG64)old;
	
		#pragma warning( disable : 4302 4311)
		return InterlockedCompareExchange((LONG*)ptr, (LONG)value, (LONG)old) == (LONG)old;
	}
	inline BOOL CAS32(void* ptr, unsigned int old, unsigned int value)
	{
		return InterlockedCompareExchange((LONG*)ptr, (LONG)value, (LONG)old) == (LONG)old;
	}

#else
	#pragma  comment(lib, "ws2_32.lib")
	#include <winsock2.h>  /* winsock2.h must be included before windows.h, otherwise there's redefine warning */
	#include <windows.h>
	#include <intrin.h>
	#include <time.h>
	#define MFENCE                                MemoryBarrier()
	#define compiler_mb()                         _ReadWriteBarrier()
	#define atomic_inc(data)                      InterlockedIncrement(&(data))
	#define atomic_dec(data)					  InterlockedDecrement(&(data))
	#define sem_t                                 HANDLE
	#define sem_init(h, b, c)                    ( (((*h)=CreateSemaphore(NULL, c, FD_SETSIZE, NULL))!=NULL )?0:-1)
	#define sem_post(h)                           ReleaseSemaphore((*h), 1, NULL)
	#define sem_wait(h)                           WaitForSingleObject((*h), INFINITE)
	#define sem_trywait(h)                       ((WaitForSingleObject((*h),0)==WAIT_OBJECT_0)?0:-1)
	#define sem_destroy(h)                        CloseHandle((*h))

	#define fd_t                                  HANDLE
	#define EFD_NONBLOCK                          00004000
	inline fd_t eventfd(unsigned int a,int b)  {HANDLE h=CreateEvent(NULL,TRUE,FALSE,NULL); if(h==NULL) return (HANDLE)-1; return h;}
	#define eventfd_read(h, b, c)				  ResetEvent(h)
	#define eventfd_write(h, b, c)				  SetEvent(h)
	#define eventfd_poll(h,t)					  WaitForSingleObject(h, t)

	#define pthread_t                             HANDLE
	#define pthread_join(a, b)                    WaitForSingleObject(a, INFINITE)
	#define pthread_create(a, b, proc, d)         ((((*a)=CreateThread(NULL, 0, __##proc, d, 0, 0))!=NULL)?0:1)
	#define TRANSLATE_PTHREAD_ROUTINE(proc)       static void* proc(void*); DWORD WINAPI __##proc(PVOID param){return NULL==proc(param);} 

	#define close(h)                              CloseHandle(h)
	#define select(a, b, c, d, e)                 select(0, b, c, d, e)
	#define sleep(a)                              Sleep((a)*1000)
	#define usleep(a)                             Sleep((a+999)/1000)
	#define getpid()                              GetCurrentProcessId()
	#define localtime_r(a, b)                     localtime_s(b, a)
	#define strncpy(d,s,n)                        strncpy_s(d,n,s,strlen(s))


	/*#pragma comment( lib, "Winmm.lib" ) */
	/*#define get_millisecond() timeGetTime()*/ /* system time and wrap around after about 50 days */
	/* there shall be 64bits overflow in serveral months if directly call (c.QuadPart*1000000/ f.QuadPart) */
	inline unsigned long long get_millisecond() {LARGE_INTEGER f, c; QueryPerformanceFrequency(&f); QueryPerformanceCounter(&c); return (c.QuadPart*1000)/f.QuadPart;}
	inline unsigned long long get_microsecond() {long long s; LARGE_INTEGER f, c; QueryPerformanceFrequency(&f); QueryPerformanceCounter(&c); s=c.QuadPart/f.QuadPart; return ((c.QuadPart-s*f.QuadPart)*1000000/ f.QuadPart)+s*1000000;}

	inline int gettimeofday(struct timeval * tp, struct timezone * tzp)
	{
		FILETIME    file_time;
		SYSTEMTIME  system_time;
		ULARGE_INTEGER ularge;

		GetSystemTime(&system_time);
		SystemTimeToFileTime(&system_time, &file_time);
		ularge.LowPart = file_time.dwLowDateTime;
		ularge.HighPart = file_time.dwHighDateTime;

		tp->tv_sec = (long) ((ularge.QuadPart - 116444736000000000LL) / 10000000L);
		tp->tv_usec = (long) (system_time.wMilliseconds * 1000);

		return 0;
	}

	inline BOOL CAS(void* ptr, void* old, void* value)
	{
		if (sizeof(void*) == 8)
			return InterlockedCompareExchange64((LONG64*)ptr, (LONG64)value, (LONG64)old) == (LONG64)old;

		#pragma warning( disable : 4302 4311)
		return InterlockedCompareExchange((LONG*)ptr, (LONG)value, (LONG)old) == (LONG)old;
	}
	inline BOOL CAS32(void* ptr, unsigned int old, unsigned int value)
	{
		return InterlockedCompareExchange((LONG*)ptr, (LONG)value, (LONG)old) == (LONG)old;
	}
	/* #define CAS(ptr, old, value)  (InterlockedCompareExchange(ptr, value, old) == old)  ,this macro make mistake when old is not a varable but an expression which maybe modified after CAS OK */

#endif


#endif /*__PLATFORM_H_69910456_5F35_4555_8CDA_D2638751918C__*/
