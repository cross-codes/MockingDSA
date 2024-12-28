#!/usr/bin/env sh

if [ "$#" -ne 2 ]; then
	echo "Usage: $0 <day> <part>"
	exit 1
fi

day=$1
part=$2

input_file="./inputs/year2024/day${day}.txt"

if [ ! -f "$input_file" ]; then
	echo "Input file $input_file does not exist"
	exit 1
fi

cat "$input_file" | ./sol.x86_64 ${part}