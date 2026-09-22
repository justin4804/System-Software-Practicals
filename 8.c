#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    char buffer[1];
    char line[1024];
    int index = 0;
    ssize_t bytesRead;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file in read-only mode
    fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Read the file one byte at a time
    while ((bytesRead = read(fd, buffer, 1)) > 0) {

        if (buffer[0] == '\n') {
            // End of current line
            line[index] = '\0';
            printf("%s\n", line);
            index = 0;
        }
        else {
            line[index++] = buffer[0];
        }
    }

    // Handle the last line if it doesn't end with '\n'
    if (index > 0) {
        line[index] = '\0';
        printf("%s\n", line);
    }

    if (bytesRead == -1) {
        perror("read");
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
