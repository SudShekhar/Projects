#include<stdio.h>

void merge(int arr[],int arr1[], int n,int m){
int i=0,j=0;
while(i < n && j < m){
	if(arr[i] < arr1[j])
	{
		fprintf(stderr,"%d ",arr[i]);
		i++;
	}
	else if (arr[i] > arr1[j]){
		fprintf(stderr,"%d ",arr1[j]);
		j++;
	
	}
	else if (arr[i]==arr1[j]){
		fprintf(stderr,"%d ",arr[i]);
		i++,j++;
	}

}
while(i < n)printf("%d ",arr[i++]);
while(j < m)printf("%d ",arr1[j++]);

return;
}

int main(){
int arr[] = {1,2,4,6,8};
int arr1[] = {3,5,6,7};

merge(arr,arr1,4,4);

}
