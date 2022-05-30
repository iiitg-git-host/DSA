#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

void push(struct node ** top , int x){
	struct node*t = (struct node *)malloc(sizeof(struct node));
	t -> data = x;
	t->next  = *top;
	*top = t;	
}

struct node* buildStack(){
	struct node *top;
	int n;
	printf("Enter size of stack\n");
	scanf("%d",&n);
	for(int i =0 ;i<n;i++){
		int data;
		printf("Enter Data:\n");
		scanf("%d",&data);
		push(&top,data);	
	}
	return top;		
}



int pop(struct node ** top){
	if(*top == NULL){printf("Stack is Empty\n");}else{
	int x = (*top) -> data;
	*top = (*top)->next;}
}

int peek(struct node ** top){return (*top)->data;}

int isEmpty(struct node ** top){if(*top == NULL){return 1;}else{return 0;}}

void display(struct node ** top){
	struct node * trav= *top;
	while(trav!=NULL){
		printf("%d ",trav->data);
		trav = trav->next;
	}
	printf("\n");
}

struct node* copyStack(struct node ** top){
	struct node * temp =NULL ;
	struct node * trav= *top;
	struct node* stack2 =NULL;
	while(trav!=NULL){
		push(&temp,trav->data);
		trav = trav->next;
	}
	struct node *trav2 = temp;
	while(trav2!=NULL){
		push(&stack2,trav2->data);
		trav2 = trav2->next;
	}
 
	return stack2; 
		 
	
	
}

int main(){
	struct node *stack = buildStack();
	printf("Stack 1 is");
	display(&stack);
	struct node *stack2 = copyStack(&stack);
	printf("\n");
	display(&stack2);
}
