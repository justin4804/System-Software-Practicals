#include <stdio.h>
#include <unistd.h>

int main()
{
    char *env[] =
    {
        "PATH=/bin:/usr/bin",
        "MYVAR=HELLO",
        NULL
    };

    execle("/bin/ls",
           "ls",
           "-Rl",
           (char *)NULL,
           env);

    perror("execle");

    return 1;
}
