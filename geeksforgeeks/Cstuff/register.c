#include<stdio.h>
#define pi(i) printf("%d\n",i)
int val(){
return 111;
}
int main(){
register int *i;
i= 0;
printf("%d\n",i);
int c=5;
i = &c;
pi(*i);
//register memory cant be read
//register can be used as vars or as pointers

//===========================POINTER===============
int x = 10;
int const* p = &x;
printf("%d\n",*p);
const int j = 14;
//*p =10;

p = &j;
printf("%d\n",j);
//static variables need to be initialized with value;  hence we can't use functions for the same

static int a = 11;

}
