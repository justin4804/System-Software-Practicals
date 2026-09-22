#include <stdio.h>
#include <sched.h>

int main()
{
    int min_fifo, max_fifo;
    int min_rr, max_rr;

    min_fifo = sched_get_priority_min(SCHED_FIFO);
    max_fifo = sched_get_priority_max(SCHED_FIFO);

    min_rr = sched_get_priority_min(SCHED_RR);
    max_rr = sched_get_priority_max(SCHED_RR);

    printf("SCHED_FIFO:\n");
    printf("Minimum priority = %d\n", min_fifo);
    printf("Maximum priority = %d\n", max_fifo);

    printf("\nSCHED_RR:\n");
    printf("Minimum priority = %d\n", min_rr);
    printf("Maximum priority = %d\n", max_rr);

    return 0;
}
