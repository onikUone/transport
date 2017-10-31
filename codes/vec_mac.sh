#!/bin/bash

if [ $# -eq 1 ]
then
    # UTF-8のテキストファイルの分かち書き
    iconv -f UTF-8 -t CP932 $1 |
    extraction.out > mecab.txt;
    echo >> mecab.txt;
    iconv -f CP932 -t UTF-8 mecab.txt |
    mecab -O wakati |
    tr ' ' '\n' > w1gram.txt;
    rm mecab.txt;

    # 1-of-N表現テキスト作成
    makevec.out > vec.txt;
    W_CNT=$(cat w.txt);
    rm w.txt;
    rm w1gram.txt;

    # bag-of-words
    makebagofw.out $W_CNT vec.txt > bagofw.txt;
fi

if [ $# -eq 0 ]
then
    # UTF-8
    iconv -f UTF-8 -t CP932 input.txt |
    extraction.out > mecab.txt;
    echo >> mecab.txt;
    iconv -f CP932 -t UTF-8 mecab.txt |
    mecab -O wakati |
    tr ' ' '\n' > w1gram.txt;
    rm mecab.txt;

    # 1-of-N
    makevec.out > vec.txt;
    W_CNT=$(cat w.txt);
    rm w.txt;
    rm w1gram.txt;

    # bag-of-words
    makebagofw.out $W_CNT vec.txt > bagofw.txt;
fi
