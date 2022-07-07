#include <stdio.h>
#include <stdlib.h>

struct node{
	char data;
	struct node * next;
};

void push(struct node ** stack,char x){
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->data=x;
	if(*stack==NULL){
		t->next=NULL;
		*stack=t;}
	else{t->next=*stack;
		*stack=t;}
}

char pop(struct node ** stack){
	if(*stack==NULL){return -1;}else{
	char x =(*stack)->data;
	*stack=(*stack)->next;
	return x;}
}

void display(struct node * stack){
	struct node * trav;
	trav=stack;
	while(trav!=NULL){printf("%c ",trav->data);trav=trav->next;}
	printf("\n");
}

int peek(struct node * stack){
	return stack->data;
}
int size(struct node * stack){
	struct node * trav = stack;
	int cnt = 0;
	while(trav!=NULL){cnt++;trav=trav->next;}
	return cnt;
}
int isEmpty(struct node ** stack){if(*stack==NULL){return 1;}else{return 0;}}

void printFullList(struct node ** llist) {
  struct node * trav = *llist;
  while (trav != NULL) {
    printf("%c", trav -> data);
    trav = trav -> next;
  }
  printf("\n");
}
int main(){
	FILE* p;
	p = fopen("input.txt","r");
	if(p == NULL){printf("file doesnt exist");}
	char ch;
	char file[500];
	int n=0;
	while(ch!=EOF){
		ch = fgetc(p);
		file[n]=ch;
		n++;		
	}
	fclose(p);
	printf("\n");
	char outfile[n];
	struct node * stack = NULL;
	int k=0;
	for(int i=0;i<n;i++){
		if(file[i]!=' '){
			push(&stack,file[i]);
			}
		else if(file[i]==' '){
			
			if(isEmpty(&stack)==1){
				continue;
				}
			else{
				while(stack){
					char x = pop(&stack);
					outfile[k]=x;
					k++;
					}
				outfile[k]=' ';k++;
				}
			}	
		}
	pop(&stack);
	pop(&stack);
	while(stack){
					char x = pop(&stack);
					outfile[k]=x;
					k++;
					}
				outfile[k]=' ';k++;
	 outfile[k]='\0';
	
	p = fopen("output.txt","w+");
	k=0;
	
	while(outfile[k]!='\0'){
		fprintf(p,"%c",outfile[k]);k++;
	}	
	fprintf(p,"\n");
	fclose(p);
	
}
