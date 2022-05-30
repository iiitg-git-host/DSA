#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct playNode{	
    int num;
	char song[100];
	struct playNode* next;
};

void enqueue(struct playNode ** queue,char n[]){
	struct playNode *t =(struct playNode*)malloc(sizeof(struct playNode));
	if(*queue==NULL){t->num =1;}else{t->num = ((*queue)->num)+1;}	
	int i;
	for(i=0;n[i]!='\0';i++){
		t->song[i]=n[i];
	}
	t->song[i]='\0';
	t->next = *queue;
	*queue = t;
	printf("%s has been added.\n",t->song);	
}

void dequeue(struct playNode ** queue, char n[]){
	struct playNode* trav = *queue;
	while(strcmp(n,trav->next->song)!=0){
		if(trav==NULL){printf("No such song.");break;}
		trav = trav->next;
	}
	printf("%s has been removed.\n",trav->next->song);
	trav->next =trav->next->next;
}

void display(struct playNode ** queue){
	struct playNode* trav = *queue;
	while(trav!=NULL){
		printf(" %s ",trav->song,trav->num);
		trav = trav->next;
	}
	printf("\n");
}

int main(){
	struct playNode * queue =NULL;
	while(1){
	printf("*****************************************************************************************\n");
	printf("1.Add Song\n2.Remove Song\n3.Display Playlist\n4.Exit\nEnter your Choice:\n");
	printf("*****************************************************************************************\n");
	int ch;
	scanf("%d",&ch);
	getchar();
	if(ch==1){
		char n[100];
		printf("Enter song name:\n");
		scanf("%[^\n]%*c",n);
		enqueue(&queue,n);		
	}
	else if(ch==2){
		char n[100];
		printf("Enter name of song to remove:");
		scanf("%[^\n]%*c",n);
		dequeue(&queue,n);
	}
	else if(ch==3){display(&queue);}
	else{printf("Incorrect choice");}
	}
	
}
