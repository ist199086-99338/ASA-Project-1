C = g++
CFLAGS = -std=c++11 -O3 -pedantic -Wall -Wextra -Werror
CDEBUG = -std=c++11 -O0 -g -pedantic -Wall -Wextra -Werror
TEST_INPUTS := $(wildcard tests/test-*.in)
GREEN=$(shell tput setaf 2)
RED=$(shell tput setaf 1)
RESET=$(shell tput op)
OK="$(GREEN)> test $* PASSED$(RESET)"
KO="$(RED)> test $* FAILED$(RESET)"
CLEAN="$(GREEN)> Everything was cleaned$(RESET)"
EXEC="$(GREEN)> Executable at ./main.o$(RESET)"

.PHONY: do test $(TEST_INPUTS)

do: src/main.cpp
	@$(C) $(CFLAGS) src/* -o main.o
	@echo $(EXEC)

clean: 
	@rm -f main.o tests/*.diff
	@echo $(CLEAN)

test: $(TEST_INPUTS)

$(TEST_INPUTS): tests/test-%.in: ./main.o
	@./$< < $@ | diff - tests/test-$*.out > tests/test-$*.diff || exit 0
	@if [ `wc -l < tests/test-$*.diff` -eq 0 ]; then echo $(OK) & rm tests/test-$*.diff; else echo $(KO); fi;

