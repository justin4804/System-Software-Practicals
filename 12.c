#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    int flags;

    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    flags = fcntl(fd, F_GETFL);

    if (flags == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    switch (flags & O_ACCMODE)
    {
        case O_RDONLY:
            printf("Read only\n");
            break;

        case O_WRONLY:
            printf("Write only\n");
            break;

        case O_RDWR:
            printf("Read write\n");
            break;

        default:
            printf("Unknown mode\n");
    }

    close(fd);

    return 0;
}
