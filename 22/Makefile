all: | part1 part2

part1: main
	@echo "PART1 - TEST - 37327623"
	@./main 1 < test.txt
	@echo "PART1 - ?"
	@/usr/bin/time ./main 1 < puzzle.txt

part2: main
	@echo "PART2 - TEST - "
	@./main 2 < test.txt
	@echo "PART2 - ?"
	@/usr/bin/time ./main 2 < puzzle.txt
	
main: main.cpp
	g++ -o $@ -std=c++20 -Wall -Wextra -O3 $<