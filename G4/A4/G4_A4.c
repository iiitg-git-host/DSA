#include <stdio.h>
#include <stdlib.h>

struct node {
    int arr[5];
    int index;
    struct node* next;    
};

void enqueue(struct node ** head , struct node ** tail){
    int data;
    printf("Enter data:\n");
    scanf("%d",&data);
    if(*head == NULL || (*head)->index == 0){
        struct node * t = (struct node *)malloc(sizeof(struct node));
        t->index = 4;
        t->arr[t->index] = data;
        if(*head ==NULL){
            *tail = t;
        }
        else{
            t->next = *head;
        }
        *head = t;
        (*tail) ->next =*head;

                
    }
    else{
        (*head)->index --;
        (*head) ->arr[(*head)->index] = data;
        
    }
}

int dequeue(struct node ** head,struct node **tail){
    struct node *trav = *head;
    int temp=0;
    while(trav!=(*tail)){
       for(int i = trav->index; i<5; i++){
           int temptemp = trav->arr[i];
           trav->arr[i] = temp;
           temp = temptemp;           
        }
        trav = trav->next;
    }
    for(int i = trav->index; i<5; i++){
           int temptemp = trav->arr[i];
           trav->arr[i] = temp;
           temp = temptemp;           
        }
    (*head)->index++;
    if ((*head)->index==5){
        (*head)= (*head)->next;
    }
}

void display(struct node ** head,struct node **tail){
    struct node * trav = *head;
    while(trav!=*tail){
        printf("[ ");
        for(int i = trav->index; i<5; i++){
            printf("%d ",trav->arr[i]);
        }
        printf("]  ->   ");
        trav = trav->next;
    }
    printf("[ ");
        for(int i = trav->index; i<5; i++){
            printf("%d ",trav->arr[i]);
        }
    printf("] ");
    printf("\n");
}
int main(){
    struct node *arq =NULL, *tarq =NULL;
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    enqueue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
    dequeue(&arq,&tarq);
    display(&arq,&tarq);
}

/*
*head
    []

    [0 0 0 0 1]    ->      NULL
    index = 4
    [0 0 0 2 1]    ->      NULL
    index = 3
    [0 0 3 2 1]    ->      NULL
    index = 2
    [0 4 3 2 1]    ->      NULL
    index = 1
    [5 4 3 2 1]    ->      NULL
    index = 0
    [0 0 0 7 6]    ->     [5 4 3 2 1]     ->      NULL
    index =3              index = 0


    [6] -> [5 4 3 2 1]
            index = 4


*/