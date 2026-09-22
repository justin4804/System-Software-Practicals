#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child PID = %d\n", getpid());
        printf("Initial PPID = %d\n", getppid());

        sleep(5);

        printf("After parent exits:\n");
        printf("New PPID = %d\n", getppid());

        sleep(10);
    }
    else
    {
        printf("Parent PID = %d\n", getpid());

        sleep(2);

        printf("Parent exiting...\n");
        exit(0);
    }

    return 0;
}
