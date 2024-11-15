#include "grep.h"

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  grep(flag, argc, argv);
  if (flag) free_options(flag);
  return 0;
}

options *flags(int argc, char **argv) {
  options *flags = create_flags();
  const char *short_flag = "e:ivclnhsf:o";
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  if (flags) flags_cycle(argc, argv, flags, short_flag, long_options);
  return flags;
}

options *create_flags(void) {
  options *flags = (options *)malloc(sizeof(options));
  if (!flags) return NULL;
  flags->regex = NULL;
  flags->f_filename = NULL;
  flags->regex = (feflags_t *)malloc(sizeof(feflags_t));
  if (!flags->regex) return NULL;
  flags->f_filename = (feflags_t *)malloc(sizeof(feflags_t));
  if (!flags->f_filename) return NULL;
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
      if (pref_matrix[i]) free(pref_matrix[i]);
    }
    if (pref_matrix) free(pref_matrix);
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
  } else if (flag == 1) {
    flags->e = 1;
    add_fe_arg(flags->regex, optarg, flag);
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

void free_options(options *flags) {
  for (int i = 0; i < 2; i++) {
    feflags_t *stru = (i == 0) ? flags->regex : flags->f_filename;
    for (size_t i = 0; i < stru->size_max; i++) {
      if (stru->matrix[i]) free(stru->matrix[i]);
    }
    if (stru->matrix) free(stru->matrix);
    if (flags->regex || flags->f_filename)
      (i == 0) ? free(flags->regex) : free(flags->f_filename);
  }
  if (flags) free(flags);
}

void grep(options *flags, int argc, char **argv) {
  FILE *fp = NULL;
  int number_c = 0;
  int files_open = 0;
  char searching_str[4096] = {0};
  if (!flags->e) strcpy(searching_str, argv[optind]);
  for (int i = (!flags->e) ? optind + 1 : optind; i < argc || optind == argc;
       ++i) {
    int flag_open = 0;
    if (i < argc || optind != argc)
      fp = file_open(fp, argv[i], argv, i, &flag_open);
    if ((optind == argc) || (i < argc && !flag_open)) {
      if (flags->e) {
        feflags_t *reg = flags->regex;
        for (size_t j = 0; j < reg->size_now; j++) {
          strcpy(searching_str, reg->matrix[j]);
          output(fp, flags, searching_str, &number_c, (files_open>=1) ? argv[i] : (argv[i+1]) ? argv[i] : NULL);
        }
      } else{
        output(fp, flags, searching_str, &number_c, (argv[i+1]) ? argv[i] : NULL);
      }
    }
    if (fp!=NULL && flags->c) {
      (files_open >= 1 || argv[i+1]) ? fprintf(stdout, "%s:%d\n", argv[i], number_c)
                       : fprintf(stdout, "%d\n", number_c);
      number_c = 0;
    }
    if (fp != NULL) {
      fclose(fp);
      files_open += 1;
    }
  }
}

void output(FILE *file, options *flags, char *searching_str, int *number_c, char *fl_next_file) {
  char buffer[4096] = {0};
  static int flag_called = 0;
  regex_t regex;
  int reg_flags = REG_EXTENDED;
  while (fgets(buffer, 4096, file)) {
    if (flags->i) reg_flags |= REG_ICASE;

    if (regcomp(&regex, searching_str, reg_flags) != 0) return;
    if ((regexec(&regex, buffer, 0, NULL, 0) == (flags->v) ? REG_NOMATCH : 0) &&
        !flags->c) {
      if(flag_called || fl_next_file) fprintf(stdout, "%s:", fl_next_file);
      fprintf(stdout, "%s", buffer);
      if (strchr(buffer, '\n') == NULL) fprintf(stdout, "\n");
    } else if (flags->c &&
               (regexec(&regex, buffer, 0, NULL, 0) == (flags->v) ? REG_NOMATCH
                                                                  : 0))
      *number_c += 1;
    regfree(&regex);
  }
  flag_called+=1;
}