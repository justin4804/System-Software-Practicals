#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("test.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("Opened successfully. FD = %d\n", fd);

    close(fd);

    printf("\nTrying O_CREAT | O_EXCL...\n");

    fd = open("test.txt", O_RDWR | O_CREAT | O_EXCL, 0644);

    if (fd == -1)
    {
        perror("open with O_EXCL");
    }
    else
    {
        printf("Created successfully. FD = %d\n", fd);
        close(fd);
    }

    return 0;
}
