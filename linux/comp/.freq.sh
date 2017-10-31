#!/bin/sh

make3gram < $1 | iconv -f CP932 -t UTF-8 | sort | uniq -c | sed -e 's/^ *//' | sort -r > $2
