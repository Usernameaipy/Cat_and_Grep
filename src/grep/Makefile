CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
BUILDDIR = ../../build/

all : grep clean_o

grep : grep.o common.o
	$(CC) $(CFLAGS) grep.o common.o -o $(BUILDDIR)grep

grep.o : grep.c grep.h
	$(CC) $(CFLAGS) -c grep.c -o grep.o

common.o : ../common/common.c ../common/common.h
	$(CC) $(CFLAGS) -c ../common/common.c -o common.o

clean_o :
	rm -rf *.o

clean : clean_o
	rm -rf $(BUILDDIR)grep

rebuild : clean all

style_check :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -style=Google -n

style :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -style=Google -i

valgrind : clean
	make grep && valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILDDIR)grep