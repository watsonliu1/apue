#include <iostream>
#include <unistd.h>

#define MAXLINE 4096

using std::cout;
using std::endl;

int main(void)
{
    char buf[MAXLINE];
    pid_t pid = 0;
    int status = 0;

    cout << "%";

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) -1 ] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }

        if ((pid = fork()) < 0)
        {
            perror("fork error");
            exit(-1);
        }
        else if (pid == 0)  /* 子进程 */
        {
            execlp(buf, buf, (char *)0);
            cout << "couldn't execute: " << buf;
            exit(127);
        }

        /* 父进程 */
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            perror("waitpid error");
            exit(-1);
        }

        cout << "%";
    }


    exit(0);
}