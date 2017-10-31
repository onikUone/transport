#include<stdio.h>

void change(int b[]){
    b[0]=3;
    b[1]=4;
    return;
}

int main(){
    int a[2];
    a[0]=1;
    a[1]=2;
    printf("a[0] = %d , a[1] = %d\n",a[0],a[1]);
    change(a);
    printf("a[0] = %d , a[1] = %d\n",a[0],a[1]);
    return 0;
}
