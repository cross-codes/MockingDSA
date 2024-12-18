#!/usr/bin/env sh

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <day> <part>"
    exit 1
fi

day=$1
part=$2

input_file="./inputs/Year_2024/Day${day}/Part${part}.txt"

if [ ! -f "$input_file" ]; then
    echo "Input file $input_file does not exist"
    exit 1
fi

cat "$input_file" | java -cp .bin Year_2024.Day${day}.Part${part}