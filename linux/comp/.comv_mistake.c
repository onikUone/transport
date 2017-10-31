/* ****************************** */
/*           conv.c               */
/*     畳み込み処理               */
/*   1-of-Nテキストを読み取り、   */
/* 　畳み込みを施す               */
/*  ＜使い方＞                    */
/*   $ conv < data1.txt           */
/* ****************************** */

/* Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* 記号定数の定義  */
#define VOCSIZE 8      /* 1-of-N表現の語彙数(要素数) */
#define WORDLEN 10       /* 1-of-N表現の単語の連鎖数 */
#define FILTERSIZE 3    /* フィルタの大きさ */

/* 関数のプロトタイプ宣言 */

/* 畳み込み処理関数 */
void conv(double filter[][FILTERSIZE]
         ,double sentence[][VOCSIZE]
         ,double convout[][VOCSIZE]);

/* フィルタの適用 */
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE]
               ,int i ,int j);

/* 畳み込み出力 */
void convres(double convout[][VOCSIZE]);

/* データ読み込み */
void getdata(double sentence[][VOCSIZE]);


/* ****************************** */
/*       main()                   */
/* ****************************** */
int main(){
    double filter[FILTERSIZE][FILTERSIZE]
        ={ {1,0,0},{0,1,0},{0,0,1} }; /* 順接フィルタ */
//        ={ {1,0,0},{1,0,0},{1,0,0} }; /* 連続フィルタ */

    double sentence[WORDLEN][VOCSIZE];      /* 入力テキスト */
    double convout[WORDLEN][VOCSIZE]={0};   /* 畳み込み出力 */


/* 入力テキストの読み込み */
    getdata(sentence);
/* 畳み込み処理 */
    conv(filter,sentence,convout);
/* 結果の出力 */
    convres(convout);

    return 0;
}


/* ****************************** */
/*     convres()                  */
/*   畳み込みの結果出力           */
/* ****************************** */
void convres(double convout[][VOCSIZE]){
    int i,j;
    int startpoint=FILTERSIZE/2; /* 出力範囲の下限 */

    for(i=startpoint; i<WORDLEN-1; ++i){
        for(j=startpoint; j<VOCSIZE-1; ++i){
            printf("%.3lf ",convout[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


/* ****************************** */
/*     getdata()                  */
/*  入力テキストの読み込み        */
/* ****************************** */
void getdata(double e[][VOCSIZE]){
    int i=0,j=0;

    while( scanf("%lf",&e[i][j])!=EOF ){
        ++j;
        if(j>=VOCSIZE){
            j=0;
            ++i;
            if(i>=WORDLEN) break; /* 読み込み終了 */
        }
    }
}


/* ****************************** */
/*     conv()                     */
/*  畳み込み処理                  */
/* ****************************** */
void conv(double filter[][FILTERSIZE]
         ,double sentence[][VOCSIZE]
         ,double convout[][VOCSIZE])
{
    int i=0,j=0;
    int startpoint=FILTERSIZE/2;

    for(i=startpoint ; i<WORDLEN-startpoint ; ++i){
        for(j=startpoint ; j<VOCSIZE-startpoint ; ++j){
            convout[i][j]=calcconv(filter,sentence,i,j);
        }
    }
}


/* ****************************** */
/*   calcconv()                   */
/* フィルタをかける               */
/* ****************************** */
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE]
               ,int i,int j)
{
    int m,n;
    double sum=0;

    for(m=0 ; m<FILTERSIZE ; ++m){
        for(n=0 ; n<FILTERSIZE ; ++n){
            sum += sentence[i-FILTERSIZE/2+m][j-FILTERSIZE/2+n]*filter[m][n];
        }
    }

    return sum;
}

