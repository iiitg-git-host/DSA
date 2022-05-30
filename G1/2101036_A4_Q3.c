#include <stdio.h>
#include <stdlib.h>
struct node {char data;struct node* next;};
void push(struct node ** top , char x){struct node*t = (struct node *)malloc(sizeof(struct node));t -> data = x;t->next = *top;*top = t;}
struct node* buildStack(){struct node *top =NULL;return top;}
char pop(struct node ** top){if(*top == NULL){printf("Stack is Empty\n");}else{char x = (*top) -> data;*top = (*top)->next;return x;}}
char peek(struct node ** top){return (*top)->data;}
int isEmpty(struct node ** top){if(*top == NULL){return 1;}else{return 0;}}
void display(struct node ** top){struct node * trav= *top;while(trav!=NULL){printf("%c ",trav->data);trav = trav->next;}printf("\n");}

int ord(char x){
	if(x =='+' || x=='-'){return 0;}
	else if(x =='*' || x=='/'){return 1;}
	else if(x =='^'){ return 2;}
	else if(x =='{' || x=='(' || x=='['){return 3;}	
}

int prcd(char x , char y){
	int m = ord(x);
	int n = ord(y);
	if(m>n || m==n){return 1;}
	else{return 0;}	
}

int main(){
	printf("Enter string to check\n");
	char a[500];
	scanf("%[^\n]%*c",a);
	struct node * preStack = buildStack();
	int flag = 1;
	int i=0;
	while(a[i]!='\0'){
		push(&preStack,a[i]);				
		i++;}
	char rev[i+1];
	int n=i;
	for(int i=0;i<n;i++){
		char x=pop(&preStack);
		rev[i]=x;
	}
	rev[i]='\0';
	char ans[n];
	int k=0;
	preStack = NULL;
	for(int i=0;i<n;i++){
		if(rev[i]==')'){push(&preStack,rev[i]);}
		else if(rev[i]=='('){while(peek(&preStack)!=')'){ans[k]=pop(&preStack);k++;}}
		else if(rev[i]=='+' || rev[i]=='-' || rev[i]=='*' || rev[i]=='/' || rev[i]=='^'){
			if(preStack==NULL){push(&preStack,rev[i]);}
			else{
				if(ord(rev[i])>ord(peek(&preStack))){push(&preStack,rev[i]);}
				else if(ord(rev[i])==ord(peek(&preStack)) && rev[i]=='^'){while(!(ord(rev[i])>ord(peek(&preStack)))){ans[k]=pop(&preStack);k++;}push(&preStack,rev[i]);}
				else if(ord(rev[i])==ord(peek(&preStack))){push(&preStack,rev[i]);}
				else if(ord(rev[i])<ord(peek(&preStack))){while(!(ord(rev[i])<ord(peek(&preStack)))){ans[k]=pop(&preStack);k++;}push(&preStack,rev[i]);}
			}
		
		}
		else{ans[k]=rev[i];k++;}
	}
	while(preStack!=NULL){
		ans[k]=pop(&preStack);k++;}
	printf("\n");
	for(int i=0;i<k;i++){
		printf("%c",ans[i]);
	}



	
}
