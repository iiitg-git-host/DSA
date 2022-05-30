#include <stdio.h>
#include <stdlib.h>
struct node {
    int serv[5];
    int front;
    int rear;
    struct node* next;    
};
struct multQueue{
    int waitQueue[10];
    int wfront;
    int wrear;
    struct node * serviceList;
    struct node * tserviceList;
};
struct node** newNode(){
    struct node * st = (struct node*)malloc(sizeof(struct node));
    struct node ** t =&st;
    (*t)->front = -1;
    (*t)->rear=-1;
    (*t)->next=NULL;
    return t;
}
struct multQueue* initialize(){
    struct multQueue * t = (struct multQueue*)malloc(sizeof(struct multQueue));
    t->wfront = -1;
    t->wrear = -1;
    t->serviceList = *(newNode());
    t->tserviceList = t->serviceList;
} 
int isEmpty(int front, int rear){
    if(front==-1 && rear==-1){
        return 1;
    }
    else{
        return 0;
    }
}
int isFull(int front, int rear, int size){
    if(front == (rear+1)%size){
        return 1;
    }
    else{
        return 0;
    }
}
void enqueue(int queue[],int *front, int*rear, int size, int x){
    if(isEmpty(*front,*rear)){*front=0;*rear=0;}
    else{*rear =(*rear+1)%size;}
    queue[*rear]=x;
}
int dequeue(int queue[],int *front, int*rear, int size){
    int x = queue[*front];    
    if(*front==*rear){
        *front=-1;*rear=-1;
    }
    else{
        *front =(*front+1)%size;        
    }
    return x;
}
void multEnqueue(struct multQueue ** MQ, int x){
    if(!(isFull((*MQ)->tserviceList->front,(*MQ)->tserviceList->rear,5))){
        enqueue((*MQ)->tserviceList->serv,&((*MQ)->tserviceList->front),&((*MQ)->tserviceList->rear),5,x);
        
    }
    else
    if(isFull((*MQ)->serviceList->front,(*MQ)->serviceList->rear,5)){
        if(isFull((*MQ)->wfront,(*MQ)->wrear,10)){
            struct node * t = *(newNode());
            t->next = (*MQ)->serviceList;
            (*MQ)->serviceList = t;
            for(int i=0;i<5;i++){
                int y = dequeue((*MQ)->waitQueue,&((*MQ)->wfront),&((*MQ)->wrear),10);
                enqueue((*MQ)->serviceList->serv,&((*MQ)->serviceList->front),&((*MQ)->serviceList->rear),5,y);
                //printf("Sfront is %d and Srear is %d\n",(*MQ)->serviceList->front,(*MQ)->serviceList->rear);
            }
            enqueue((*MQ)->waitQueue,&((*MQ)->wfront),&((*MQ)->wrear),10,x);
            //printf("Wfront is %d and Wrear is %d\n",(*MQ)->wfront,(*MQ)->wrear);
        }
        else{
            enqueue((*MQ)->waitQueue,&((*MQ)->wfront),&((*MQ)->wrear),10,x);
            //printf("Wfront is %d and Wrear is %d\n",(*MQ)->wfront,(*MQ)->wrear);
        }
    }
    else{  
        enqueue((*MQ)->serviceList->serv,&((*MQ)->serviceList->front),&((*MQ)->serviceList->rear),5,x);
        //printf("Sfront is %d and Srear is %d\n",(*MQ)->serviceList->front,(*MQ)->serviceList->rear);
    }
}
int multDequeue(struct multQueue ** MQ){
    int x;
    if(isEmpty((*MQ)->wfront,(*MQ)->wrear)){
        if(isEmpty((*MQ)->tserviceList->front,(*MQ)->tserviceList->rear)){
            struct node * trav = (*MQ)->serviceList;
            while(trav->next->next!=NULL){
                trav=trav->next;
            }
            trav->next=NULL;
            (*MQ)->tserviceList=trav;
            x = multDequeue(MQ);            
        }
        else{
            x= dequeue((*MQ)->tserviceList->serv,&((*MQ)->tserviceList->front),&((*MQ)->tserviceList->rear),5);
        }
    }
    else{
        x= dequeue((*MQ)->tserviceList->serv,&((*MQ)->tserviceList->front),&((*MQ)->tserviceList->rear),5);
        int y = dequeue((*MQ)->waitQueue,&((*MQ)->wfront),&((*MQ)->wrear),10);
        enqueue((*MQ)->tserviceList->serv,&((*MQ)->tserviceList->front),&((*MQ)->tserviceList->rear),5,y);
    }
    return x;

}
void displayWait(struct multQueue ** MQ){
    if(isEmpty((*MQ)->wfront,(*MQ)->wrear)){
        printf("None\n");
    }
    else{
        int i = (*MQ)->wfront;
        while(i!=(*MQ)->wrear){
            printf("%d ",(*MQ)->waitQueue[i]);
            i=(i+1)%10;
        }
    printf("%d\n",(*MQ)->waitQueue[i]);
    }
}
void displayService(struct multQueue ** MQ){
    if(isEmpty((*MQ)->serviceList->front,(*MQ)->serviceList->rear)){
        printf("None\n");
    }
    else{
        struct node * trav = (*MQ)->serviceList;
        while(trav!=NULL){
            int i = trav->front;
            printf("[");
            while(i!=trav->rear){
                printf("%d, ",trav->serv[i]);
                i=(i+1)%5;
            }
            printf("%d]  ->  ",trav->serv[i]);
            trav=trav->next;
        }
        printf("NULL\n");
    }
}
int serviceNodes(struct multQueue **MQ){
    struct node * trav = (*MQ)->serviceList;
    int cnt =0;
    while(trav!=NULL){
        cnt++;
        trav=trav->next;
    }
    return cnt;
}
void statusQueue(struct multQueue ** MQ){
    printf("The no. of nodes in Service List is %d\nElements in Service List:\n",serviceNodes(MQ));
    displayService(MQ);
    printf("Elements in Wait Queue:\n");
    displayWait(MQ);
    if(isFull((*MQ)->serviceList->front,(*MQ)->serviceList->rear,5)){
        if(isFull((*MQ)->wfront,(*MQ)->wrear,10)){
            printf("Mult Queue is Full!\n");
        }
        else{
            printf("New Element will be enqueued in Wait Queue!\n");
        }
    }
    else{  
        printf("New Element will be enqueued in Service List!\n");
    }
}
int main(){
    struct multQueue * MQ  =initialize();
    while(1){
        printf("******************************************************\n");
        printf("1.multEnqueue\n2.multDequeue\n3.statusQueue\n4.Exit\nEnter your choice:\n");
        printf("******************************************************\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            printf("Enter data:");
            int data;
            scanf("%d",&data);
            multEnqueue(&MQ,data);
        }
        else if(ch==2){
            printf("%d dequeued.\n",multDequeue(&MQ));            
        }
        else if(ch==3){
            statusQueue(&MQ);
        }
        else if(ch==4){
            exit(0);
        }
    }
}
