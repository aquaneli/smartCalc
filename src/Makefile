CC = gcc -std=c11 -g
FLAGS = -Wall -Werror -Wextra
BD = ../build/
OS = $(shell uname)
LIBSOURCES = smart_calc.c parcer.c rev_notation.c opr_stack.c out_str.c tests.c

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread -fprofile-arcs -ftest-coverage 
endif

all: test

install: uninstall build
	make clean_qmake

uninstall:
	rm -rf ../build

clean:
	rm -rf smart_calc.o \
	parcer.o \
	rev_notation.o \
	opr_stack.o \
	out_str.o \
	tests.o \
	*.gcno \
	*.gcda \
	./run.dSYM \
	report.info

dist:
	cd $(BD) && tar -czvf dist.tar.gz smart_calc.app dvi.html
	cp ../build/dist.tar.gz .
	rm -rf ../build/dist.tar.gz

build: smart_calc.pro
	cd $(BD); qmake smart_calc.pro; make -C $(BD)

smart_calc.pro:
	mkdir ../build;
	cp smart_calc/dvi.html $(BD)
	cp smart_calc/smart_calc.pro $(BD)

open:
	open ../build/./smart_calc.app

dvi:
	open smart_calc/dvi.html

test: clean tests.o
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage 
	./run

test_val:
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	sh valgrind.sh ./run

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html
	make clean

clean_qmake:
	rm -rf ../build/*.o \
	../build/.qmake.stash \
	../build/ui_graphform.h \
	../build/ui_mainwindow.h \
	../build/Makefile \
	../build/moc_graphform.cpp \
	../build/moc_mainwindow.cpp \
	../build/moc_predefs.h \
	../build/moc_qcustomplot.cpp \
	../build/smart_calc.pro \

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i -n *.c *.h smart_calc/graphform.cpp \
	smart_calc/main.cpp smart_calc/mainwindow.cpp \
	smart_calc/graphform.h smart_calc/mainwindow.h 
	