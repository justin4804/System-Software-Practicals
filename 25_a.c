#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Before exec\n");

    execl("./25",
          "./25",
          (char *)NULL);

    perror("execl");

    return 1;
}
