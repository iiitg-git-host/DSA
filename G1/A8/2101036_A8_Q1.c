#include <stdio.h>
void swap(int array[], int first, int second){
	int temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}
int partition(int array[],int upperBound, int lowerBound){
	int pivot = lowerBound;
	int up = upperBound , low = lowerBound;
	while(low<up){
		while(array[pivot]<array[up]){up--;}
		while(array[pivot]>=array[low]){low++;}
		if(low<up){
			swap(array,low,up);			
		}
	}
	swap(array,pivot,up);
	return up;
}
void quickSort(int array[], int upperBound, int lowerBound){
	
	int pivot  = partition(array,  upperBound, lowerBound);
	if(lowerBound<pivot-1){quickSort(array, pivot-1, lowerBound);}
	if(pivot+1<upperBound){quickSort(array, upperBound, pivot+1);}
}

int binarySearch(int array[], int low, int high, int x){
	if(low<=high){
		int mid =low+(high-low)/2;
		if(x==array[mid]){return 1;}
		if(x<array[mid]){return binarySearch(array,low,mid-1,x);}
		if(x>array[mid]){return binarySearch(array,mid+1,high,x);}
	}	
	else{return 0;}
}

int find(int A[], int B[], int K, int size){
	for(int i=0;i<size;i++){
		int temp = K-A[i];
		if(binarySearch(B,0,size-1,temp)==1){return 1;}
	}
	return 0;
}

int main(){
	int size;
	printf("Enter Size of Array\n");
	scanf("%d",&size);
	int A[size];
	int B[size];
	for(int i = 0 ;i<size;i++){
		printf("Enter element in Array A at index %d \n",i);
		scanf("%d",&A[i]);		
	}
	for(int i = 0 ;i<size;i++){
		printf("Enter element in Array B at index %d \n",i);
		scanf("%d",&B[i]);
	}		
	quickSort(A, size-1, 0);
	quickSort(B, size-1, 0);
	int K;
	printf("Enter Value Of K\n");
	scanf("%d",&K);
	int flag = find(A,B,K,size);	
	if(flag==1){printf("exists\n");}
	else{printf("doesnt\n");}	
	
	
}
