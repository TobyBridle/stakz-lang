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
#endif
