#include "apue.h"
#include <errno.h>      /* 错误码定义 */
#include <stdarg.h>     /* 可变参数支持 */
#include <syslog.h>     /* 系统日志支持 */

static void err_doit(int, int, const char *, va_list);

/* 非致命错误：打印错误信息（不含错误码） */
void err_msg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

/* 致命错误：打印错误信息后退出（不含错误码） */
void err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/* 非致命错误：打印错误信息 + 系统错误码（如 "xxx: No such file or directory"） */
void err_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, 0, fmt, ap);
    va_end(ap);
}

/* 致命错误：打印错误信息 + 系统错误码后退出 */
void err_sys(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/* 致命错误：打印错误信息 + 自定义错误码后退出 */
void err_exit(int error, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

/* 致命错误：打印错误信息 + 系统错误码 + core dump 后退出 */
void err_dump(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, 0, fmt, ap);
    va_end(ap);
    abort();        /* 触发 core dump */
    exit(1);        /* 备用退出（abort 后不会执行） */
}

/* 日志：非致命错误（打印到系统日志） */
void log_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, 0, fmt, ap);
    va_end(ap);
}

/* 日志：致命错误（打印到系统日志后退出） */
void log_sys(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/* 日志：非致命错误（仅打印信息，不含错误码） */
void log_msg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

/* 日志：致命错误（仅打印信息，不含错误码，退出） */
void log_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/* 错误处理核心函数：根据参数决定是否打印错误码、是否写入日志 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE - 1, fmt, ap);  /* 格式化可变参数到缓冲区 */
    if (errnoflag) {
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1,
                 ": %s", strerror(error ? error : errno));  /* 追加错误描述 */
    }
    strcat(buf, "\n");  /* 追加换行符 */

    if (log_to_stderr) {
        fflush(stdout);  /* 刷新标准输出，避免错误信息与正常输出混叠 */
        fputs(buf, stderr);  /* 打印到标准错误 */
        fflush(stderr);
    } else {
        syslog(log_priority, "%s", buf);  /* 写入系统日志 */
    }
    return;
}

/* 初始化日志（可选：指定日志标识、选项、优先级） */
void log_open(const char *ident, int option, int priority)
{
    log_to_stderr = 0;
    openlog(ident, option, priority);
}