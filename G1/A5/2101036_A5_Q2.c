#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int num;	
	char name;
	struct node* next;
};

void enqueue(struct node ** queue,char name){
	struct node *t =(struct node*)malloc(sizeof(struct node));
	if(*queue==NULL){t->num =1;}else{t->num = ((*queue)->num)+1;}	
	t->name = name;
	t->next = *queue;
	*queue = t;
	printf("%c has been given order number %d\n",t->name,t->num);	
}

void dequeue(struct node ** queue, int num){
	struct node* trav = *queue;
	while(trav->next->num!=num){
		if(trav==NULL){printf("No such customer");break;}
		trav = trav->next;
	}
	printf("%c has recieved their order\n",trav->next->name);
	trav->next =trav->next->next;
}

void display(struct node ** queue){
	struct node* trav = *queue;
	while(trav!=NULL){
		printf(" %c(%d) ",trav->name,trav->num);
		trav = trav->next;
	}
	printf("\n");
}

int main(){
	struct node * queue =NULL;
	while(1){
	printf("*****************************************************************************************\n");
	printf("1.New Customer 1\n2.Order Complete? 2\n3.Display Current queue\nEnter your Choice:\n");
	printf("*****************************************************************************************\n");
	int ch;
	scanf("%d",&ch);
	getchar();
	if(ch==1){
		char n;
		printf("Enter name of the customer:\n");
		scanf("%c",&n);
		enqueue(&queue,n);		
	}
	else if(ch==2){
		int x;
		printf("Enter number of customer whose order has been completed");
		scanf("%d",&x);
		dequeue(&queue,x);
	}
	else if(ch==3){display(&queue);}
	else{printf("Incorrect choice");}
	}
	
}
