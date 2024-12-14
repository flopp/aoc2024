all: | part1 part2

part1: main
	@echo "PART1 - TEST - "
	@./main 1 11 7 < test.txt
	@echo "PART1 - ?"
	@/usr/bin/time ./main 1 101 103 < puzzle.txt

part2: main
	@echo "PART2 - ?"
	@/usr/bin/time ./main 2 101 103 < puzzle.txt
	
main: main.cpp
	g++ -o $@ -std=c++20 -Wall -Wextra -O3 $<