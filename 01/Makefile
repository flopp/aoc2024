all: main
	@echo "PART1 - TEST - 11"
	@./main 1 < test.txt
	@echo "PART1 - ?"
	@/usr/bin/time ./main 1 < puzzle.txt
	@echo
	@echo "PART2 - TEST - 31"
	@./main 2 < test.txt
	@echo "PART2 - ?"
	@/usr/bin/time ./main 2 < puzzle.txt

main: main.cpp
	g++ -o $@ -std=c++20 -Wall -Wextra -O3 $<