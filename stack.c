#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node * next;
}*stack=NULL;

void push(int x){
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->data=x;

	if(stack==NULL){
		t->next=NULL;
		stack=t;}
	else{t->next=stack;
		stack=t;}
}

int pop(){
	if(stack==NULL){return -1;}else{
	int x = stack->data;
	stack=stack->next;
	return x;}
}

void display(){
	struct node * trav;
	trav=stack;
	while(trav!=NULL){printf("%d ",trav->data);trav=trav->next;}
	printf("\n");
}

int peek(){
	return stack->data;
}
int size(){
	struct node * trav = stack;
	int cnt = 0;
	while(trav!=NULL){cnt++;trav=trav->next;}
	return cnt;
}
int isEmpty(){if(stack==NULL){return 1;}else{return 0;}}
int main(){
	while(1>0){ 
		printf("*****************************************************************************\n");
		printf("1.push()\n2.pop\n3.display()\n4.peek()\n5.isEmpty()\n6.size()\nChoose your input:\n");
		printf("*****************************************************************************\n");
		int ch;
		scanf("%d",&ch);
		if(ch==1){
			int x;
			printf("Enter Data:\n");
			scanf("%d",&x);	
			push(x);
		}
		else if(ch==2){
			int x = pop();
			if(x==-1){
				printf("Empty stack\n");
			}
			else{
				printf("%d\n",x);
			}
		}
		else if(ch==3){
			display();
		}
		else if(ch==4){
			if(isEmpty()==1){
				printf("Stack is Empty\n");
			}
			else{
				int x = peek();
				printf("%d \n",x);
			}
		}
		else if(ch==5){
			if(isEmpty()==1){
				printf("Stack is Empty\n");
			}
			else{
				printf("Stack is not Empty\n");
			}
		}
		else if(ch==6){
			printf("%d \n",size());
		}
		else{
			printf("Invalid Choice\n");
		}
		printf("*****************************************************************************\n");
	}
}

