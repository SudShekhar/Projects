#include<stdio.h>
int fun(int num){
	while(num > 0){
	num = num* fun(num-1);
	}
	return num;

}

int main(){
int x=1;
int mask = ~(x<<5 -1);
int i;
for(i=31;i>=0;i--)
{
	if(mask& 1<<i)
		printf("1");
	else printf("0");
}
printf("\n");
printf("%d\n",mask);

printf("%d\n",fun(8));
}

