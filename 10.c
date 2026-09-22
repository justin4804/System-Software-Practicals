#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    off_t pos;

    fd = open("hole.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, "AAAAAAAAAA", 10);

    pos = lseek(fd, 10, SEEK_CUR);

    if (pos == (off_t)-1)
    {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("lseek returned offset = %ld\n", (long)pos);

    write(fd, "BBBBBBBBBB", 10);

    close(fd);

    return 0;
}
