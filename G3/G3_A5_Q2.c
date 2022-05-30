#include <stdio.h>
#include <stdlib.h>

int mod(int x , int y){
    if(x<0){return (x+y)%y;}
    else{return x%y;}
}
int isFull(int *front, int *rear, int size){if(mod(*front-1,size)==*rear){return 1;}else{return 0;}}
int isEmpty(int *front, int *rear){if(*front ==-1 && *rear==-1){return 1;}else{return 0;}}

void insertRear(int queue[], int* front, int * rear,int size, int x){
	if(*front==-1 && *rear==-1){
		*front=0;
		*rear=0;
		queue[*rear]=x;
		}
	else if(isFull(front,rear,size)){
		printf("Queue is Full!\n");
		}
	else{
		*rear=mod(*rear+1,size);
		queue[*rear] = x;
		}		
}
void insertFront(int queue[], int* front, int * rear,int size, int x){
	if(*front==-1 && *rear==-1){
		*front=0;
		*rear=0;
		queue[*front]=x;
		}
	else if(isFull(front,rear,size)){
		printf("Queue is Full!\n");
		}
	else{
		*front=mod(*front-1,size);
		queue[*front] = x;
		}		
}

int deleteFront(int queue[], int* front, int * rear,int size){
	if(isEmpty(front,rear)){printf("Queue is Empty!\n");}
	else if(*front==*rear){
		int x =queue[*front];
		*front=-1;
		*rear=-1;
		return x;
	}
	else{
		int x =queue[*front];
		*front=mod((*front+1),size);
		return x;
	}
}

int deleteRear(int queue[], int* front, int * rear,int size){
	if(isEmpty(front,rear)){printf("Queue is Empty!\n");}
	else if(*front==*rear){
		int x =queue[*rear];
		*front=-1;
		*rear=-1;
		return x;
	}
	else{
		int x =queue[*rear];
		*rear=mod(*rear-1,size);
		return x;
	}
}
void stretchQueue(int queue[],int *front,int *rear,int size){
    if(*rear<*front){
        
        for(int i=0;i<size-*front;i++){
            queue[size-(1+i)]=queue[size-(6+i)];
        }
        *front = *front+5;
    }
}

void reduceQueue(int queue[],int *front,int *rear,int *size){
    if(*size>10){
        if(*front-*rear>=6){
            for(int i=*front;i<*size;i++){
                queue[i-5]=queue[i];
            }
            *front = *front-5;
            *size=*size-5;
        }
        else if(*front<*rear){
            *size = *size-5;
        }
        else{printf("Cannot reduce size. Space in Use!\n");}
    }
    else{printf("Minimum allowed size already in use!\n");}
    
}
int printElements(int queue[], int* front, int * rear,int size){
	
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
void display(int queue[],int size){
    for (int i =0;i<size;i++){
        printf("%d ",queue[i]);
    }
    printf("\n");
}

int main(){
    int bigArray[100];
    int size = 10;
    int fArray=-1;
    int rArray=-1;
    while(1){
        printf("*******************************************************\n");
        printf("1.insertFront()\n2.insertRear()\n3.deleteFront()\n4.deleteRear()\n5.stretchQueue()\n6.reduceDequeue\n7.printElements()\n8.Exit\nEnter Your Choice:\n");
        printf("*******************************************************\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            printf("Enter Data:\n");
            int data;
            scanf("%d",&data);
            insertFront(bigArray,&fArray,&rArray,size,data);
            printf("front is %d and rear is %d\n",fArray,rArray);
            display(bigArray,size);
        }
        else if(ch==2){
            printf("Enter Data:\n");
            int data;
            scanf("%d",&data);
            insertRear(bigArray,&fArray,&rArray,size,data);
            printf("front is %d and rear is %d\n",fArray,rArray);
            display(bigArray,size);
        }
        else if(ch==3){
            int x = deleteFront(bigArray,&fArray,&rArray,size);
            if(x!=-1){printf("Dequeued: %d\n",x);display(bigArray,size);}
            
        }
        else if(ch==4){
            int x = deleteRear(bigArray,&fArray,&rArray,size);
            if(x!=-1){printf("Dequeued: %d\n",x);display(bigArray,size);}
        }
        else if(ch==5){
            size = size+5;
            stretchQueue(bigArray,&fArray,&rArray,size);
            display(bigArray,size);
        }
        else if(ch==6){
            reduceQueue(bigArray,&fArray,&rArray,&size);
            display(bigArray,size);
        }
        else if(ch==7){
            printElements(bigArray,&fArray,&rArray,size);
            display(bigArray,size);
        }
        else if(ch==8){
            exit(0);
        }
        else{
            printf("Invalid Choice\n");
        }
    }

}
