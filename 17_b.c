#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(int);
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("lock");
        close(fd);
        return 1;
    }

    read(fd, &ticket, sizeof(ticket));

    ticket++;

    lseek(fd, 0, SEEK_SET);

    write(fd, &ticket, sizeof(ticket));

    printf("Reserved ticket number = %d\n", ticket);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}
