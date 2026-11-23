CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++20 -I. -Itests -g --coverage

EXECUTABLE = all_test


TEST_SOURCES = \
	./tests/list_tests.cc \
	./tests/stack_tests.cc \
	./tests/queue_tests.cc \
	./tests/vector_tests.cc \
	./tests/array_tests.cc \
	./tests/set_tests.cc \
	./tests/map_tests.cc \
	./tests/multiset_tests.cc

UNAME := $(shell uname)

LDFLAGS = -isystem /usr/local/include -pthread -L/usr/local/lib -lgtest -lgtest_main -lpthread -lm -lsubunit --coverage

OPEN_REPORT ?=
LEAKS?=

ifneq ($(findstring Linux,$(UNAME)),)
	OPEN_REPORT += xdg-open
	LEAKS += valgrind --vgdb=no --leak-check=full -s --show-leak-kinds=all --track-origins=yes --verbose
else ifeq ($(UNAME),Darwin)
	OPEN_REPORT += open
	LEAKS += leaks -atExit --
endif

.PHONY: all clean test gcov_report format leaks_check

all: clean test gcov_report

leaks_check: $(EXECUTABLE)
	@$(LEAKS) ./$(EXECUTABLE)

clean:
	@rm -f $(EXECUTABLE) *.gcno *.gcda *.info *~ coverage.*
	@rm -rf coveragereport

$(EXECUTABLE): $(TEST_SOURCES)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

test: $(EXECUTABLE)
	@./$(EXECUTABLE)

gcov_report: test
	@mkdir -p coveragereport
	@lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch,mismatch,mismatch
	@lcov --remove coverage.info \
		'/usr/*' \
		'*/tests/*' \
		--output-file filtered_coverage.info
		--ignore-errors mismatch
	@genhtml filtered_coverage.info --output-directory coveragereport
	@$(OPEN_REPORT) coveragereport/index.html || true

format:
	@clang-format -i \
		tree/*.h tree/*.tpp \
		tests/*.cc \
		set/*.h set/*.tpp \
		multiset/*.h multiset/*.tpp \
		map/*.h map/*.tpp \
		array/*.h array/*.tpp \
		list/*.h list/*.tpp \
		queue/*.h queue/*.tpp \
		stack/*.h stack/*.tpp \
		vector/*.h vector/*.tpp