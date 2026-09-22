#include <stdio.h>
#include <unistd.h>

int main()
{
    execlp("ls",
           "ls",
           "-Rl",
           (char *)NULL);

    perror("execlp");

    return 1;
}
