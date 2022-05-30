#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node * next;
};

struct node* build(){
    struct node *main_list, *t,*last;
    main_list = NULL;
    int n;
    printf("Enter the length of linked list\n");
    scanf("%d", &n);
	t =(struct node*) malloc( sizeof(struct node));
        int data;
        printf("Enter Data");
        scanf("%d",&data);
        t-> data = data;
        t->next = NULL;
        main_list = t;
	last = t;
    for( int i=0;i<n-1;i++){
         t =(struct node*) malloc( sizeof(struct node));
         printf("Enter Data");
         scanf("%d",&data);
         t-> data = data;
         t->next = NULL;
	last->next = t;
	last = t;}
    return main_list;

}

struct node* copy( struct node **main_list){
    struct node *clist,*t,*last;
    t = (struct node*) malloc(sizeof(struct node));
    clist = t;
    t-> data = (*main_list) -> data;
    t-> next = NULL;
    last = t;
    *main_list= (*main_list)->next;
    while(*main_list!= NULL){
        t=(struct node*)malloc(sizeof(struct node));
        t->data = (*main_list) -> data;
        t->next = NULL;
        last-> next = t;
	last = t;
        *main_list= (*main_list)->next;
        
	}
    return clist;

}

int llength(struct node * main_list){
	struct node * trav = main_list;
	int cnt =0;
	while((trav)!=NULL){
		cnt++;
		trav = (trav)->next;	
	}
	return cnt;}

int compll(struct node**main_list,struct node**sec_list){
	if(llength(*main_list)==llength(*sec_list)){
		struct node *trav1 = *main_list, *trav2 = *sec_list;				
		while(trav1!=NULL){
			if(trav1->data == trav2->data){trav1= trav1->next;trav2=trav2->next;continue;}
			else if(trav1->data > trav2->data){return 1;}
			else{return -1;}
		}
		return 0;
		
	}else if (llength(*main_list)>llength(*sec_list)){return 1;}else{return -1;}
}

void printList(struct node **main_list){
	struct node * trav = *main_list;
	while((trav)!=NULL){
		printf("%d ",(trav)->data);
		trav = (trav)->next;	
	}
	printf("\n");
}

int main(){
        struct node* first_list = build();
	printList(&first_list);
	struct node* second_list = build();
	printList(&second_list);
	printf("%d",compll(&first_list,&second_list));
    
}
