#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left,*right;
};
struct node * newNode(int key){
	struct node * temp = (struct node*)malloc(sizeof(struct node));
	temp->data = key;
	return temp;
}

int height(struct node * root){
	if(root==NULL){return 0;}
	int left = height(root->left);
	int right = height(root->right);
	if(left>right){return left+1;}else{return right+1;}	
}

void levelSum(struct node * root, int level, int * Sum){
	if(root==NULL){return;}
	else if(level==1){(*Sum) = (*Sum) + root->data;}
	else if(level>1){
		levelSum(root->left,level-1, Sum);
		levelSum(root->right,level-1, Sum);
	}
}

int maxLevelSum(struct node* root){
	int h = height(root);
	int max = 0;
	int maxLevel = 0;
	for(int i=1;i<h+1;i++){
		int lSum = 0;
		levelSum(root, i, &lSum);
		if(lSum>max){
			max = lSum;
			maxLevel = i;
//			printf("level %d has sum %d and currently max is %d\n",i,lSum,maxLevl);
		}
		
	}
	return maxLevel;
} 

struct node * build(int preOrder[], int inOrder[], int front, int rear, int* preIndex){
	if(rear<front){return NULL;}
	struct node * root = newNode(preOrder[(*preIndex)++]);
	if(front==rear){return root;}
	int r;
	for(r=front;r<=rear;r++){if(inOrder[r]==root->data){break;}}
	root->left = build(preOrder, inOrder, front,r-1,preIndex);
	root->right = build(preOrder, inOrder, r+1, rear, preIndex);
	return root;
}
struct node * treeFromPreAndIn(int preOrder[], int inOrder[], int front, int rear){
	int preIndex = 0;
	return build(preOrder, inOrder, front, rear, &preIndex);

}

void nHalfNodes(struct node* root, int* count){
	if(root==NULL){return;}	
	nHalfNodes(root->left,count);
	if((root->left==NULL && root->right!=NULL) || (root->left!=NULL && root->right ==NULL)){
		(*count)++;}
	nHalfNodes(root->right,count);
}

void printIn(struct node * root){
	if(root==NULL){return;}	
	printIn(root->left);
	printf("%d ",root->data);
	printIn(root->right);		
		
}
void printPre(struct node * root){
	if(root==NULL){return;}
	printf("%d ",root->data);
	printPre(root->left);
	printPre(root->right);
}



int main(){
	struct node* root =NULL;
	while(1>0){
		printf("******************************************************************\n");
		printf("1.buildTreeFromPreorderAndInorder()\n2.maxLevelSum()\n3.halfNodes()\n4.exit\n");
		printf("******************************************************************\n");
		int ch;
		printf("Enter your choice\n");
		scanf("%d",&ch);
		if(ch==1){
			int size;
			printf("Enter Size:\n");
			scanf("%d",&size);
			int preOrder[size],inOrder[size];
			//{8,3,11,6,4,7,10,14,13};
			//{11,3,4,6,7,8,10,13,14};
			for(int i=0;i<size;i++){
				printf("Enter element at index %d for preOrder\n",i);
				scanf("%d",&preOrder[i]);
			}
			for(int i=0;i<size;i++){
				printf("Enter element at index %d for InOrder\n",i);
				scanf("%d",&inOrder[i]);
			}
			root = treeFromPreAndIn(preOrder, inOrder, 0, size-1);
			printPre(root);
			printf("\n");
			printIn(root);
			printf("\n");
		}
		else if(ch==2){
						if(root==NULL){
							printf("No tree\n");
						}
						else{
							int maxLSum = maxLevelSum(root);
							printf("%d\n",maxLSum);
						}
		}
		else if(ch==3){
						if(root==NULL){
							printf("No tree\n");
						}
						else{
							int halfNodes=0;
							nHalfNodes(root,&halfNodes);
							printf("%d\n",halfNodes);		
						}
		}
		else if(ch==4){exit(0);}
		else{printf("Invalid Choice\n");}
	}
	 
	
	
	
		
}
