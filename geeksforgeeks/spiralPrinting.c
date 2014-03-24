#include<stdio.h>

void spiral(int arr[][4],int n){
int i,j;
i=0;j=0;
	while(i<n || j < n){
	//first row
	for(;i<n;i++)
		printf("%d ",arr[i][j]);
	i--; //last column
	if(j == n-1)break;
	j++;
	for(;j<n;j++)
		printf("%d ",arr[i][j]);
	//printed first row and column
	j--;//last row
	i--;
	for(;i>=0;i--)
		printf("%d ",arr[i][j]);
	i++;
	j--;
	for(;j>0;j--)
		printf("%d ",arr[i][j]);
	//j goes till 1
	j++;
	i++;
	n--;
	//now j is 1 and i is 1
	}
}


int main(){
int arr[4][4]= {{1,2,3,10},{4,5,6,11},{7,8,9,12},{13,14,15,16}};
spiral(arr,4);


}
