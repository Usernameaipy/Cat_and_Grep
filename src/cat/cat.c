#include "cat.h"

options *flags(int argc, char **argv) {
  options *flags = (options *)malloc(sizeof(options));
  const char small_fl[] = "beEnsTtv";
  const struct option long_fl[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                   {"number", no_argument, NULL, 'n'},
                                   {"squeeze-blank", no_argument, NULL, 's'},
                                   {NULL, 0, NULL, 0}};
  int flag;
  while ((flag = getopt_long(argc, argv, small_fl, long_fl, NULL)) != -1) {
      flag_choice(flag, flags);
  }
  return flags;
}

void flag_choice(int flag, options *flags)
{
    if(flag=='b'){
        flags->b=1;
    } else if(flag=='e'){
        flags->b = 1;
    } else if(flag=='E'){
        flags->E = 1;
    } else if(flag=='n'){
        flags->n = 1;
    } else if(flag=='s'){
        flags->s = 1;
    } else if(flag=='t'){
        flags->t = 1;
    } else if(flag=='T'){
        flags->T = 1;
    } else if(flag=='v'){
        flags->v = 1;
    } else {
        flags->no_flags=1;
    }
}

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  free(flag);
  return 0;
}