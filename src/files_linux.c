#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // STDIN_FILENO, …
int main(int argc, char **argv)
{
    int fdr, fdw; // file descriptors
    char c;
    if (argc != 3)
    {
        fputs("usage: a.out <inp file> <out file>", stderr);
        exit(EXIT_FAILURE);
    }
    fdr = open(argv[1], O_RDONLY); // open files
    fdw = open(argv[2], O_WRONLY | O_CREAT);
    if (fdr < 0 || fdw < 0)
    {
        perror("failed to open input or output files");
        exit(EXIT_FAILURE);
    }
    while (read(fdr, &c, 1)) // read/write a single char
    {                        // from/to the files
        if (write(fdw, &c, 1) != 1)
        {
            perror("write() failed");
            exit(EXIT_FAILURE);
        }
        write(1, &c, 1); // echo char to stdout
    }
    close(fdr); // close the files
    close(fdw);

    int a;
    scanf("%d", &a);
    exit(EXIT_SUCCESS);
}
