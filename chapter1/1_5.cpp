#include <iostream>

int main(void)
{
    int c = 0;

    while( (c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            perror("output error");
        }
    }

    if (ferror(stdin))
    {
        perror("input error");
    }

    exit(0);
}