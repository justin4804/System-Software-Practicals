#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

void print_policy(int policy)
{
    switch (policy)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;

        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;

        case SCHED_RR:
            printf("SCHED_RR\n");
            break;

        default:
            printf("Unknown policy\n");
    }
}

int main()
{
    int policy;

    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");
    print_policy(policy);

    struct sched_param param;

    param.sched_priority =
        sched_get_priority_min(SCHED_FIFO);

    printf("\nTrying SCHED_FIFO...\n");

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler SCHED_FIFO");
    }
    else
    {
        printf("Successfully changed to SCHED_FIFO\n");
    }

    policy = sched_getscheduler(0);

    printf("Current policy: ");
    print_policy(policy);

    printf("\nTrying SCHED_RR...\n");

    param.sched_priority =
        sched_get_priority_min(SCHED_RR);

    if (sched_setscheduler(0, SCHED_RR, &param) == -1)
    {
        perror("sched_setscheduler SCHED_RR");
    }
    else
    {
        printf("Successfully changed to SCHED_RR\n");
    }

    policy = sched_getscheduler(0);

    printf("Current policy: ");
    print_policy(policy);

    return 0;
}
