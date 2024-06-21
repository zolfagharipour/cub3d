#include "cubid.h"

int arg_error(int argc, char **argv)
{
    int fd;

    fd = 0;
    if (argc != 2 || !argv[1])
        return (0);
    return 1;
}
