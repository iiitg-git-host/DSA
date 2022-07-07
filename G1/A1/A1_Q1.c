#include <stdio.h>

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
	int even=0,odd=0;
	for(int i=0;i<n;i++){if (a[i]%2==0){even++;}else{odd++;}}
	printf("No. of even elements : %d , No. of odd elements: %d\n",even,odd);
}
