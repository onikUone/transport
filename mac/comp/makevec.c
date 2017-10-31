/* ********************************************* */
/*              makevec.c                        */
/*                                               */
/*  単語1-gramで分かち書きされたテキストから     */
/*  1-of-N表現を生成するプログラム               */
/*  ＜使い方＞                                   */
/*  $ makevec （引数）                           */
/*     + 引数には入出力ファイルを指定する        */
/*     + 第一引数 入力ファイル(単語1-gram)       */
/*         - 引数の指定がない場合はw1gram.txt    */
/*     + 第二引数 単語語彙を格納するファイル     */
/*         - 引数の指定がない場合はvoc.txt       */
/*                                               */
/* ********************************************* */

/* Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 記号定数の定義 */
#define TRUE 1
#define FALSE 0
#define LENGTH 64	/* １単語の長さの上限 */
#define N 5000		/* 単語数の上限（ベクトル空間の上限） */
#define INPUTFILE "w1gram.txt"	/* デフォルト入力ファイル名 */
#define OUTPUTFILE "voc.txt"	/* デフォルト出力ファイル名 */
#define COUNTFILE "w.txt"       /* デフォルト単語数ファイル名 */

/* 関数のプロトタイプ宣言 */
int isnew(char word[],char dictionary[][LENGTH],int n);
	/* 新規単語判別 */
void putvec(char word[],char dictionary[][LENGTH],int n);
	/* 1-of-N出力 */

/* ********************************* */
/*          main()関数               */
/* ********************************* */
int main(int argc,char *argv[]){
    char word[LENGTH*10];	/* 単語の読み込み用 */
    char dictionary[N][LENGTH];	/* 単語を登録する辞書 */
    int n=0;			/* 単語の種類数 */
    FILE *fpi,*fpo,*fpcnt;		/* ファイルポインタ */
    char inputfile[LENGTH]=INPUTFILE;	/* 入力ファイル名 */
    char outputfile[LENGTH]=OUTPUTFILE;	/* 出力ファイル名 */

/* 入力ファイル名の設定 */
    if(argc>=2) strncpy(inputfile,argv[1],LENGTH);  /* 入力ファイル指定の有無 */
    if(argc>=3) strncpy(outputfile,argv[2],LENGTH); /* 出力ファイル指定の有無 */

/* 入力ファイルのオープン */
    if( (fpi=fopen(inputfile,"r"))==NULL ){
        /* ファイルオープン失敗 */
        fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile);
        exit(1);
    }

/* 出力ファイルのオープン */
    if( (fpo=fopen(outputfile,"w"))==NULL ){
        /* ファイルオープン失敗 */
        fprintf(stderr,"%s:ファイルオープン失敗\n",outputfile);
        exit(1);
    }

/* 単語数ファイルのオープン */
    if( (fpcnt=fopen(COUNTFILE,"w"))==NULL ){
        /* ファイルオープン失敗 */
        fprintf(stderr,"%s:ファイルオープン失敗\n",COUNTFILE);
        exit(1);
     }

/* データを読み込んで辞書に登録 */
    while( fscanf(fpi,"%s",word)!=EOF ){
        if( isnew(word,dictionary,n)==TRUE){
            strncpy(dictionary[n],word,LENGTH);	/* 単語登録 */
            ++n;
        }
    }
    fprintf(stderr,"単語数 %d\n",n);
    fprintf(fpcnt,"%d",n);
    rewind(fpi);	/* ファイル先頭に巻き戻す */

/* 1-of-N表現の出力 */
    while( fscanf(fpi,"%s",word)!=EOF ){
        putvec(word,dictionary,n);	/* 出力 */
    }

/* 語彙のファイル出力 */
    int i;
    for(i=0;i<n;++i){
        fprintf(fpo,"%s\n",dictionary[i]);
    }
    
    return 0;
}

/* ******************************** */
/*         putvec()関数             */
/*  1-of-N表現の出力                */
/* ******************************** */
void putvec(char word[],char dictionary[][LENGTH],int n){
    int i;
    for(i=0;i<n;++i){
        if( (strncmp(word,dictionary[i],LENGTH)==0) && (strlen(word)==strlen(dictionary[i])) ){
            printf("1");
        }
        else{
            printf("0");
        }
        printf(" ");
    }
    printf("\n");	/* ベクトルの区切り */
}

/* **************************************** */
/*             isnew()関数                  */
/*    新規単語かどうかの判定                */
/* **************************************** */
int isnew(char word[],char dictionary[][LENGTH],int n){
    int i;
    for(i=0;i<n;++i){
        if( (strncmp(word,dictionary[i],LENGTH)==0) && (strlen(word)==strlen(dictionary[i])) ){
            break;	/* 既登録 */
        }
    }
    if(i<n){
        return FALSE;
    }
    
    return TRUE;
}

