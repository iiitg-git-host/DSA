#include <stdio.h>
void swap(int array[], int first, int second){
	int temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}
void bubbleSort(int array[], int size, int *swapCount){
	for(int m = 0;m<size;m++){
		for(int i=0;i<size-1;i++){
			if(array[i]>array[i+1]){
				swap(array, i,i+1);
				(*swapCount)++;
			}
		}
	}
}
void insertionSort(int array[], int size, int *swapCount){
	for(int m=1;m<size;m++){
		int j=m;
		int i=m-1;
		while(i>=0 && array[i]>array[j]){
			swap(array,i--,j--);(*swapCount)++;
		}
	}
	
}
void selectionSort(int array[], int size, int *swapCount){
	for(int m = 0;m<size-1;m++){
		int min = m;
		for(int i=m+1;i<size-1;i++){
			if(array[i]<array[min]){min = i;}
		}	
		swap(array,min,m);(*swapCount)++;
	}
}
int partition(int array[], int lowerBound, int upperBound, int *swapCount){
	int pivot = lowerBound;
	int up = upperBound , low = lowerBound;
	while(low<up){
		while(array[pivot]<array[up]){up--;}
		while(array[pivot]>=array[low]){low++;}
		if(low<up){
			swap(array,low,up);	
			(*swapCount)++;		
		}
	}
	swap(array,pivot,up);
	(*swapCount)++;
	return up;
}
void quickSort(int array[], int lowerBound, int upperBound, int *swapCount){
	int pivot  = partition(array,  lowerBound, upperBound, swapCount);
	if(lowerBound<pivot-1){quickSort(array, lowerBound, pivot-1, swapCount);}
	if(pivot+1<upperBound){quickSort(array, pivot+1, upperBound, swapCount);}
}


void merge(int array[], int low, int mid, int up, int *swapCount){
	int lowSize = mid-low+1;int upSize = up-mid;int lowArray[lowSize], upArray[upSize];
	for(int i =0;i<lowSize;i++){lowArray[i] = array[low + i];}
	for(int i =0;i<upSize;i++){upArray[i] = array[mid  + 1 + i];}
	int lowIdx = 0; int upIdx = 0; int mergeIdx = low;
	while(lowIdx < lowSize && upIdx < upSize){
		if(lowArray[lowIdx]<=upArray[upIdx]){array[mergeIdx++] = lowArray[lowIdx++];}
		else{array[mergeIdx++] = upArray[upIdx++];}
	}
	while(lowIdx<lowSize){array[mergeIdx++] = lowArray[lowIdx++];}
	while(upIdx<upSize){array[mergeIdx++] = upArray[upIdx++];}
}

void mergeSort(int array[], int lowerBound, int upperBound, int *swapCount){
	if(upperBound>lowerBound){
		int mid = lowerBound + (upperBound-lowerBound)/2;
		mergeSort(array,lowerBound,mid,swapCount);
		mergeSort(array,mid+1,upperBound,swapCount);
		merge(array,lowerBound,mid,upperBound,swapCount);
	}
}

int main(){	
	int size  = 14, bubbleCount = 0, insertionCount = 0, selectionCount = 0, quickCount = 0;	     
	int arr[] = {10,2,3,1,56,48,24,79,11,90,35,23,3,78};
	int temp[size];
	for(int i=0;i<size;i++){temp[i]=arr[i];}
	bubbleSort(temp, size, &bubbleCount);
	for(int i=0;i<size;i++){temp[i]=arr[i];}
	insertionSort(temp, size, &insertionCount);
	for(int i=0;i<size;i++){temp[i]=arr[i];}
	selectionSort(temp, size, &selectionCount);	
	for(int i=0;i<size;i++){temp[i]=arr[i];}
	quickSort(temp,0,size-1,&quickCount);
//	for(int i=0;i<size;i++){
//	printf("%d ",arr[i]);}
	printf("bubble:%d\ninsert:%d\nselect:%d\nquick:%d\n",bubbleCount,insertionCount,selectionCount,quickCount);

}
