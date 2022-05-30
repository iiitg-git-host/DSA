#include <stdio.h>
int checksub(int arr[],int n,int sub[],int m){
	int start=sub[0];
	int allflag=0;
	for(int i=0;i<n;i++){
		if(arr[i]==start){int flag=1;for(int j=1;j<m;j++){if(sub[j]!=arr[i+j]){flag=0;break;}}allflag=flag;}
		if(allflag==1){break;}
		
	}return allflag;
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
	int m;
	printf("Enter no. of elements:");
	scanf("%d",&n);
	printf("\n");
	int b[n];
	for(int i=0;i<n;i++){
	printf("Enter element:");
	scanf("%d",&b[i]);
	}
	if(checksub(a,n,b,m)==1){printf("sub");}else{printf("not sub");}
	
	
}
