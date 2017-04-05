#ifndef __INX_H_30226458_B33F_4EAB_AA69_867FDF01AB60__
#define __INX_H_30226458_B33F_4EAB_AA69_867FDF01AB60__

#ifdef linux
# include <netinet/in.h>
#else
/*************************************************************************************************************
 * for windows platform, network header file "winsock2.h" MUST be place ahead of "windows.h"
 * so if you encount some compile error, you could try place #include "Winsock2.h" in first line of error file.
 *************************************************************************************************************/
# include "ws2ipdef.h"
# include "Inaddr.h"
# include "In6addr.h"
#endif

#include <string.h>

union inx_addr
{
	struct in_addr ip4;
	struct in6_addr ip6;
	char bytes[20];

#define s_4or6 bytes[sizeof(struct in6_addr)+1] /*6: ipv6, other:ipv4 */
};

/* 0: equal */
inline int inx_addr_cmp(union inx_addr *addr1, union inx_addr *addr2)
{
	if (addr1->s_4or6!=6 && addr2->s_4or6!=6)
		return memcmp(addr1, addr2, sizeof(struct in_addr));

	if (addr2->s_4or6 != addr2->s_4or6)
		return 1;

	return memcmp(addr1, addr2, sizeof(struct in6_addr));
}

inline void sockaddr_storage_set(struct sockaddr_storage *sa, unsigned short port, union inx_addr *inx)
{
	if(inx->s_4or6 == 6) {
		sa->ss_family = AF_INET6;
		struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
		sa6->sin6_addr = inx->ip6;
		sa6->sin6_port = port;
	}
	else{
		sa->ss_family = AF_INET;
		struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
		sa4->sin_addr = inx->ip4;
		sa4->sin_port = port;
	}
}

inline unsigned short sockaddr_storage_get(struct sockaddr_storage *sa, union inx_addr *inx)
{
	if (sa->ss_family == AF_INET6) {
		struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
		inx->ip6 = sa6->sin6_addr;
		return sa6->sin6_port;
	}
	else {
		struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
		inx->ip4 = sa4->sin_addr;
		return sa4->sin_port;
	}
}

#endif /*__INX_H_30226458_B33F_4EAB_AA69_867FDF01AB60__*/
