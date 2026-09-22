#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd2;

    // Open file in append mode
    fd = open("append.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicate fd using fcntl()
    fd2 = fcntl(fd, F_DUPFD, 10);

    if (fd2 == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Original FD = %d\n", fd);
    printf("Duplicated FD = %d\n", fd2);

    // Write using original descriptor
    write(fd, "Using fd\n", 9);

    // Write using duplicated descriptor
    write(fd2, "Using fd2\n", 10);

    close(fd);
    close(fd2);

    return 0;
}
