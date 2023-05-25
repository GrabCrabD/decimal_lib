FLAGS= -Wall -Wextra -Werror
STD= -std=c11
FUNC_MAY = common/s21_add.c common/s21_from_decimal_to_int.c common/s21_from_decimal_to_float.c common/s21_from_int_to_decimal.c common/s21_from_float_to_decimal.c common/s21_mul.c
FUNC = common/s21_negate.c common/s21_sub.c common/s21_is_equal.c common/s21_div.c common/s21_negate.c common/s21_is_less.c common/s21_is_greater_or_equal.c common/s21_is_not_equal.c
FUNC_2 = common/s21_floor.c common/s21_round.c common/s21_truncate.c common/s21_is_greater.c common/s21_is_less_or_equal.c
TEST_MAY = tests/s21_from_int_to_decimal_test.c tests/s21_from_decimal_to_int_test.c tests/s21_mul_test.c tests/s21_from_float_to_decimal_test.c tests/s21_from_decimal_to_float_test.c tests/s21_add_test.c
TEST_2 = tests/s21_sub_test.c tests/s21_is_equal_test.c tests/s21_div_test.c tests/s21_negate_test.c tests/s21_is_less_test.c tests/s21_is_greater_or_equal_test.c tests/s21_is_not_equal_test.c
TEST_3 = tests/s21_floor_test.c tests/s21_round_test.c tests/s21_truncate_test.c tests/s21_is_greater_test.c tests/s21_is_less_or_equal_test.c
GCC_C= gcc -g -Wall -Werror -Wextra -std=c11 -c
LDFLAGS=-lcheck -lm
GCOV_FLAGS= -fprofile-arcs -ftest-coverage -fPIC

all: s21_decimal.a

style:
	clang-format -i -style=google *.c
	clang-format -style=google -n *.c
	
s21_decimal.a: clean
	${GCC_C} -g ${FUNC_MAY} ${FUNC} ${FUNC_2} sup_funcs.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	make clean.o

gs21_decimal.a: clean
	${GCC_C} -g ${FUNC_MAY} ${FUNC} ${FUNC_2} sup_funcs.c ${GCOV_FLAGS}
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	make clean.o

test: s21_decimal.a
	gcc ${FLAGS} ${STD} ${TEST_MAY} ${TEST_2} ${TEST_3} sup_funcs.c tests/main.c s21_decimal.a -o run_tests ${LDFLAGS}
# gcc -c -fprofile-arcs -ftest-coverage s21_decimal.c
# gcc -fprofile-arcs -ftest-coverage s21_decimal.c test.o -lcheck -lm -lpthread -o run_tests -lsubunit -lm
	./run_tests

gcov_report: gs21_decimal.a
		gcc ${FLAGS} ${STD} ${TEST_MAY} ${TEST_2} ${TEST_3} sup_funcs.c tests/main.c s21_decimal.a -o test ${LDFLAGS} ${GCOV_FLAGS}
	./test
	rm -rf *test.gcda *test.gcno main.gc*
	gcovr -p
	mkdir report
	gcovr -p --html-details -o report/report.html
	open report/report.html 
	rm -rf *.gcda *gcno

clean:
	rm -rf *.o *.gcov *.gcno *.gcda test run_tests run_tests_b s21_decimal s21_decimal.a report

clean.o:
	rm -rf *.o
