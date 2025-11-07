#include <iostream>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void)
{
    int n = 0;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            perror("write error");
        }
    }

    if (n < 0)
    {
        perror("read error");
    }

    exit(0);
}