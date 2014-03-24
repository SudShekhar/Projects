#include<stdio.h>
#include<stdlib.h>
void sz(int *a){
printf("%d\n",sizeof(a)/sizeof(a[0]));


}


int main(){
int arr[10];
int *temp = (int*)malloc(sizeof(int) * 3);

sz(arr);
sz(temp);

}
