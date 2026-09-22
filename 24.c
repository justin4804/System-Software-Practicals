#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t children[3];

    for (int i = 0; i < 3; i++)
    {
        children[i] = fork();

        if (children[i] < 0)
        {
            perror("fork");
            return 1;
        }

        if (children[i] == 0)
        {
            printf("Child %d: PID = %d\n",
                   i + 1,
                   getpid());

            sleep((i + 1) * 2);

            printf("Child %d exiting\n", i + 1);

            exit(10 + i);
        }
    }

    int status;

    printf("Parent waiting specifically for Child 2...\n");

    waitpid(children[1], &status, 0);

    if (WIFEXITED(status))
    {
        printf("Child 2 exited with status %d\n",
               WEXITSTATUS(status));
    }

    printf("Parent now waits for remaining children...\n");

    waitpid(children[0], NULL, 0);
    waitpid(children[2], NULL, 0);

    return 0;
}
