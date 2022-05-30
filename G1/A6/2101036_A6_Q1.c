#include <stdio.h>

int isFull(int queue[], int* front, int * rear,int size){
	if(*front=(*rear+1)%size){
		return 1;
		}
	else{
		return 0;
		}
	}

int isEmpty(int queue[], int* front, int * rear,int size){
	if(*front==-1 && *rear==-1){
	return 1;
	}else{return 0;}}

void enqueue(int queue[], int* front, int * rear,int size, int x){
	if(*front==-1 && *rear==-1){
		*front=0;
		*rear=0;
		queue[*rear]=x;
		}
	else if((*rear+1)%size==*front){
		printf("Queue is Full!\n");
		}
	else{
		*rear=(*rear+1)%size;
		queue[*rear] = x;
		}		
}

int dequeue(int queue[], int* front, int * rear,int size){
	if(*front ==-1 && *rear==-1){printf("Queue is Empty!\n");}
	else if(*front==*rear){
		int x =queue[*front];
		*front=-1;
		*rear=-1;
		return x;
	}
	else{
		int x =queue[*front];
		*front=(*front+1)%size;
		return x;
	}
}

int display(int queue[], int* front, int * rear,int size){
	
	int i =*front;
	if(*rear>=*front){
		while(i<*rear){
			printf("%d ",queue[i]);
			i=(i+1)%size;
		}
	printf("%d",queue[*rear]);
	}
	else{
		while(i<size){
			printf("%d ",queue[i]);
			i++;
		}
		i=0;
		while(i<=*rear){
			printf("%d ",queue[i]);
			i++;
		}
	}
	printf("\n");
	
	
	
}


int main(){
	int size;
	printf("Enter Size of Queue:\n");
	scanf("%d",&size);
	int q[size];
	int qfr= -1;
	int qrr= -1;
	while(1){
		printf("*****************************************************************\n");
		printf("1.Enqueue\n2.Dequeue\n3.Display\n");
		printf("*****************************************************************\n");	
		printf("Enter Your Choice:\n");
		int ch;
		scanf("%d",&ch);	
		if (ch==1){
			int x;
			printf("Enter Data:\n");
			scanf("%d",&x);
			enqueue(q,&qfr,&qrr,size,x);
		}
		else if(ch==2){
			printf("%d\n",dequeue(q,&qfr,&qrr,size));
		}
		else if(ch==3){
			display(q,&qfr,&qrr,size);
		}
		else{
			printf("Invalid Choice\n");
		}
	}
	
	
	
	
	
	
	
}
