#include <stdio.h>
#include <sys/stat.h>

int main()
{
    if (mkfifo("myfifo", 0666) == -1)
    {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully.\n");

    return 0;
}
