
CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
TFLAGS=-fprofile-arcs -ftest-coverage
TARGET =QtCAlc
TEST_FOLDER =test/
FUNCTIONS_FOLDER =./
LIB_NAME =s21_smart_calc.a
TESTFALGS =-lcheck

UNIT_TEST=-o unit_test
GCOV_TEST=-o gcov_test
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
ifeq ($(shell uname), Linux)
	TESTFALGS += -lpthread -lrt -lsubunit -lm
endif


all: test gcov_report

${LIB_NAME}:
	$(CC) $(CFLAGS) -c ./*.c
	ar rc ${LIB_NAME} *.o
	rm *.o
	ranlib ${LIB_NAME}

test: ${LIB_NAME}
	${CC} ${CFLAGS} ${UNIT_TEST} ${wildcard ${TEST_FOLDER}*.c} ${LIB_NAME} ${TESTFALGS}
	./unit_test
	rm ${LIB_NAME}
	rm unit_test

gcov_report: 
	${CC} ${CFLAGS} ${GCOV_FLAGS} --coverage ${wildcard ${FUNCTIONS_FOLDER}*.c} ${GCOV_TEST} ${wildcard ${TEST_FOLDER}*.c} ${TESTFALGS}
	./gcov_test
	lcov -t "stest" -o s21_test.info -c -d . -no-external
	genhtml -o report s21_test.info
	open ./report/index.html
	rm gcov_test

valgrind_test: ${LIB_NAME}
	${CC} ${CFLAGS} ${UNIT_TEST} ${wildcard ${TEST_FOLDER}*.c} ${LIB_NAME} ${TESTFALGS}
	leaks -atExit -- ./unit_test
	rm ${LIB_NAME}
	rm unit_test

install:       
	echo "Installation of $(TARGET).app:"
	mkdir -p ../build
	cd ../build && qmake ../src && make && make clean && rm -rf Makefile
	echo "Installation completed! You can find app in the ../build/ folder!"

uninstall:
	rm -rf ../build
	echo "Uninstall completed!"

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf unit_test
	rm -rf *.out
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf ./report
	rm -rf ../build
	rm -rf ../dist
	rm -rf ./html
	rm -rf ./latex
	rm -rf Doxyfile
	
dist: install
	mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp -R . ../dist/src
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app
	@rm -rf ../dist/src
	echo "Archive creation completed successfully!"

dvi:
	doxygen -g
	doxygen ./Doxyfile
	open ./html/index.html

check_clang_format:
	mv ../materials/linters/.clang-format .
	clang-format -n ${FUNCTIONS_FOLDER}*.c
	clang-format -n ${TEST_FOLDER}*.c
	mv .clang-format ../materials/linters/

fix_clang_format:
	mv ../materials/linters/.clang-format .
	clang-format -i ${FUNCTIONS_FOLDER}*.c
	clang-format -i ${TEST_FOLDER}*.c
	mv .clang-format ../materials/linters/

