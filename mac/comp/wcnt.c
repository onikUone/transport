/* ************************** */
/*         wcnt.c             */
/* ************************** */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define LENGTH 64
#define INPUTFILE "voc.txt"
#define OUTPUTFILE "w.txt"

/* ************************** */
/*         main()             */
/* ************************** */
int main(int argc,char *argv[]){
    FILE *fpi,*fpo;
    char inputfile[LENGTH]=INPUTFILE;
    char outputfile[LENGTH]=OUTPUTFILE;
    int cnt=0;
    int i=0;
    char word[LENGTH*10];

    if(argc>=2) strncpy(inputfile,argv[1],LENGTH);
    if(argc>=3) strncpy(outputfile,argv[2],LENGTH);

    if( (fpi=fopen(inputfile,"r"))==NULL){
        fprintf(stderr,"%s:Opening the file is failed.\n",inputfile);
        exit(1);
    }
    if( (fpo=fopen(outputfile,"w"))==NULL){
        fprintf(stderr,"%s:Opening the file is failed.\n",outputfile);
        exit(1);
    }
    
    while( fscanf(fpi,"%s",word)!=EOF){
        ++i;
    }

    fprintf(fpo,"%d",i);

    return 0;
}
