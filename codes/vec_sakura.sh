#!/bin/bash

if [ $# -eq 1 ]
then
    # UTF-8のテキストファイルの分かち書き
    iconv -f UTF-8 -t CP932 $1 |
    extraction |
    iconv -f CP932 -t UTF-8 |
    mecab -O wakati |
    sed 's/ /\n/g' > w1gram.txt;
    
    # 1-of-N表現テキスト作成
    makevec > vec.txt;
    W_CNT=$(cat w.txt);
    rm w.txt;
    rm w1gram.txt;

    # bag-of-words
    makebagofw $W_CNT vec.txt > bagofw.txt;
fi

if [ $# -eq 0 ]
then
    # UTF-8
    iconv -f UTF-8 -t CP932 input.txt |
    extraction |
    iconv -f CP932 -t UTF-8 |
    mecab -O wakati |
    sed 's/ /\n/g' > w1gram.txt;

    # 1-of-N
    makevec > vec.txt;
    W_CNT=$(cat w.txt);
    rm w.txt;
    rm w1gram.txt;

    # bag-of-words
    makebagofw $W_CNT vec.txt > bagofw.txt;
fi
