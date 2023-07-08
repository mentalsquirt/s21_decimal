NAME = s21_decimal
CC = gcc
CC_FLAGS = -std=c11 -Wall -Wextra -Werror -g -pedantic
GCOV_FLAGS = -L. -ls21_decimal --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check)
endif

TEST_COMPILE = $(CC) $(CC_FLAGS) tests/*.c libs21_decimal.a $(CHECK_FLAGS) -L. -ls21_decimal

all: clean s21_decimal.a

clean:
	rm -rf *.o, *.g* *.info *.out report *.a *.dSYM

re: clean all

s21_decimal.o:
	$(CC) $(CC_FLAGS) -c s21_*.c

s21_decimal.a: s21_decimal.o
	ar rcs libs21_decimal.a *.o
	rm -rf *.o
	ranlib libs21_decimal.a
	cp libs21_decimal.a s21_decimal.a

test: s21_decimal.a
	$(TEST_COMPILE)
	./a.out

gcov_report: s21_decimal.a test
	rm -f *.g*
	$(CC) $(CC_FLAGS) s21_*.c tests/*.c libs21_decimal.a $(CHECK_FLAGS) $(GCOV_FLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno

check:
	clang-format -style=google -i s21_*.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean

.PHONY: all clean re s21_decimal.a test gcov_report check
