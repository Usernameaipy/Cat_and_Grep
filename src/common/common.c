#include "common.h"

FILE* file_open(FILE *fileptr, char *filename, char **argv, int pos_argv, int *flag_open){
    fileptr=fopen(filename, "r");
    if(fileptr==NULL){
        fprintf(stderr, "%s: %s: file or directory doesnt exist\n", argv[0], argv[pos_argv]);
        *flag_open=1;
        return 0;
    }
    return fileptr;
}