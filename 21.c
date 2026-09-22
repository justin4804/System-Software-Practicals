#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd;

    fd = open("forkfile.txt",
              O_CREAT | O_WRONLY | O_TRUNC,
              0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        write(fd, "Child writes\n", 13);
    }
    else
    {
        write(fd, "Parent writes\n", 14);
        wait(NULL);
    }

    close(fd);

    return 0;
}
