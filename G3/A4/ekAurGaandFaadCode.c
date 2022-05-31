#include <stdio.h>
#include <stdlib.h>
struct node {
    int service[5];
    int front;
    int rear;
    struct node* next;    
};
struct MultQue{
    int waitQueue[10];
    int waitFront;
    int waitRear;
    struct node * serviceList;
    struct node * tailServiceList;
};
struct node** addNode(){
    struct node * st = (struct node*)malloc(sizeof(struct node));
    struct node ** t =&st;
    (*t)->front = -1;
    (*t)->rear=-1;
    (*t)->next=NULL;
    return t;
}

int isEmpty(int front, int rear){if(front==-1 && rear==-1){return 1;}else{return 0;}}
int isFull(int front, int rear, int size){if(front == (rear+1)%size){return 1;}else{return 0;}}

void enqueue(int q[],int *front, int*rear, int size, int x){
    if(isEmpty(*front,*rear)){*front=0;*rear=0;}
    else{*rear =(*rear+1)%size;}
    q[*rear]=x;
}
int dequeue(int q[],int *front, int*rear, int size){
    int x = q[*front];    
    if(*front==*rear){
        *front=-1;*rear=-1;
    }
    else{
        *front =(*front+1)%size;        
    }
    return x;
}
void multEnqueue(struct MultQue ** mulQue, int x){
    if(!(isFull((*mulQue)->tailServiceList->front,(*mulQue)->tailServiceList->rear,5))){
        enqueue((*mulQue)->tailServiceList->service,&((*mulQue)->tailServiceList->front),&((*mulQue)->tailServiceList->rear),5,x);
    }
    else if(isFull((*mulQue)->serviceList->front,(*mulQue)->serviceList->rear,5)){
        if(isFull((*mulQue)->waitFront,(*mulQue)->waitRear,10)){
            struct node * t = *(addNode());
            t->next = (*mulQue)->serviceList;
            (*mulQue)->serviceList = t;
            for(int i=0;i<5;i++){
                int deqFromW = dequeue((*mulQue)->waitQueue,&((*mulQue)->waitFront),&((*mulQue)->waitRear),10);
                enqueue((*mulQue)->serviceList->service,&((*mulQue)->serviceList->front),&((*mulQue)->serviceList->rear),5,deqFromW);
            }
            enqueue((*mulQue)->waitQueue,&((*mulQue)->waitFront),&((*mulQue)->waitRear),10,x);
        }
        else{
            enqueue((*mulQue)->waitQueue,&((*mulQue)->waitFront),&((*mulQue)->waitRear),10,x);
        }
    }
    else{  
        enqueue((*mulQue)->serviceList->service,&((*mulQue)->serviceList->front),&((*mulQue)->serviceList->rear),5,x);
    }
}
int multDequeue(struct MultQue ** mulQue){
    int x;
    if(isEmpty((*mulQue)->waitFront,(*mulQue)->waitRear)){
        if(isEmpty((*mulQue)->tailServiceList->front,(*mulQue)->tailServiceList->rear)){
            struct node * temp = (*mulQue)->serviceList;
            while(temp->next->next!=NULL){
                temp=temp->next;
            }
            temp->next=NULL;
            (*mulQue)->tailServiceList=temp;
            x = multDequeue(mulQue);            
        }
        else{
            x= dequeue((*mulQue)->tailServiceList->service, &((*mulQue)->tailServiceList->front), &((*mulQue)->tailServiceList->rear), 5);
        }
    }
    else{
        x= dequeue((*mulQue)->tailServiceList->service, &((*mulQue)->tailServiceList->front), &((*mulQue)->tailServiceList->rear), 5);
        int deqFromS = dequeue((*mulQue)->waitQueue, &((*mulQue)->waitFront), &((*mulQue)->waitRear),10);
        enqueue((*mulQue)->tailServiceList->service, &((*mulQue)->tailServiceList->front), &((*mulQue)->tailServiceList->rear), 5, deqFromS);
    }
    return x;

}
void printWaitQueue(struct MultQue ** mulQue){
    if(isEmpty((*mulQue)->waitFront,(*mulQue)->waitRear)){
        printf("None\n");
    }
    else{
        int i = (*mulQue)->waitFront;
        while(i!=(*mulQue)->waitRear){
            printf("%d ",(*mulQue)->waitQueue[i]);
            i=(i+1)%10;
        }
    printf("%d\n",(*mulQue)->waitQueue[i]);
    }
}
void printServiceList(struct MultQue ** mulQue){
    if(isEmpty((*mulQue)->serviceList->front,(*mulQue)->serviceList->rear)){
        printf("None\n");
    }
    else{
        struct node * temp = (*mulQue)->serviceList;
        while(temp!=NULL){
            int i = temp->front;
            printf("[");
            while(i!=temp->rear){
                printf("%d, ",temp->service[i]);
                i=(i+1)%5;
            }
            printf("%d]  ->  ",temp->service[i]);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}
int countServiceNodes(struct MultQue **mulQue){
    struct node * temp = (*mulQue)->serviceList;
    int cnt =0;
    while(temp!=NULL){
        cnt++;
        temp=temp->next;
    }
    return cnt;
}
void statusQueue(struct MultQue ** mulQue){
    printf("The number of nodes in Service List is %d\nData in Service List:",countServiceNodes(mulQue));
    printServiceList(mulQue);
    printf("Data in Wait Queue:");
    printWaitQueue(mulQue);
    if(isFull((*mulQue)->serviceList->front,(*mulQue)->serviceList->rear,5)){
        if(isFull((*mulQue)->waitFront,(*mulQue)->waitRear,10)){
            printf("Mult Queue is Full!\n");
        }
        else{
            printf("Next Element will be enqueued in Wait Queue.\n");
        }
    }
    else{  
        printf("Next Element will be enqueued in Service List.\n");
    }
}
int main(){
    struct MultQue * mulQue = (struct MultQue*)malloc(sizeof(struct MultQue));
    mulQue->waitFront = -1;
    mulQue->waitRear = -1;
    mulQue->serviceList = *(addNode());
    mulQue->tailServiceList = mulQue->serviceList;
    while(1){
        printf("##################################\n");
        printf("##\t1.Mult Enqueue\t\t##\n##\t2.Mult Dequeue\t\t##\n##\t3.Status Queue\t\t##\n##\t4.Exit\t\t\t##\n##\tEnter your choice:\t##\n");
        printf("##################################\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            printf("Enter data:");
            int data;
            scanf("%d",&data);
            multEnqueue(&mulQue,data);
        }
        else if(ch==2){
            printf("%d dequeued.\n",multDequeue(&mulQue));            
        }
        else if(ch==3){
            statusQueue(&mulQue);
        }
        else if(ch==4){
            exit(0);
        }
    }
}
