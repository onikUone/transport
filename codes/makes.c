/* *************************************** */
/*           makes.c                       */
/* *************************************** */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define LENGTH 64
#define N 10000
#define VOCFILE "voc.txt"

/* *************************************** */
/*            main()                       */
/* *************************************** */
int main(int argc,char *argv[]){
    char word[LENGTH*10];
    char dictionary[N][LENGTH];
    int n=0;
    FILE *fpvoc,*fpi;
    char inputfile[LENGTH];
    char vocfile[LENGTH]=VOCFILE;
    int e;
    int i;

    fpi=stdin;
    if(argc>=2) strncpy(vocfile,argv[1],LENGTH);
    if(argc>=3) strncpy(inputfile,argv[2],LENGTH);

    if( (fpvoc=fopen(vocfile,"r"))==NULL){
        /* failed */
        fprintf(stderr,"%s:Opening the file is failed.\n",vocfile);
        exit(1);
    }

    if( (argc>=3)&&(fpi=fopen(inputfile,"r"))==NULL ){
        /* failed */
        fprintf(stderr,"%s:Opening the file is failed.\n",inputfile);
        exit(1);
    }

    while( fscanf(fpvoc,"%s",word)!=EOF ){
        strncpy(dictionary[n],word,LENGTH);
        ++n;
    }

    printf("Words : %d\n",n);

    i=0;
    while( fscanf(fpi,"%d",&e)!=EOF ){
        if(e==1) printf("%s",dictionary[i]);
        ++i;
        if(i>=n) i=0;
    }
    
    return 0;
}
