#include <stdio.h>
#include <stdlib.h>

struct node{
    char data;
    struct node * next;
    struct node * prev;
};
int isEmpty(struct node ** head, struct node ** tail){if(*head==NULL && *tail==NULL){return 1;}else{return 0;}}

void addAction(struct node ** head,struct node ** tail,char x){
    struct node * t = (struct node*)malloc(sizeof(struct node));
    t->data = x;
    t->prev = NULL;
    if(*head==NULL){
        *head = t;
        *tail = t;
        (*tail)->next =NULL;
        (*head)->prev= NULL;
    }
    else{
        t->next = *head;
        (*head)->prev = t;
        *head = t;
    }       
}
void undoSameOrder(struct node ** head,struct node **tail){
    if(isEmpty(head,tail)){
        printf("No actions in list!\n");
        }
    else{
        printf("%c undid\n",(*tail)->data);
        *tail=(*tail)->prev;
        if(*tail!=NULL){(*tail)->next=NULL;}
        if(*tail==NULL){*head = NULL;}
    }
}

void undoReverseOrder(struct node ** head, struct node ** tail){
    if(isEmpty(head,tail)){
        printf("No actions in list!\n");
        }
    else{
        printf("%c undid\n",(*head)->data);
        *head=(*head)->next;
        if(*head!=NULL){(*head)->prev = NULL;}
        if(*head==NULL){*tail = NULL;}
    }
}

void investigate(struct node ** head, struct node ** tail){
    if(isEmpty(head,tail)){
        printf("No actions in list!\n");
        }
    else{
        char x;
        printf("Enter action to investigate:\n");
        scanf("%c",&x);
        struct node *trav= *head;
        int flag = 1;
        while(trav->data!=x){
            if(trav==NULL){printf("Action not found!\n");flag=0;break;}
            trav=trav->next;
        }
        if(flag!=0){
            while(trav!=NULL){
                printf("%c ",trav->data);
                trav=trav->next;
            }
            printf("\n");
        }        
    }
}
void redo(struct node ** head, struct node ** tail){
    if(isEmpty(head,tail)){
        printf("No actions in list!\n");
        }
    else{
        struct node * trav = *tail;
        int flag= 1;
        while(flag){
            if(trav==NULL){break;}
            printf("Has '%c' been performed correctly?(y/n)\n",trav->data);
            char ch;
            scanf("%c",&ch);
            getchar();
            if(ch=='n'){flag=0;}
            trav=trav->prev;
        }
        if(trav!=NULL){trav=trav->next;}
        if(flag==0){
            char x = trav->data;
            trav->next->prev=trav->prev;
            trav->prev->next = trav->next;
            addAction(head,tail,x);
            printf("%c redone!\n",x);            
        }

    }
}

void printActionList(struct node ** head, struct node ** tail){
    if(isEmpty(head,tail)){printf("No actions in list!\n");}
    else{
        struct node * trav = *tail;
        int flag= 1;
        while(flag){
            if(trav==NULL){break;}
            printf("%c ",trav->data);
            trav=trav->prev;
        }
        printf("\n");
    }
}
int main(){
    struct node * list=NULL;
    struct node * tlist=NULL;
    while(1){
        printf("*******************************************************\n");
        printf("1.addAction()\n2.undoSameOrder()\n3.undoReverseOrder()\n4.investigate()\n5.redo()\n6.printActionList()\n7.Exit\nEnter Your Choice:\n");
        printf("*******************************************************\n");
        int ch;
        scanf("%d",&ch);
        getchar();
        if(ch==1){
            char x;
            printf("Enter Data:\n");
            scanf("%c",&x);
            addAction(&list,&tlist,x);
        }
        else if(ch==2){
            undoSameOrder(&list,&tlist);
        }
        else if(ch==3){
            undoReverseOrder(&list,&tlist);            
        }
        else if(ch==4){
            investigate(&list,&tlist);
        }
        else if(ch==5){
            redo(&list,&tlist);
        }
        else if(ch==6){
            printActionList(&list,&tlist);
        }
        else if(ch==7){
            exit(0);
        }
        else{
            printf("Invalid Choice\n");
        }
    }

}