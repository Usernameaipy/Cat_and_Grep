#ifndef GREP_H
#define GREP_H
#include "../common/common.h"
typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int no_flags;
  char regex[4096];
  char f_filename[4096];
} options;
options* flags(int, char**);
void flags_cycle(int, char** a, options*, const char*, const struct option*);
void e_flag(options*);
void f_flag(options*);
#endif