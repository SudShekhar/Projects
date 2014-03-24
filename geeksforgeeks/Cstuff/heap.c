#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
int main(){
foo();
return;
}

void rec(char* name){

assert(name!=NULL);

}
void foo(){
printf("ih\n");
rec(NULL);
}
