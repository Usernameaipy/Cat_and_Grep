#include "grep.h"

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  return 0;
}

options *flags(int argc, char **argv) {
  options *flags = create_flags();
  const char *short_flag = "e:ivclnhsf:o";
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  flags_cycle(argc, argv, flags, short_flag, long_options);
  return flags;
}

options *create_flags(void) {
  options *flags = (options *)malloc(sizeof(options));
  flags->regex = NULL;
  flags->f_filename = NULL;
  flags->regex = (feflags_t *)malloc(sizeof(feflags_t));
  flags->f_filename = (feflags_t *)malloc(sizeof(feflags_t));
  if (flags->regex && flags->f_filename) {
    feflags_t *stru = flags->regex;
    stru->matrix = (char **)malloc(sizeof(char *) * 2);
    if (stru->matrix) {
      stru->size_max = 2;
      stru->size_now = 0;
    }

    stru = flags->f_filename;
    stru->matrix = (char **)malloc(sizeof(char *) * 2);
    if (stru->matrix) {
      stru->size_max = 2;
      stru->size_now = 0;
    }
  }
  return flags;
}

void add_matrix(feflags_t *stru, int flag) {
  int pref_size = stru->size_now;
  char **pref_matrix = stru->matrix;
  stru->size_max = stru->size_max * 2;
  char **new_matrix = (char **)malloc(sizeof(char *) * stru->size_max);
  if (new_matrix != NULL) {
    for (int i = 0; i < pref_size; i++) {
      new_matrix[i] = (char *)malloc(sizeof(char) * ((flag == 0) ? 256 : 1024));
      if (new_matrix[i] != NULL) {
        strcpy(new_matrix[i], pref_matrix[i]);
      }
      free(pref_matrix[i]);
    }
    free(pref_matrix);
  } else {
    new_matrix = NULL;
  }
  stru->matrix = new_matrix;
}

void add_fe_arg(feflags_t *stru, char *str, int flag) {
  if (stru->size_now == stru->size_max) add_matrix(stru, flag);
  if (stru->matrix) {
    char **mtr = stru->matrix;
    mtr[stru->size_now] =
        (char *)malloc(sizeof(char) * ((flag == 0) ? 256 : 1024));
    if (mtr[stru->size_now]) {
      strncpy(mtr[stru->size_now], str, (flag == 0) ? 256 : 1024);
      stru->size_now += 1;
    }
  }
}

void fe_flag(options *flags, int flag) {
  if (flag == 0) {
    flags->f = 1;
    add_fe_arg(flags->f_filename, optarg, flag);
  } else {
    flags->e = 1;
    add_fe_arg(flags->f_filename, optarg, flag);
  }
}

void flags_cycle(int argc, char **argv, options *flags, const char *short_flag,
                 const struct option *long_option) {
  int opt;
  while ((opt = getopt_long(argc, argv, short_flag, long_option, NULL)) != -1) {
    if (opt == 'e')
      fe_flag(flags, 1);
    else if (opt == 'i')
      flags->i = 1;
    else if (opt == 'v')
      flags->v = 1;
    else if (opt == 'c')
      flags->c = 1;
    else if (opt == 'l')
      flags->l = 1;
    else if (opt == 'n')
      flags->n = 1;
    else if (opt == 'h')
      flags->h = 1;
    else if (opt == 's')
      flags->s = 1;
    else if (opt == 'f')
      fe_flag(flags, 0);
    else if (opt == 'o')
      flags->o = 1;
    else
      flags->no_flags = 1;
  }
}