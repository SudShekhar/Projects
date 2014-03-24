#include<stdio.h>

int diff(int arr[],int n){
int min=arr[0],max=arr[0];
int ans=0;
int i;
for( i=1;i<n;i++){
if(arr[i] > max)max = arr[i];
if(arr[i] < min) min = arr[i],max = min;

if(max - min > ans)ans = max-min;

}
return ans;
}


int main(){

int n,arr[100];
scanf("%d",&n);
int i;
for( i =0;i<n;i++)
	scanf("%d",&arr[i]);
printf("%d\n",diff(arr,n));

}
