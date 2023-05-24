.PHONY: all install dvi dist tests gcov_report leaks valgrind clang clean

CC=gcc
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
TEST_FLAGS:=$(CFLAGS) -g#-fsanitize=address -O1 -fno-omit-frame-pointer
LINUX_FLAGS =-lrt -lpthread -lm
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
LIBS=-lgtest
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

TARGET = s21_smart_calc.a

SRC=./model/model.cc

TEST_SRC=./unit_tests/unit_tests.cc

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install dvi open_exe

$(TARGET): ${SRC}
	$(CC) -c $(CFLAGS) -I $(CPPFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

install:
	make clean
	mkdir build
	cd ui && qmake && make && make clean && rm Makefile && cd ../ && mv ui/SmartCalc.app build

uninstall:
	rm -rf build*

open_exe:
	$(OPEN_CMD) build/SmartCalc.app

dvi:
	$(OPEN_CMD) readme.html

dist:
	rm -rf SmartCalc_v2.0/
	mkdir SmartCalc_v2.0/
	mkdir SmartCalc_v2.0/src
	mv ./build/SmartCalc.app SmartCalc_v2.0/src/
	tar cvzf SmartCalc_v2.0.tgz SmartCalc_v2.0/
	rm -rf SmartCalc_v2.0/

tests: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) $(SRC) $(TEST_SRC) -o unit_test
else
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(SRC) $(CPPFLAGS) -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) $(SRC) -o gcov_report 
else
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(TEST_SRC) $(SRC) -o gcov_report $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

leaks: test
	leaks -atExit -- ./unit_test

valgrind: clean $(TARGET)
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(SRC) $(CPPFLAGS) -o valgrind_test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test
	$(OPEN_CMD) ./RESULT_VALGRIND.txt

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n ./controller/*.cc ./controller/*.h ./model/*.cc ./model/*.h ./view/*.cc ./view/*.h ./unit_tests/*.cc
	rm .clang-format

clean:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf gcov_report
	rm -rf valgrind_test
	rm -rf *.dSYM
	rm -rf unit_test
	rm -rf RESULT_VALGRIND.txt
