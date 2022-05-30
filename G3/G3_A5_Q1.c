#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node * next;
    struct node * prev;
};
void initialize(struct node ** head,struct node ** tail){
    int size;
    printf("Enter Size of Linked head:\n");
    scanf("%d",&size);
    for(int i=0;i<size;i++){
        struct node * t = (struct node*)malloc(sizeof(struct node));
        if(*head==NULL){
            *head = t;
            *tail = t;
            (*tail)->next =*head;
            (*head)->prev= *tail;
        }
        else{
            t->next = *head;
            (*head)->prev = t;
            t->prev = *tail;
            (*tail)->next = t;
            *head = t;
        }       

    }
}
int isEmpty(struct node ** front, struct node ** rear){if(*front==NULL && *rear==NULL){return 1;}else{return 0;}}
int isFull(struct node ** front, struct node ** rear){if((*rear)->next==*front){return 1;}else{return 0;}}

void insertFront(struct node **front,struct node ** rear,struct node **head,int x){
    if((*front)==NULL && (*rear)==NULL){*front = *head;*rear= *head;(*front)->data = x;}
    else if(isFull(front,rear)){printf("Queue is Full!\n");}
    else{(*front)=(*front)->prev;(*front)->data = x;}
}

void insertRear(struct node **front,struct node ** rear,struct node **head,int x){
    if((*front)==NULL && (*rear)==NULL){*front = *head;*rear= *head;(*rear)->data = x;}
    else if(isFull(front,rear)){printf("Queue is Full!\n");}
    else{(*rear)=(*rear)->next;(*rear)->data = x;}
}

int deleteFront(struct node **front,struct node ** rear,struct node **head){
    if(isEmpty(front,rear)){printf("Queue is Empty!\n");return -1;}
    else if(*front==*rear){int x = (*front)->data;*front=NULL;*rear=NULL;return x;}
    else{int x= (*front)->data;*front= (*front)->next;return x;}
}
int deleteRear(struct node **front,struct node ** rear,struct node **head){
    if(isEmpty(front,rear)){printf("Queue is Empty!\n");return -1;}
    else if(*front==*rear){int x = (*rear)->data;*front=NULL;*rear=NULL;return x;}
    else{int x= (*rear)->data;*rear= (*rear)->prev;return x;}
}
void printElements(struct node ** front, struct node ** rear){
    if(isEmpty(front,rear)){printf("Queue is Empty!\n");}
    else{
        struct node * trav = *front;
        while(trav!=*rear){
            printf("%d ",trav->data);
            trav= trav->next;
        }
        printf("%d\n",trav->data);
    }
}
int main(){
    struct node * list=NULL;
    struct node * tlist=NULL;
    initialize(&list,&tlist);
    struct node * front = NULL;
    struct node * rear = NULL;
    while(1){
        printf("*******************************************************\n");
        printf("1.insertFront()\n2.insertRear()\n3.deleteFront()\n4.deleteRear()\n5.printElements()\n6.Exit\nEnter Your Choice:\n");
        printf("*******************************************************\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            printf("Enter Data:\n");
            int data;
            scanf("%d",&data);
            insertFront(&front,&rear,&list,data);
        }
        else if(ch==2){
            printf("Enter Data:\n");
            int data;
            scanf("%d",&data);
            insertRear(&front,&rear,&list,data);
        }
        else if(ch==3){
            int x = deleteFront(&front,&rear,&list);
            if(x!=-1){printf("Dequeued: %d\n",x);}
            
        }
        else if(ch==4){
            int x = deleteRear(&front,&rear,&list);
            if(x!=-1){printf("Dequeued: %d\n",x);}
        }
        else if(ch==5){
            printElements(&front,&rear);
        }
        else if(ch==6){
            exit(0);
        }
        else{
            printf("Invalid Choice\n");
        }
    }

}