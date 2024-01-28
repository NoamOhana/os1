#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    FILE *fdr, *fdw; // file descriptors in C
    char c;
    if (argc != 3)
    {
        fputs("usage: a.out <inp file> <out file>", stderr);
        exit(EXIT_FAILURE);
    }
    fdr = fopen(argv[1], "r"); // openning the files
    fdw = fopen(argv[2], "w");
    if (!fdr || !fdw)
    {
        perror("failed to open input or output files");
        exit(EXIT_FAILURE);
    }
    while ((c = fgetc(fdr)) != EOF)
    {                     // reading/writing
        fputc(c, fdw);    // a single char
        fputc(c, stdout); // from/to a file
    }
    fclose(fdr); // closing the files
    fclose(fdw);
    exit(EXIT_SUCCESS);
}