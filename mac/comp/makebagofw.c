/* ************************** */
/*       makebagofw.c         */
/* ************************** */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define N 1000
#define LENGTH 64

/* ************************** */
/*       main()               */
/* ************************** */
int main(int argc,char *argv[]){
    int n;
    FILE *fpi;
    char inputfile[LENGTH];
    int e;
    int i=0;
    int bagofwords[N]={0};

    if(argc<2){
        fprintf(stderr,"How to use $ makenewvec "
                "n (file_name)\n");
        exit(1);
    }
    fpi=stdin;
    n=atoi(argv[1]);
    if(argc>2){
        strncpy(inputfile,argv[2],LENGTH);
        if( (fpi=fopen(inputfile,"r"))==NULL){
            /* failed */
            fprintf(stderr,"%s:Opening th file is failed.\n",inputfile);
            exit(1);
        }
    }

    while( fscanf(fpi,"%d",&e)!=EOF){
        bagofwords[i]+=e;
        ++i;
        if(i>=n) i=0;
    }

    for(i=0;i<n;++i) printf("%d ",bagofwords[i]);
    printf("\n");

    return 0;
}
