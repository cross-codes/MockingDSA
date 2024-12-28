#!/usr/bin/env sh

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <day>"
	exit 1
fi

day=$1

input_file="./inputs/year2024/day${day}.txt"

if [ ! -f "$input_file" ]; then
	echo "Input file $input_file does not exist"
	exit 1
fi

echo -n "Part 1: "
cat "$input_file" | ./sol.x86_64 1
echo -n "Part 2: "
cat "$input_file" | ./sol.x86_64 2
