#include <stdio.h>

void mztb(int arr[],int n){
	for(int i=0;i<n;i++){if(arr[i]==0){for(int j=i+1;j<n;j++){if(arr[j]!=0){int temp=arr[i];arr[i]=arr[j];arr[j]=temp;}}}}
}

int main(){
	int n;
	printf("Enter no. of elements:");
	scanf("%d",&n);
	printf("\n");
	int a[n];
	for(int i=0;i<n;i++){
	printf("Enter element:");
	scanf("%d",&a[i]);
	}
	mztb(a,n);
	for(int k=0;k<n;k++){
	printf("%d ",a[k]);	
	}
	printf("\n");
	
}
