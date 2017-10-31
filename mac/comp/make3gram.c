/* ********************************************** */
/*               make3gram.c                      */
/*  Shift_JIS漢字コード用文字3-gram生成器         */
/*  Shift_JISで記述されたテキストファイルから     */
/*  全角文字だけを抽出して3-gramを生成する        */
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
#define N 6	/* n-gramの n の２倍 */

/* 関数のプロトタイプ宣言 */
int is2byte(int chr);	/* 全角文字の１バイト目かどうかの判定 */
void put3gram(int chr);	/* 3-gramの出力 */
int invert(int flag);	/* フラグの反転 */
/* ************ */
/*  main()関数  */
/* ************ */

int main(){
    int chr;	/*入力文字 */

/* データを読み込んで１文字ずつ出力する */
    while( (chr=getchar()) != EOF){
        if(is2byte(chr)==TRUE){
            put3gram(chr);	 /* put3gram()に１バイト目送信 */
            put3gram(getchar()); /* put3gram()に２バイト目送信 */
         }
    }
    return 0;
}

/* ********************************** */
/*       invert()関数                 */
/* flagの反転を行う                   */
/* ********************************** */
int invert(int flag){
    if(flag==FALSE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/* ********************************** */
/*    put3gram()関数                  */
/* 3-gramの出力を行う                 */
/* ********************************** */
void put3gram(int c){
    static char queue[N]="      ";	/* 出力用のキュー */
    static int flag=FALSE;		/* 出力タイミング制御フラグ */
    int i;				/* 繰り返し用 */

    for(i=0;i<N-1;++i){
        queue[i]=queue[i+1];	/* キュー内のシフト移動 */
    }
    queue[N-1]=c;		/* キューにデータ追加 */

    if(flag==TRUE){
        for(i=0;i<N;++i){
            putchar(queue[i]);
        }
        putchar('\n');
    }
    flag=invert(flag);
}

/* ********************************** */
/*    is2byte()関数                   */
/* 全角文字の１バイト目かどうかの判定 */
/* ( 0x81～0x9f もしくは 0xe0～0xef ) */
/* ********************************** */
int is2byte(int c){
    if( (c>=0x81)&&(c<=0x9f) || (c>=0xe0)&&(c<=0xef) ){
        return TRUE;	/* ２バイト文字である */
    }
    else{
        return FALSE;	/* １バイト文字である */
    }
}

