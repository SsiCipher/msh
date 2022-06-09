#include "msh.h"
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        DIR *curr_dir = opendir(getcwd(NULL, 0));

        struct dirent *dir = readdir(curr_dir);
        while (dir != NULL)
        {
            if (dir->d_name[0] != '.')
                printf("%s ", dir->d_name);
            dir = readdir(curr_dir);
        }

        closedir(curr_dir);
    }

    return (0);
}
