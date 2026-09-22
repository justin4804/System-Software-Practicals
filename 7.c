#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int src, dest;
    char buffer[4096];
    ssize_t n;

    if (argc != 3)
    {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    src = open(argv[1], O_RDONLY);

    if (src == -1)
    {
        perror("source");
        return 1;
    }

    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (dest == -1)
    {
        perror("destination");
        close(src);
        return 1;
    }

    while ((n = read(src, buffer, sizeof(buffer))) > 0)
    {
        ssize_t written = 0;

        while (written < n)
        {
            ssize_t w = write(dest, buffer + written, n - written);

            if (w == -1)
            {
                perror("write");
                close(src);
                close(dest);
                return 1;
            }

            written += w;
        }
    }

    if (n == -1)
        perror("read");

    close(src);
    close(dest);

    return 0;
}
