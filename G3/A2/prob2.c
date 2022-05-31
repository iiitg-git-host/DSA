#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	struct node* next;
} *llist =NULL,*tail=NULL;

void insert_first(int x){
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->data = x;
	t->next = llist;
	llist = t;
	if(tail ==NULL){tail = t;}
	
} 
int delete_first(){
	int x = llist->data;
	llist = llist->next;
	return x;}
void insert_last(int x){
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->data = x;
	t->next = NULL;
	tail->next =t;
	tail = t;
	if(llist==NULL){llist=t;}
}
int delete_last(){
	int x = tail->data;
	struct node *last = llist;
	while((last->next)->next !=NULL){
		last=last->next;}
	last->next = NULL;
	tail = last;
return x;}

void swap_ends(){int x = delete_first();int y = delete_last();insert_first(y);insert_last(x);}

void shift_left(int k){
	
	int x;
	for(int i=0;i<k;i++){
		x = delete_last();
		insert_first(x);
}
}
void printFullList() {
  struct node * trav = llist;
  while (trav != NULL) {
    printf("%d ", trav -> data);
    trav = trav -> next;
  }
  printf("\n");
}


int main(){
	while(1){
        	printf("******************************************************\n");
	        printf("1.insertFirst\n2.insertLast\n3.deleteFirst\n4.deleteLast\n5.swapEnds\n6.shiftLeft\n7.printList\n8.exit\nEnter your choice:\n");
	        printf("******************************************************\n");
	        int ch;
	        scanf("%d",&ch);
	        if(ch==1){
	        	int x;
			printf("Enter data:\n");
			scanf("%d",&x);
			insert_first(x);
	        }
	        else if(ch==2){
	        	int x;
			printf("Enter data:\n");
			scanf("%d",&x);
			insert_last(x);           
	        }
	        else if(ch==3){
	            	printf("%d deleted\n",delete_first());
	        }
	        else if(ch==4){
	            	printf("%d deleted\n",delete_last());
	        }
	        else if(ch==5){
	        	swap_ends();
	            	printf("Swapped\n");
	        }
	        else if(ch==6){
	        	int x;
	        	printf("Shift left by:\n");
			scanf("%d",&x);
			shift_left(x);
	        }
	        else if(ch==7){
	        	printFullList();
	        }
	        else if(ch==8){
	            exit(0);
	        }
		else{
		printf("Invalid Choice!!\n");
		}
	}
}
