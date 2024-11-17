#include "common.h"

FILE* file_open(FILE *fileptr, char *filename, char **argv, int pos_argv, int *flag_open, int flag){
    fileptr=fopen(filename, "r");
    if(fileptr==NULL && flag==0){
        fprintf(stderr, "%s: %s: file or directory doesnt exist\n", argv[0], argv[pos_argv]);
        *flag_open=1;
        return 0;
    }
    if(flag!=0 && fileptr==NULL) *flag_open=1;
    return fileptr;
}