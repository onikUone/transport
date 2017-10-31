#!/bin/bash

iconv -f UTF-8 -t CP932 $1 | extraction | iconv -f CP932 -t UTF-8 | mecab -O wakati | sed 's/ /\n/g'
