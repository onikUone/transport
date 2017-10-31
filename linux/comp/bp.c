/* ******************************************* */
/*                 bp.c                        */
/* ******************************************* */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define INPUTNO 2   /* 入力層の数 */
#define HIDDENNO 2  /* 中間層の数 */
#define ALPHA 5    /* 学習係数 */
//#define SEED 65535  /* 乱数用シード */
#define SEED 6555  /* 乱数用シード */
#define MAXINPUTNO 100 /* 学習データの最大個数 */
#define BIGNUM 100  /* 誤差の初期値 */
#define LIMIT 0.001 /* 誤差の許容値 */

/* 関数のプロトタイプ宣言 */
double fs(double u);
void initwh(double wh[HIDDENNO][INPUTNO+1]);
void initwo(double wo[HIDDENNO+1]);
double drnd(void);

void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1]);

double forward(double wh[HIDDENNO][INPUTNO+1]
              ,double wo[HIDDENNO+1]
              ,double hi[]
              ,double e[INPUTNO+1]);

void olearn(double wo[HIDDENNO+1]
           ,double hi[]
           ,double e[INPUTNO+1]
           ,double o);

int getdata(double e[][INPUTNO+1]);

void hlearn(double wh[HIDDENNO][INPUTNO+1]
           ,double wo[HIDDENNO+1]
           ,double hi[]
           ,double e[INPUTNO+1]
           ,double o);


/* ******************************************* */
/*           main()                            */
/* ******************************************* */
int main(){
    double wh[HIDDENNO][INPUTNO+1];
    double wo[HIDDENNO+1];

    double e[MAXINPUTNO][INPUTNO+1];
    double hi[HIDDENNO+1];
    double o;
    double err=BIGNUM;
    int i,j;
    int n_of_e;
    int count=0;

    /* 乱数初期化 */
    srand(SEED);
    /* 重みの初期化 */
    initwh(wh);
    initwo(wo);
    print(wh,wo);   /* 重み初期値の出力 */

    /* 学習データ読み込み */
    n_of_e = getdata(e);
    printf("学習データの個数:%d\n",n_of_e);

    /* 学習プロセス */
    while(err > LIMIT){ /* 誤差が許容範囲になるまで繰り返す */
        err=0.0;
        for(j=0;j<n_of_e;++j){
            /*順方向計算*/
            o = forward(wh,wo,hi,e[j]);
            /*出力層の重み調整*/
            olearn(wo,hi,e[j],o);
            /*中間層の重み調整*/
            hlearn(wh,wo,hi,e[j],o);
            /*誤差の積算*/
            err += (o-e[j][INPUTNO])*(o-e[j][INPUTNO]);
        }
        ++count;
        fprintf(stderr,"%d\t%lf\n",count,err);
    } /*学習終了*/

    /*結合荷重の出力*/
    print(wh,wo);

    /*学習データに対する出力*/
    for(i=0 ; i < n_of_e ; ++i){
        printf("%d ",i);
        for(j=0 ; j < INPUTNO+1 ; ++j)
            printf("%lf ",e[i][j]);
        o = forward(wh,wo,hi,e[i]);
        printf("%lf\n",o);
    }
    
    return 0;
}



/* ******************************************* */
/*            hlearn()                         */
/* ******************************************* */
void hlearn(double wh[HIDDENNO][INPUTNO+1]
           ,double wo[HIDDENNO+1]
           ,double hi[]
           ,double e[INPUTNO+1]
           ,double o)
/*hlearn*/{
    int i,j;
    double dj;

    for(j=0 ; j < HIDDENNO ; ++j){
        dj = hi[j] * (1-hi[j]) * wo[j] * (e[INPUTNO]-o) * o * (1-o) ;
        for(i=0 ; i < INPUTNO ; ++i){
            wh[j][i] += ALPHA * e[i] * dj;
        }
        wh[j][i] += ALPHA * (-1.0) * dj;
    }
}


/* ******************************************* */
/*         getdata()                           */
/* ******************************************* */
int getdata(double e[][INPUTNO+1]){
    int n_of_e = 0;
    int i=0;

    while( scanf("%lf" , &e[n_of_e][i])!=EOF ){
        ++i;
        if(i > INPUTNO){
            i=0;
            ++n_of_e;
        }
    }

    return n_of_e;
}



/* ******************************************* */
/*         olearn()                            */
/* ******************************************* */
void olearn(double wo[HIDDENNO+1]
           ,double hi[]
           ,double e[INPUTNO+1]
           ,double o)
/*olearn*/{
    int i;
    double d;

    d = (e[INPUTNO]-o) * o * (1-o);
    for(i=0 ; i < HIDDENNO ; ++i){
        wo[i] += ALPHA * hi[i] * d;
    }
    wo[i] += ALPHA * (-1.0) * d;
}


/* ******************************************* */
/*      forward()                              */ 
/* ******************************************* */
double forward(double wh[HIDDENNO][INPUTNO+1]
              ,double wo[HIDDENNO+1]
              ,double hi[]
              ,double e[INPUTNO+1])
/*forward*/{
    int i,j;
    double u;
    double o;

    /*hiの計算*/
    for(i=0 ; i < HIDDENNO ; ++i){
        u=0;
        for(j=0 ; j < INPUTNO ; ++j){
            u += e[j] * wh[i][j];
        }
        u -= wh[i][j];
        hi[i] = fs(u);
    }

    /* oの計算*/
    for(i=0 ; i < HIDDENNO ; ++i){
        o += hi[i] * wo[i];
    }
    o -= wo[i];

    return fs(o);
}


/* ******************************************* */
/*      print()                                */
/* ******************************************* */
void print(double wh[HIDDENNO][INPUTNO+1] , double wo[HIDDENNO+1]){
    int i,j;

    printf("中間層の重み出力\n");
    for(i=0 ; i < HIDDENNO ; ++i){
        for(j=0 ; j < INPUTNO+1 ; ++j){
            printf("%lf ",wh[i][j]);
        }
        printf("\n");
    }

    printf("出力層の重み出力\n");
    for(i=0 ; i < HIDDENNO+1 ; ++i) printf("%lf ",wo[i]);
    printf("\n");
}


/* ******************************************* */
/*         initwh()                            */
/* ******************************************* */
void initwh(double wh[HIDDENNO][INPUTNO+1]){
    int i,j;

    for(i=0 ; i < HIDDENNO ; ++i)
        for(j=0 ; j < INPUTNO+1 ; ++j)
            wh[i][j]=drnd();
}


/* ******************************************* */
/*            initwo()                         */
/* ******************************************* */
void initwo(double wo[HIDDENNO+1]){
    int i;
    for(i=0 ; i < HIDDENNO+1 ; ++i)
        wo[i]=drnd();
}



/* ******************************************* */
/*              drnd()                         */
/* ******************************************* */
double drnd(void){
    double rndno;
    
    while( (rndno=(double)rand()/RAND_MAX)==1.0);
    rndno = rndno * 2 -1;
    return rndno;
}


/* ******************************************* */
/*         fs()                                */
/* ******************************************* */
double fs(double u){
    return 1.0/(1.0 + exp(-u) );
}

