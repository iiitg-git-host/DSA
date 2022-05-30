#include <stdio.h>
void sort(int a[],int n){
	int i,j,temp;
	for(i=0;i<n;i++){for(j=0;j<n;j++){if(a[i]<a[j]){temp=a[i];a[i]=a[j];a[j]=temp;}}}
}
int main(){
	int n,m;
	printf("Enter length of first array:\n");
	scanf("%d",&m);
	int a[m];
	for(int i=0;i<m;i++){printf("Enter Value:\n");scanf("%d",&a[i]);}
	printf("Enter length of second array:\n");
	scanf("%d",&n);
	int b[n],out[n];	
	for(int j=0;j<n;j++){printf("Enter Value:\n");scanf("%d",&b[j]);}		
	int k=0;
	for(int i=0;i<m;i++){for(int j=0;j<n;j++){if(a[i]==b[j]){out[k]=b[j];b[j]=0;k++;}}}
	sort(b,n);
	for(int i=0;i<n;i++){if(b[i]!=0){out[k]=b[i];k++;}}
	for(int i=0;i<n;i++){printf("%d ",out[i]);}
		

	}
