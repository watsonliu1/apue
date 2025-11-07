#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *dirp;

    if (argc != 2)
    {
        perror("usage: ls directory_name");
        return -1;
    }

    if ((dp = opendir(argv[1])) == NULL)
    {
        perror("can't open ");
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
        std::cout << dirp->d_name << std::endl;
    }

    closedir(dp);
    

    exit(0);
}