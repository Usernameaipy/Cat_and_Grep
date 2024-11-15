#ifndef GREP_H
#define GREP_H
#include "../common/common.h"
typedef struct {
  char **matrix;
  size_t size_now;
  size_t size_max;
} feflags_t;
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
  feflags_t *regex;
  feflags_t *f_filename;
} options;
options *flags(int, char **);
void flags_cycle(int, char **a, options *, const char *, const struct option *);
options *create_flags(void);
void add_matrix(feflags_t *, int);
void add_fe_arg(feflags_t *, char *, int);
void fe_flag(options *, int);
void free_options(options *);
void grep(options *, int, char **);
void output(FILE *, options *, char *, int *, char *);
#endif