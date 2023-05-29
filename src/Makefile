.PHONY: all install dvi dist tests gcov_report leaks valgrind clang clean

CC=gcc
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
TEST_FLAGS:=$(CFLAGS) -g#-fsanitize=address -O1 -fno-omit-frame-pointer
LINUX_FLAGS =-lrt -lpthread -lm
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
LIBS=-lgtest
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
#For Linux support
CMAKE_FLAGS=-DCMAKE_PREFIX_PATH="/home/user/Qt/6.5.1/gcc_64"

SRC=./model/model.cc

TEST_SRC=./model/tests/unit_tests.cc

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: tests gcov_report install dist dvi open

install: clean uninstall
	mkdir -p build && cd build && cmake .. $(CMAKE_FLAGS)
	cd build && make

uninstall:
	rm -rf build*
	rm -rf ./view/build*

dvi:
	$(OPEN_CMD) readme.html

dist: clean
	zip -r SmartCalc_v2.zip *

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
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clean:
	rm -rf *.dSYM
	rm -rf unit_test
	rm -rf *.gcda	*.gcno *.info report gcov_report
	rm -rf valgrind_test RESULT_VALGRIND.txt
	rm -rf *.zip

open:
ifeq ($(OS), Darwin)
	./build/SmartCalc.app/Contents/MacOS/SmartCalc
else
	./build/SmartCalc
endif

leaks: test
	leaks -atExit -- ./unit_test

valgrind: clean
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(SRC) $(CPPFLAGS) -o valgrind_test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n ./controller/*.cc ./controller/*.h ./model/*.cc ./model/*.h ./view/*.cc ./view/app/*.cc ./view/app/*.h ./model/tests/*.cc
	rm .clang-format


	
