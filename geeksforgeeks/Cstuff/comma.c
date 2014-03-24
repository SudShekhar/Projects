#include<stdio.h>

int main(){
int x=2;
int y =5;

printf("%d\n",(x,y));
//both operators are evaluated
y = (x++,++x);
printf("%d\n",y);
x = 5;
y = (x++,printf("x = %d\n",x), ++x, printf("x = %d\n",x),x++);

printf("%d\n",y);
printf("%d\n",x);


}
