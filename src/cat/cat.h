#ifndef CAT_H
#define CAT_H
#include "../common/common.h"
typedef struct options {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
  int no_flags;
} options;
options *flags(int, char **);
void flag_choice(int flag, options *flags);
#endif