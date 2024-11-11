#include "grep.h"

int main(int argc, char *argv[]) {
  options *flag = flags(argc, argv);
  return 0;
}

options *flags(int argc, char **argv) {
  options *flags = (options *)malloc(sizeof(options));
  const char *short_flag = "e:ivclnhsf:o";
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  flags_cycle(argc, argv, flags, short_flag, long_options);
  return flags;
}

void e_flag(options *flags) {
  if (flags->regex[0] != 0) strcat(flags->regex, "|");
  strcat(flags->regex, optarg);
}

void f_flag(options *flags) {
  if (flags->f_filename[0] != 0) strcat(flags->f_filename, "|");
  strcat(flags->f_filename, optarg);
}

void flags_cycle(int argc, char **argv, options *flags, const char *short_flag,
                 const struct option *long_option) {
  int opt;
  while ((opt = getopt_long(argc, argv, short_flag, long_option, NULL)) != -1) {
    if (opt == 'e')
      e_flag(flags);
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
      f_flag(flags);
    else if (opt == 'o')
      flags->o = 1;
    else
      flags->no_flags = 1;
  }
}