#include "includes/stakz.h"
#include "includes/list.h"
#include "includes/token.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage:\n%s input.stx\n", argv[0]);
        return 1;
    }
    
    if(argc > 2 && strcmp(argv[2], "-f=print-err") == 0)
    {
        char* cmd = calloc(strlen(argv[0]) + strlen(argv[1]) + 21, sizeof(char));
        strcat(cmd, argv[0]);
        strcat(cmd, " ");
        strcat(cmd, argv[1]);
        strcat(cmd, " 2> stakz_error.log");
        
        system(cmd);
        free(cmd);
        exit(0);
    }
    stakz_compile_file(argv[1]);
    return 0;
}
