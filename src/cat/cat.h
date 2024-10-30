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
void flag_choice(int, options *);
void cat(int, char **, options *);
int output(FILE *, options *);
void flag_b(int *, char, char);
void flag_e(char);
void flag_n(int *, char, char);
void flag_t(char);
void mutual_exclusion(options *);
#endif