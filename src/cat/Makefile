CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
BUILDDIR = ../../build/
# TESTFLAGS = 

all : cat clean_o

cat : cat.o common.o
	$(CC) $(CFLAGS) cat.o common.o -o $(BUILDDIR)cat

cat.o : cat.c cat.h
	$(CC) $(CFLAGS) -c cat.c -o cat.o

common.o : ../common/common.c ../common/common.h
	$(CC) $(CFLAGS) -c ../common/common.c -o common.o

clean_o :
	rm -rf *.o

clean : clean_o
	rm -rf *.txt
	rm -rf $(BUILDDIR)cat

rebuild : clean all

style_check :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -style=Google -n

style :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -style=Google -i

#valgrind