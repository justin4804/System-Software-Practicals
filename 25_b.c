#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./14",
          "./14",
          "q8.txt",
          (char *)NULL);

    perror("execl");

    return 1;
}
