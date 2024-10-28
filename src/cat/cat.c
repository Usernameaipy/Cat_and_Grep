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
    switch (flag) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        break;
      case 'E':
        flags->E = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        break;
      case 'T':
        flags->T = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
    }
  }
  return flags;
}

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  free(flag);
  return 0;
}