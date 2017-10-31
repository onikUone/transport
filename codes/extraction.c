/* ********************************************** */
/*               extraction.c                     */
/*  Shift_JIS漢字コード用全角 文字抽出器          */
/*  Shift_JISで記述されたテキストファイルから     */
/*  全角文字だけを抽出する。                      */
/* ＜使い方＞                                     */
/*  ./a.out < input > output                      */
/* ********************************************** */

/* Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

/* 記号定数の定義 */
#define TRUE 1
#define FALSE 0

/* 関数のプロトタイプ宣言 */
int is2byte(int chr); /* 全角文字の１バイト目かどうかの判定 */

/* ************ */
/*  main()関数  */
/* ************ */

int main(){
    int chr;	/*入力文字 */

/* データを読み込んで１文字ずつ出力する */
    while( (chr=getchar()) != EOF){
        if(is2byte(chr)==TRUE){
            putchar(chr);	/* １バイト目出力 */
            putchar(getchar());	/* ２バイト目を読み込んで出力 */
        }
    }
    return 0;
}

/* ********************************** */
/*    is2byte()関数                   */
/* 全角文字の１バイト目かどうかの判定 */
/* ( 0x81～0x9f もしくは 0xe0～0xef ) */
/* ********************************** */
int is2byte(int c){
    if( ((c >= 0x81)&&(c <= 0x9f)) || ((c >= 0xe0)&&(c <= 0xef)) ){
        return TRUE;	/* ２バイト文字である */
    }
    else{
        return FALSE;	/* １バイト文字である */
    }
}


