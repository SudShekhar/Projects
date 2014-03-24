#include<stdio.h>

int main(){
unsigned int x = -1;
int y =~0;
printf("%u,%d",x,y);
if(x == y)
	printf("same\n");
else printf("no\n");
}
