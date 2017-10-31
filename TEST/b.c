#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* 記号定数の定義 */
#define INPUTNO 2
#define HIDDENNO 2
#define ALPHA 10
#define SEED 65535
#define MAXINPUTNO 100
#define BIGNUM 100
#define LIMIT 0.001

/* プロトタイプ宣言 */
double fs(double u);    /*シグモイド関数*/



int main(int argc , char *argv[]){
    double waitH[HIDDENNO][INPUTNO+1];
    double waitO[HIDDENNO+1];
    double teacher[MAXINPUTNO][INPUTNO+1];
    double hide[HIDDENNO+1];
    double output;
    double err = BIGNUM;
    int i,j;
    int no_of_teacher;
    int count=0;

    srand(SEED);

    /* 重みの初期化 */
    init_waitH(waitH);
    init_waitO(waitO);
    /**/

    /* 学習データ読み込み */
    no_of_teacher = getdata(teacher);
    /**/

    /* 学習処理 */
    while(err > LIMIT){
        err = 0.0;
        
        for(j=0; j < no_of_teacher; j++){
            output = forward(waitH , waitO , hide , teacher[j]);
            waitO_learn(waitO , hide , teacher[j] , output);
            waitH_learn(waitH , waitO , hide , teacher[j] , output);
            err += (output - teacher[j][INPUTNO])*(output - teacher[j][INPUTNO]);
            count++;

        }
    }
    /**/


}

/********************/
/* waitH_learn 関数 */
/********************/

void waitH_learn(double waitH[HIDDENNO][INPUTNO+1]
                ,double waitO[HIDDENNO+1]
                ,double hide[]
                ,double teacher[INPUTNO+1]
                ,double output)
{
    int i,j;
    double dj;

    for(j=0 ; j < HIDDENNO ; j++){
        dj = hide[j] * (1 - hide[j]) * waitO[j] * (teacher[INPUTNO] - output) * output * (1 - output);
        for(i=0 ; i < INPUTNO ; i++){
            waitH[j][i] += ALPHA*teacher[i]*dj;
        }
        waitH[j][i] += ALPHA*(-1.0)*dj;
    }
}








