#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 50


void lock_record(int fd, int record)
{
    struct flock lock;

    lock.l_type = F_RDLCK;      // Read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = record * SIZE;
    lock.l_len = SIZE;


    if(fcntl(fd, F_SETLKW, &lock)==-1)
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


    fcntl(fd,F_SETLK,&lock);
}



int main()
{
    int fd;
    char buffer[SIZE];


    fd=open("records.txt",O_RDONLY);


    if(fd==-1)
    {
        perror("open");
        return 1;
    }



    int record_no=2;   // Access Record 3



    printf("Locking Record %d...\n",record_no+1);



    // Apply read lock
    lock_record(fd,record_no);



    printf("Read lock acquired\n");



    lseek(fd,record_no*SIZE,SEEK_SET);



    read(fd,buffer,SIZE);



    printf("Record Data: %s\n",buffer);



    unlock_record(fd,record_no);



    printf("Read lock released\n");



    close(fd);


    return 0;
}
