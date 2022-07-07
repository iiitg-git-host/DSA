#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* next;
};

void push(struct node ** top , char x){
	struct node*t = (struct node *)malloc(sizeof(struct node));
	t -> data = x;
	t->next  = *top;
	*top = t;	
}

struct node* buildStack(){
	struct node *top =NULL;
	return top;		
}



char pop(struct node ** top){
	if(*top == NULL){printf("Stack is Empty\n");}else{
	int x = (*top) -> data;
	*top = (*top)->next;}
}

char peek(struct node ** top){return (*top)->data;}

int isEmpty(struct node ** top){if(*top == NULL){return 1;}else{return 0;}}

void display(struct node ** top){
	struct node * trav= *top;
	while(trav!=NULL){
		printf("%c ",trav->data);
		trav = trav->next;
	}
	printf("\n");
}

int main(){
	printf("Enter string to check\n");
	char a[500];
	scanf("%[^\n]%*c",a);
	struct node * checkStack = buildStack();
	int flag = 1;
	int i=0;
	while(a[i]!='\0'){
		if(a[i]=='(' || a[i]=='{' || a[i]=='['){push(&checkStack, a[i]);}
		else if(a[i]==')'){if(peek(&checkStack) == '('){pop(&checkStack);}else{flag = 0 ; break;}}
		else if(a[i]==']'){if(peek(&checkStack) == '['){pop(&checkStack);}else{flag = 0 ; break;}}
		else if(a[i]=='}'){if(peek(&checkStack) == '{'){pop(&checkStack);}else{flag = 0 ; break;}}
		else{flag = -1;break;}
		i++;}
	if(flag == 1 && isEmpty(&checkStack)==1){printf("Correct\n");}	
	else if(flag==-1){printf("Input not correct");}	
	else if(flag ==0 || isEmpty(&checkStack)==0) {printf("Incorrect");}
	



	
}
