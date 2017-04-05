#ifndef __LOG_H_D1FCA3BE_1B53_4F01_ADA5_1BA0B8CD6D63__
#define __LOG_H_D1FCA3BE_1B53_4F01_ADA5_1BA0B8CD6D63__

#define LOG_LEVEL_DEBUG      (0)
#define LOG_LEVEL_INFO       (1)
#define LOG_LEVEL_WARNING    (2)
#define LOG_LEVEL_ERROR      (3)

#ifdef SKIP_LOGGING
# define Log_error(s, ...)
# define Log_warning(s, ...)
# define Log_info(s, ...)
#else
# define Log_error(s, ...)   FFL_LOG((__FILE__), (__FUNCTION__), (__LINE__), LOG_LEVEL_INFO,    s, ##__VA_ARGS__ )
# define Log_warning(s, ...) FFL_LOG((__FILE__), (__FUNCTION__), (__LINE__), LOG_LEVEL_WARNING, s, ##__VA_ARGS__ )
# define Log_info(s, ...)    FFL_LOG((__FILE__), (__FUNCTION__), (__LINE__), LOG_LEVEL_ERROR,   s, ##__VA_ARGS__ )
void FFL_LOG(const char *filename, const char *function, long line, int level, const char *fmt, ...);
#endif

int ffl_log_init(int write_to_stdio);
void ffl_log_uninit(void);

typedef void (*log_handler_t)(struct timeval *now, int level, const char *buf, int len);
/* register or unregister handler must after ffl_log_init() and before ffl_log_uninit() */
int register_log_handler(log_handler_t handler);
int unregister_log_handler(log_handler_t handler);


#endif /*__LOG_H_D1FCA3BE_1B53_4F01_ADA5_1BA0B8CD6D63__*/
