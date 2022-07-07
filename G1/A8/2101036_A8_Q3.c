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

int findMaxInArray(int array[], int size){
	int max = array[0];
	int maxFreq = 0;
	for(int i=0;i<size;i++){
		int startIndex = i;
		int count =0;
		while(array[startIndex]==array[i]){count++;i++;}
		i--;
		// printf("Element %d freq %d\n",array[i],count);
		if(count>maxFreq){maxFreq=count;max = array[startIndex];}		
	}
	return max;
}

int main(){
	int size;
	printf("Enter Size of Array\n");
	scanf("%d",&size);
	int A[size];
	for(int i = 0 ;i<size;i++){
		printf("Enter element in Array A at index %d \n",i);
		scanf("%d",&A[i]);		
	}		
	quickSort(A, size-1, 0);
	for(int i = 0 ;i<size;i++){
		printf("%d ",A[i]);
	}	
	printf("\n");
	printf("%d\n",findMaxInArray(A,size));	
}
