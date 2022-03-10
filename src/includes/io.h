#ifndef STAKZ_IO_H
#define STAKZ_IO_H
#include <stdio.h>

typedef struct STAKZ_IO_POSITION_STRUCT
{
  size_t lineNumber;
  size_t charNumber;
  char*  filename;
} pos_t;

char* stakz_read_file(const char* filename);
FILE* stakz_open_file(const char* filename);
int stakz_append_file(FILE* file, char* data);

#endif
