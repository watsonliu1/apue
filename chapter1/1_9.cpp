#include <iostream>
#include <unistd.h>

int main()
{
    std::cout << "uid = " << getuid() << ", gid = " << getgid() << std::endl;

    exit(0);
}