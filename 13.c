#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    fd_set readfds;
    struct timeval timeout;
    int ret;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");
    fflush(stdout);

    ret = select(STDIN_FILENO + 1,
                 &readfds,
                 NULL,
                 NULL,
                 &timeout);

    if (ret == -1)
    {
        perror("select");
    }
    else if (ret == 0)
    {
        printf("No data available within 10 seconds.\n");
    }
    else
    {
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char buffer[100];

            ssize_t n = read(STDIN_FILENO,
                             buffer,
                             sizeof(buffer) - 1);

            if (n > 0)
            {
                buffer[n] = '\0';
                printf("Data available: %s", buffer);
            }
        }
    }

    return 0;
}
