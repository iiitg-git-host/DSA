#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {char data;struct node* next;};
void push(struct node ** top , char x){struct node*t = (struct node *)malloc(sizeof(struct node));t -> data = x;t->next = *top;*top = t;}
struct node* buildStack(){struct node *top =NULL;return top;}
char pop(struct node ** top){if(*top == NULL){printf("Stack is Empty\n");}else{char x = (*top) -> data;*top = (*top)->next;return x;}}
char peek(struct node ** top){return (*top)->data;}
int isEmpty(struct node ** top){if(*top == NULL){return 1;}else{return 0;}}
void display(struct node ** top){struct node * trav= *top;while(trav!=NULL){printf("%c ",trav->data);trav = trav->next;}printf("\n");}
void reverse(char *exp){

    int size = strlen(exp);
    int j = size, i=0;
    char temp[size];

    temp[j--]='\0';
    while(exp[i]!='\0')
    {
        temp[j] = exp[i];
        j--;
        i++;
    }
    strcpy(exp,temp);
}


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
	char rev[500];
	scanf("%[^\n]%*c",rev);
	struct node * preStack = buildStack();
	int flag = 1;
	int i=0;
	while(rev[i]!='\0'){
		push(&preStack,rev[i]);				
		i++;}
	int n=i;
	reverse(rev);
    for(int i=0;i<n;i++){
        if(rev[i]=='('){rev[i]=')';}
        else if(rev[i]==')'){rev[i]='(';}
    }
	char ans[n];
	int k=0;
	preStack = NULL;
    for(int i=0;i<n;i++){
        if ((rev[i] >= 'a' && rev[i] <= 'z') || (rev[i] >= 'A' && rev[i] <= 'Z'))
        {
            ans[k] = rev[i];
            k++;
        }
        else if (rev[i] == '(')
        {
            push(&preStack, rev[i]);
        }
        else if (rev[i] == ')')
        {
            while (!isEmpty(&preStack) && peek(&preStack) != '(')
            {
                ans[k]=pop(&preStack);k++;
            }
            pop(&preStack);
            
        }
        else{
            while(!isEmpty(&preStack) && ord(rev[i]) <=ord(peek(&preStack))){
                ans[k] =pop(&preStack);k++;
            }
            push(&preStack,rev[i]);
        }
    }
    while(!isEmpty(&preStack)){
        ans[k] =pop(&preStack);k++;
    }
    reverse(ans);
	printf("%s\n",ans);

}
