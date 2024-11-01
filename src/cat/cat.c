#include "cat.h"

options *flags(int argc, char **argv) {
  options *flags = (options *)malloc(sizeof(options));
  const char small_fl[] = "beEnsTtv";
  const struct option long_fl[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                   {"number", no_argument, NULL, 'n'},
                                   {"squeeze-blank", no_argument, NULL, 's'},
                                   {NULL, 0, NULL, 0}};
  int flag = 0;
  while ((flag = getopt_long(argc, argv, small_fl, long_fl, NULL)) != -1) {
    flag_choice(flag, flags);
  }
  return flags;
}

void flag_choice(int flag, options *flags) {
  if (flag == 'b') {
    flags->b = 1;
  } else if (flag == 'e') {
    flags->e = 1;
  } else if (flag == 'E') {
    flags->E = 1;
  } else if (flag == 'n') {
    flags->n = 1;
  } else if (flag == 's') {
    flags->s = 1;
  } else if (flag == 't') {
    flags->t = 1;
  } else if (flag == 'T') {
    flags->T = 1;
  } else if (flag == 'v') {
    flags->v = 1;
  } else {
    flags->no_flags = 1;
  }
}

void mutual_exclusion(options *flag) {
  if (flag->b == 1) flag->n = 0;
  if (flag->e || flag->t) flag->v = 1;
}

void cat(int argc, char **argv, options *flag) {
  FILE *fp = NULL;
  if (flag->no_flags) {
    printf("ERROR\n");
    return;
  }
  for (int i = optind; i < argc; ++i) {
    fp = fopen(argv[i], "r");
    if (fp != NULL) {
      output(fp, flag);
      fclose(fp);
    } else {
      printf("ERROR\n");
    }
  }
}

int output(FILE *fp, options *flag) {
  char s = 0, s_prev = 0;
  static int number = 0;
  int blank_line = 0;
  while ((s = fgetc((fp == NULL) ? stdin : fp)) != EOF) {
    int fl_v = 0;
    if (s == '\n' && s_prev == '\n') {
      if (flag->s && blank_line) {
        continue;
      }
      blank_line = 1;
    } else {
      blank_line = 0;
    }
    if (flag->b) flag_b(&number, s, s_prev);
    if (flag->n) flag_n(&number, s_prev, s);
    if (flag->e || flag->E) flag_e(s);
    if (flag->t || flag->T) {
      flag_t(s);
      fl_v = 1;
    }
    if (flag->v) flag_v(&fl_v, s);
    if (((flag->t && s != '\t') || (!flag->t)) &&
        ((flag->T && s != '\t') || (!flag->T)) && (!fl_v || (flag->T && fl_v)))
      fprintf(stdout, "%c", s);
    s_prev = s;
  }
  return 0;
}

void flag_b(int *number, char s, char s_prev) {
  if ((!(*number) && !s_prev && s != '\n') || (s_prev == '\n' && s != '\n') ||
      (number && !s_prev && s != '\n')) {
    (*number)++;
    fprintf(stdout, "%6d\t", *number);
  }
}

void flag_e(char s) {
  if (s == '\n') fprintf(stdout, "$");
}

void flag_n(int *number, char s_prev, char s) {
  if (s_prev == '\n' || (number && !s_prev && s != '\n')) {
    (*number)++;
    fprintf(stdout, "%6d\t", *number);
  }
}

void flag_t(char s) {
  if (s == '\t') fprintf(stdout, "^I");
}

void flag_v(int *fl, char s) {
  if (isprint(s) == 0 && s != 10 && s != 9) {
    if (s != 127)
      s += 64;
    else
      s = '?';
    fprintf(stdout, "^%c", s);
    *fl = 1;
  } else
    *fl = 0;
}

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  mutual_exclusion(flag);
  cat(argc, argv, flag);
  free(flag);
  return 0;
}