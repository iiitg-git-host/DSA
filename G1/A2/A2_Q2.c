#include <stdio.h>

int find(int x, int a[],int n){
	for(int e=0;e<n;e++){if(a[e]==x){return 1;}}
	return 0;
}

void sort(int a[],int n){
	int i,j,temp;
	for(i=0;i<n;i++){for(j=0;j<n;j++){if(a[i]<a[j]){temp=a[i];a[i]=a[j];a[j]=temp;}}}
}

int main(){
	printf("Enter no. of rows:\n");
	int rows,cols;
	scanf("%d",&rows);
	printf("Enter no. of columns:\n");
	scanf("%d",&cols);
	int a[rows][cols];
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			printf("Enter value:\n");
			int temp;
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			printf("%d ",a[i][j]);
		}
	printf("\n");
	}
	int x;
	printf("Enter number to find\n");	
	scanf("%d",&x);
	int flag=0;int n,m;
	for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){if(x==a[i][j]){m=i;n=j;flag=1;break;}}}
	int len;	
	if((m==rows-1 &&(n==0||n==cols-1))||(m==0 && (n==0||n==cols-1))){len=3;}
	else if(m==rows-1 || m==0 || n==0 || n==cols-1){len=5;}else{len=8;}
	int ne[len];
	for(int i=0;i<len;i++){for(int j=m-1;j<m+2;j++){for(int k=n-1;k<n+2;k++){if(j>=0 && k>=0 && j<rows && k<cols && !(j==m && k==n)){if(find(a[j][k],ne,len)==1){continue;}else{ne[i]=a[j][k];}}}}}
	sort(ne,len);	
	for(int i=0;i<len;i++){printf("%d ",ne[i]);}

}
	
	

