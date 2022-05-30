#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};

void enqueue(struct node ** queue, int x){
	struct node *t =(struct node*)malloc(sizeof(struct node));
	t->data = x;
	t->next = *queue;
	*queue = t;	
}

int dequeue(struct node ** queue){
	struct node* trav = *queue;
	while(trav->next->next!=NULL){
		trav = trav->next;
	}
	int x = trav->next->data;
	trav->next =NULL;
	return x;
}

void display(struct node ** queue){
	struct node* trav = *queue;
	while(trav!=NULL){
		printf("%d",trav->data);
		trav = trav->next;
	}
	printf("\n");
}

int size(struct node ** queue){
	int s = 0;
	struct node* trav = *queue;
	while(trav!=NULL){
		s++;
		trav = trav->next;
	}
	return s;
}

int compare(struct node **que1 , struct node ** que2){
	if(size(que1)>size(que2)){return 1;}
	else if(size(que1)<size(que2)){return -1;}
	else if(size(que1)==size(que2)){
		struct node *trav1 = *que1,*trav2 = *que2;
		while(trav1!=NULL){
			if(trav1->data==trav2->data){trav1=trav1->next;trav2=trav2->next;continue;}
			else if(trav1->data>trav2->data){return 1;}
			else if(trav1->data<trav2->data){return -1;}
		}
		return 0;
	}
}

int main(){
	struct node *queue1= NULL,*queue2=NULL;
	while(1){
	printf("*****************************************************************************************\n");
	printf("1.Edit Queue 1\n2.Edit Queue 2\n3.Compare\nEnter your Choice:\n");
	printf("*****************************************************************************************\n");
	int ch;
	scanf("%d",&ch);
	if(ch==1){
		printf("	******************************************************************************************\n");
		printf("	*1.Enqueue\n	*2.Dequeue\n	*3.Display\n	*Enter your Choice:\n");
		printf("	******************************************************************************************\n");
		int q;
		scanf("%d",&q);
		if(q==1){
			int x;
			printf("Enter data:\n");
			scanf("%d",&x);
			enqueue(&queue1,x);
			}
		else if(q==2){
			printf("%d\n",dequeue(&queue1));
			}
		else if(q==3){display(&queue1);}
		else{printf("Incorrect input\n");}		
		
	}
	else if(ch==2){
		printf("	******************************************************************************************\n");
		printf("	*1.Enqueue\n	*2.Dequeue\n	*3.Display\n	*Enter your Choice:\n");
		printf("	******************************************************************************************\n");
		int q;
		scanf("%d",&q);
		if(q==1){
			int x;
			printf("Enter data:\n");
			scanf("%d",&x);
			enqueue(&queue2,x);
			}
		else if(q==2){
			printf("%d\n",dequeue(&queue2));
			}
		else if(q==3){display(&queue2);}
		else{printf("Incorrect input\n");}}
	else if(ch==3){
		if(compare(&queue1,&queue2)==1){printf("Queue 1 is greater\n");}
		else if(compare(&queue1,&queue2)==-1){printf("Queue 2 is greater\n");}
		else if(compare(&queue1,&queue2)==0){printf("Queues are equal\n");}
	}	
	else{printf("Incorrect Input\n");}
}	
}
