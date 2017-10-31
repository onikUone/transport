/* ************************************** */
/*           tow2gram.c                   */
/*  makew1gram.sh の出力から              */
/*  単語の2-gramを生成します              */
/*  ＜使い方＞                            */
/*                                        */
/* ************************************** */

/* Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 記号定数の定義 */
#define N 256	/* 単語1-gramのバイト長 */

/* ************************************ */
/*            main()関数                */
/* ************************************ */

int main(){
    char w1[N]="",w2[N]="";	/* 入力された２単語(1-gram) */

    while( scanf("%s",w2)!=EOF ){
        printf("%s -> %s\n",w1,w2);
        strncpy(w1,w2,N);	/* 入力された単語を保存 */
    }
    return 0;
}

