#include <iostream>
#include <unistd.h>

int main(void)
{
    std::cout << "hello world from process ID " << getpid() << std::endl;

    exit(0);
}