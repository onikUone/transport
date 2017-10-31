#!/bin/bash

.extraction < $1 | iconv -f CP932 -t UTF-8 | mecab -O wakati | sed 's/ /\n/g' | .tow2gram 
