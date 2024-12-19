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

cat "$input_file" | /usr/lib/jvm/java-1.8.0/bin/java \
-cp .bin \
-ea \
-XX:+UseSerialGC \
-XX:TieredStopAtLevel=1 \
-XX:NewRatio=5 \
-Xms8M \
-Xmx512M \
-Xss64M \
-DCROSS_DEBUG=true \
-Dcom.sun.management.jmxremote.port=8080 \
-Dcom.sun.management.jmxremote.authenticate=false \
-Dcom.sun.management.jmxremote.ssl=false \
Year_2024.Day${day}.Part${part}