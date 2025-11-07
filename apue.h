#ifndef _APUE_H
#define _APUE_H

#define _XOPEN_SOURCE 600  /* 启用 X/Open 标准，兼容更多 Unix 系统 */
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdarg.h>
#include <syslog.h>
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <utmp.h>
#include <utmpx.h>
#include <lastlog.h>
#include <sys/utsname.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/statvfs.h>
#include <sys/mount.h>
#include <sys/statfs.h>
#include <dirent.h>
#include <fnmatch.h>
#include <glob.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <pty.h>
#include <utime.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>

/* 版本检查：确保系统支持所需的 Unix 标准 */
#if defined(SOLARIS)
# define _APUE_SOLARIS
# include <sys/filio.h>
# include <sys/sockio.h>
# include <sys/statvfs.h>
# define statfs statvfs
# define fstatfs fstatvfs
#elif defined(BSD)
# define _APUE_BSD
# include <sys/filio.h>
# include <sys/sockio.h>
# include <sys/statvfs.h>
# define statfs statvfs
# define fstatfs fstatvfs
#elif defined(LINUX)
# define _APUE_LINUX
# include <sys/filio.h>
# include <sys/sockio.h>
#endif

/* 常用宏定义 */
#define MAXLINE 4096                 /* 最大行长度 */
#define BUFFSIZE 8192                /* 缓冲区大小 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  /* 默认文件权限：644 */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH) /* 默认目录权限：755 */

#define offsetof(type, member) ((size_t)&((type *)0)->member)

/* 错误处理函数声明（需在 error.c 中实现） */
void err_dump(const char *, ...) __attribute__((noreturn));
void err_msg(const char *, ...);
void err_quit(const char *, ...) __attribute__((noreturn));
void err_exit(int, const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_sys(const char *, ...) __attribute__((noreturn));

/* 日志相关函数声明 */
void log_msg(const char *, ...);
void log_open(const char *, int, int);
void log_quit(const char *, ...) __attribute__((noreturn));
void log_ret(const char *, ...);
void log_sys(const char *, ...) __attribute__((noreturn));

/* 其他工具函数声明 */
char *path_alloc(int *);            /* 分配路径名缓冲区 */
uid_t uid_find(const char *);       /* 通过用户名查找 UID */
gid_t gid_find(const char *);       /* 通过组名查找 GID */
void pr_exit(int);                  /* 打印进程退出状态 */
void pr_mask(const char *);         /* 打印当前信号掩码 */
int tty_cbreak(int);                /* 设置终端为 cbreak 模式 */
int tty_raw(int);                   /* 设置终端为 raw 模式 */
int tty_reset(int);                 /* 重置终端模式 */
void tty_atexit(void);              /* 注册终端退出清理函数 */
#ifdef _BSD
void sleep_us(unsigned int);        /* BSD 系统的微秒级睡眠 */
#else
void sleep_us(unsigned int);        /* 其他系统的微秒级睡眠（需实现） */
#endif
ssize_t readn(int, void *, size_t); /* 读取指定字节数（避免短读） */
ssize_t writen(int, const void *, size_t); /* 写入指定字节数（避免短写） */
int fd_pipe(int *);                 /* 创建管道并设置非阻塞（可选） */
int recv_fd(int, ssize_t (*)(int, const void *, size_t)); /* 接收文件描述符 */
int send_fd(int, int);              /* 发送文件描述符 */
int send_err(int, int, const char *); /* 发送错误信息 */
int serv_listen(const char *);      /* 监听服务端端口 */
int serv_accept(int, uid_t *);      /* 接受客户端连接并获取 UID */
int cli_conn(const char *, const char *); /* 客户端连接服务端 */
int buf_args(char *, int (*func)(int, char **)); /* 解析缓冲区为命令行参数 */
int ptym_open(char *, int);         /* 打开伪终端主设备 */
int ptys_open(int, const char *);   /* 打开伪终端从设备 */
#ifdef TIOCGWINSZ
struct winsize;
void pr_winsize(int);               /* 打印窗口大小 */
void tty_set_winsize(int, const struct winsize *); /* 设置窗口大小 */
struct winsize *tty_get_winsize(int, struct winsize *); /* 获取窗口大小 */
#else
# define pr_winsize(fd)
# define tty_set_winsize(fd, winp)
# define tty_get_winsize(fd, winp) (NULL)
#endif

#endif /* _APUE_H */