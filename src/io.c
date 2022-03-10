#include "includes/io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Reads the contents of a file
 *
 * @param char* filename
 *
 * @return char*
 */
char* stakz_read_file(const char* filename)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read; // Must be `ssize` since an error may return -1

    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not read file `%s`\n", filename);
        exit(1);
    }

    char* buffer = (char*) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while((read = getline(&line, &len, fp)) != -1)
    {
        buffer = (char*) realloc(buffer, (strlen(buffer) + strlen(line) + 2) * sizeof(char));
        char* ret = calloc(strlen(line) + 2, sizeof(char));
        strcat(ret, line);
        strcat(ret, (char[]){'\n', 0});

        strcat(buffer, ret);
        free(ret);
    }

    fclose(fp);
    if(line) free(line);
    
    return buffer;
}

FILE* stakz_open_file(const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if(fp != NULL)
    {
        fprintf(stderr, "\033[1;31m[IO] File `%s already exists!`\n", filename);
        exit(1);
    }
    fclose(fp);
    
    fp = fopen(filename, "a+");
    fprintf(fp, ".global _start\n.align 2\n\n_start:\n\t");

    return fp;
}

int stakz_append_file(FILE* file, char* data)
{
    if(file)
    {
        printf("Success!");
    }
    return 1;
}