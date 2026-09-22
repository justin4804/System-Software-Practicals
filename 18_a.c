#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 50


void lock_record(int fd, int record)
{
    struct flock lock;

    lock.l_type = F_WRLCK;      // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = record * SIZE;
    lock.l_len = SIZE;

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Lock");
    }
}


void unlock_record(int fd, int record)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record * SIZE;
    lock.l_len = SIZE;

    fcntl(fd, F_SETLK, &lock);
}


int main()
{
    int fd;
    char buffer[SIZE];

    fd = open("records.txt", O_RDWR);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }


    int record_no = 1;   // Access Record 2


    printf("Locking Record %d...\n", record_no+1);


    // Lock record
    lock_record(fd, record_no);


    printf("Record locked\n");


    // Move to record position
    lseek(fd, record_no * SIZE, SEEK_SET);


    // Read old record
    read(fd, buffer, SIZE);

    printf("Old Record: %s\n", buffer);



    // Modify record

    lseek(fd, record_no * SIZE, SEEK_SET);

    char newdata[SIZE] = "Bob 500";

    write(fd, newdata, strlen(newdata)+1);


    printf("Record updated\n");


    // Unlock
    unlock_record(fd, record_no);


    printf("Record unlocked\n");


    close(fd);

    return 0;
}
