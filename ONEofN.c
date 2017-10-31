#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define LENGTH 64
#define N 5000
#define VOC "voc_sample.txt"
#define VEC "vec_sample.txt"

/* プロトタイプ宣言 */
int isnew(char word[],char dictionary[][LENGTH],int n);
void putvec(char word[],char dictionary[][LENGTH],int n,FILE *fpvec);

/* main関数 */
int main(int argc , char *argv[]){
    char word[LENGTH*10];
    char dictionary[N][LENGTH];
    int n=0;
    FILE *fpi,*fpvoc,*fpvec;
    char vocfile[LENGTH]=VOC;
    char vecfile[LENGTH]=VEC;
    char inputfile[LENGTH];
    strncpy(inputfile , argv[1] , LENGTH);

    /* ファイルオープン */
    if( (fpi=fopen(inputfile,"r")) == NULL){
        fprintf(stderr , "%s:ファイルオープン失敗\n" , inputfile);
        exit(1);
    }
    if( (fpvoc=fopen(vocfile,"w")) == NULL){
        fprintf(stderr , "%s:ファイルオープン失敗\n" , vocfile);
        exit(1);
    }
    if( (fpvec=fopen(vecfile,"w")) == NULL){
        fprintf(stderr , "%s:ファイルオープン失敗\n" , vecfile);
        exit(1);
    }

    /* 語彙データ作成 */
    while( fscanf(fpi,"%s",word) != EOF ){
        if(isnew(word,dictionary,n)){
            strncpy(dictionary[n],word,LENGTH);
            n++;
        }
    }
    int i;
    for(i=0;i<n;i++){
        fprintf(fpvoc,"%s\n",dictionary[i]);
    }
    rewind(fpi);

    /* 1-of-Nデータ作成 */
    while( fscanf(fpi,"%s",word) != EOF){
       putvec(word,dictionary,n,fpvec); 
    }

    fclose(fpi);
    fclose(fpvoc);
    fclose(fpvec);
    return 0;
}

/* putvec関数 */
void putvec(char word[] , char dictionary[][LENGTH] , int n , FILE *fpvec){
    int i;

    for(i=0;i<n;i++){
        if( (strncmp(word,dictionary[i],LENGTH)==0) && (strlen(word)==strlen(dictionary[i])) ){
            fprintf(fpvec,"1");
        }
        else{
            fprintf(fpvec,"0");
        }
        fprintf(fpvec," ");
    }
    fprintf(fpvec,"\n");
}

/* isnew関数 */
int isnew(char word[] , char dictionary[][LENGTH] , int n){
    int i;

    for(i=0;i<n;i++){
        if( (strncmp(word,dictionary[i],LENGTH)==0) && (strlen(word)==strlen(dictionary[i])) ){
            break;
        } 
    }
    if(i<n){
        return FALSE;
    }
    return TRUE;
}

