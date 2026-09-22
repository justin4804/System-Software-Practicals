#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int target_hour;
    int target_minute;

    if (argc != 2)
    {
        printf("Usage: %s HH:MM\n", argv[0]);
        return 1;
    }

    if (sscanf(argv[1],
               "%d:%d",
               &target_hour,
               &target_minute) != 2)
    {
        printf("Invalid time format.\n");
        return 1;
    }

    if (target_hour < 0 || target_hour > 23 ||
        target_minute < 0 || target_minute > 59)
    {
        printf("Invalid time.\n");
        return 1;
    }

    /*
     * First fork
     */
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        return 0;
    }

    /*
     * Create new session
     */
    if (setsid() == -1)
    {
        perror("setsid");
        return 1;
    }

    /*
     * Second fork
     */
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        return 0;
    }

    /*
     * Become independent of terminal/filesystem state.
     */
    umask(0);
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /*
     * Wait until target time.
     */
    while (1)
    {
        time_t now;
        struct tm *tm_now;

        time(&now);
        tm_now = localtime(&now);

        if (tm_now->tm_hour == target_hour &&
            tm_now->tm_min == target_minute)
        {
            system("/home/justin/Documents/System_Software_Practicals/PS1/script.sh");
            break;
        }

        sleep(20);
    }

    return 0;
}
