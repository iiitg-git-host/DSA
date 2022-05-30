#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    int size;
    struct node* seclast;
};

struct node* initialize(int size){
    struct node *queue =NULL;
    queue = (struct node*)malloc(sizeof(int)+sizeof(struct node*));
    queue->size = size;
    return queue;
}

void enqueue(struct node ** queue){
    struct node *t = (struct node*)malloc(sizeof(struct node)-sizeof(int));
    int x;
    printf("Enter Data\n");
    scanf("%d", &x);
    t->data = x;
    t->next = *queue;
    *queue = t;
    (*queue)->size--;
}
int dequeue(struct node ** queue){

}
void display(struct node ** queue){
    struct node* trav = *queue;
    while((trav->next)!=NULL){
        printf("%d ", (trav)->data);
        trav = trav->next;
    }
}
int peek(struct node** queue){}


int main(){
    int size;
    printf("Input Size:\n");
    scanf("%d",&size);
    struct node * list = initialize(size);
    for (int i = 0; i < size; i++)
    {
        enqueue(&list);
    }
    display(&list);
    while(1){
        printf("******************************************************************************\n");
        printf("Enter your choice: 1.Enqueue\n2.Dequeue\n3.Display\n4.Peek\n");
        printf("******************************************************************************\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 1)
        {
            enqueue(&list);
        }
        else if (ch == 2)
        {
            dequeue(&list);
        }
        else if (ch == 3)
        {
            display(&list);
        }
        else if (ch == 4)
        {
        }
        else if (ch == 5)
        {
        }
        else
        {
        }
    }
}