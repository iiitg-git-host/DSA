#include <stdio.h>
#include <stdlib.h>
struct tnode{
    int data;
    struct tnode *left;
    struct tnode *right;
    int streeSum;
};
struct tnode *newNode(int key){
    struct tnode *tnode = malloc(sizeof(struct tnode));
    tnode->data = key;
    tnode->left = NULL;
    tnode->right = NULL;
    return tnode;
}
//          Utilities

int power(int base, int exp){if(exp==0){return 1;}return base * power(base,exp-1);}
int absolute(int x){if(x>0){return x;}else{return -x;}}
void check(struct tnode *curr, int key, int *flag){
    if (curr == NULL){return;}
    if (curr->data == key){*flag = 1;}
    check(curr->left, key, flag);    
    check(curr->right, key, flag);
}
int subSum(struct tnode *root){
    if(root==NULL){return 0;}
    return root->data + subSum(root->left)+ subSum(root->right);
}
void updateTree(struct tnode *root){
    if (root == NULL){return;}
    root->streeSum = subSum(root);
    updateTree(root->left);    
    updateTree(root->right);
}
int height(struct tnode *root){
    if (root == NULL){
        return 0;
    }
    else{
        int left = height(root->left);
        int right = height(root->right);
        if (left > right){
            return (left + 1);
        }
        else{
            return (right + 1);
        }
    }
}
void minSumD(struct tnode *root,struct tnode **minSumNode,int *min){
    if(root!=NULL){
        printf("i am %d",root->data);
        int sSumDiff;
        if(root->left!=NULL && root->right!=NULL){
            sSumDiff = root->left->streeSum - root->right->streeSum;            
        }
        else{
            if(root->left==NULL && root->right ==NULL){sSumDiff=0;}
            else if(root->left==NULL){sSumDiff=-root->right->streeSum;}
            else if(root->right==NULL){sSumDiff= root->left->streeSum;}
        }
        if(sSumDiff<*min){*min = sSumDiff;*minSumNode = root;}
        minSumD(root->left,minSumNode,min);
        minSumD(root->right,minSumNode,min);
    }
}
void insertMinSumD(struct tnode **minSumNode, struct tnode *secondRoot, int *flag){
    if (*minSumNode == NULL || *flag ==1){return;}
    if((*minSumNode)->left!=NULL && (*minSumNode)->right!=NULL){
        int diff = (*minSumNode)->left->streeSum - (*minSumNode)->right->streeSum;
        if(diff<0){while((*minSumNode)->left!=NULL){(*minSumNode)=(*minSumNode)->left;}(*minSumNode)->left = secondRoot;}
        else{while((*minSumNode)->right!=NULL){(*minSumNode)=(*minSumNode)->right;}(*minSumNode)->right = secondRoot;}
    }
    else{
        if((*minSumNode)->left==NULL && (*minSumNode)->right ==NULL){(*minSumNode)->left = secondRoot;}
        else if((*minSumNode)->left==NULL){(*minSumNode)->left = secondRoot;}
        else if((*minSumNode)->right==NULL){(*minSumNode)->right = secondRoot;}
    }
        
    *flag = 1;
}
void insertMaxHD(struct tnode *root, struct tnode *secondRoot, int *flag){
    if (root == NULL || *flag ==1){return;}
        if((root->left->streeSum)-(root->right->streeSum)<0){
            if(root->left==NULL){root->left = secondRoot;}
            else{
                while(root->left!=NULL){root=root->left;}
                root->left = secondRoot;
            }
        }
        else{
            if(root->right==NULL){root->right = secondRoot;}
            else{
                while(root->right!=NULL){root=root->right;}
                root->right = secondRoot;
            }
        }
        *flag = 1;
}
void countNodes(struct tnode *root, int *count){
    if (root == NULL){return;}
    countNodes(root->left, count);
    (*count)++;
    countNodes(root->right, count);
}
void countNodesAtLevel(struct tnode *root, int level, int *count){
    if(level==0 || root ==NULL){return;}
    else if(level==1){(*count)++;}
    else if(level>1){countNodesAtLevel(root->left,level-1,count);countNodesAtLevel(root->right,level-1,count);}

}
//         Printing            

void printInorder(struct tnode *root){
    if (root == NULL){return;}
    printInorder(root->left);
    printf("%d -> sum : %d\t", root->data, root->streeSum);
    printInorder(root->right);
}
void printPreorder(struct tnode *root){
    if (root == NULL){return;}
    printf("%d -> sum : %d\t", root->data, root->streeSum);
    printPreorder(root->left);
    printPreorder(root->right);
}
void printPostorder(struct tnode *root){
    if (root == NULL){return;}
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d -> sum : %d\t", root->data, root->streeSum);
}
void print(struct tnode *root){
    int printch;
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| 1.Inorder()\t\t\t|\n| 2.Preorder()\t\t\t|\n| 3.Postorder()\t\t\t|\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter YOur Choice:\n");
    scanf("%d",&printch);
    if(printch==1){printInorder(root);}
    else if(printch==2){printPreorder(root);}
    else if(printch==3){printPostorder(root);}
    else{printf("Invalid Choice");}
    
}
//          Building

struct tnode *initTreeFromPostAndIn(int inOrder[], int postOrder[], int front, int rear, int *postIndex){
    if (front > rear){return NULL;}
    struct tnode *temp = newNode(postOrder[(*postIndex)--]);
    int r;
    for (int i = front; i <= rear; i++){
        if (inOrder[i] == temp->data){r = i;break;}
    }
    temp->right = initTreeFromPostAndIn(inOrder, postOrder, r + 1, rear, postIndex);
    temp->left = initTreeFromPostAndIn(inOrder, postOrder, front, r - 1, postIndex);
    return temp;
}
struct tnode *treeFromPostAndIn(int postOrder[], int inOrder[], int size){
    int postIndex = size-1;
    return initTreeFromPostAndIn(inOrder, postOrder, 0, size - 1, &postIndex);
}
// //          Inserting

void insert(struct tnode *root, int key){
    if (root->left == NULL){
        root->left = newNode(key);
    }
    else if (root->right == NULL){
        root->right = newNode(key);
    }
}
void nsydeInsertChild(struct tnode *root, int key1, int key2){
    if (root != NULL){
        if (root->data == key2){
            if (root->left != NULL && root->right != NULL){
                if ((root->left->streeSum)-(root->right->streeSum) > 0){insert(root->right, key1);}
                else{insert(root->left, key1);}
            }
            else{
                if (root->left == NULL){root->left = newNode(key1);}
                else{root->right = newNode(key1);}
            }
        }
        else{
            nsydeInsertChild(root->left, key1, key2);
            nsydeInsertChild(root->right, key1, key2);
        }
    }
}
void insertChild(struct tnode *root, int key1, int key2){
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    check(root, key1, &checkFlag);
    check(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1){
        printf("pehle se hi ek hai\n");
        return;
    }
    if (keyTwoCheckFlag == 0){
        printf("Nahi mila\n");
        return;
    }
    nsydeInsertChild(root, key1, key2);
    updateTree(root);
}
//          Deleting

void delete (struct tnode **root, int *key, int *flag){
    if (*root == NULL || *flag ==1){return;}
    if ((*root)->left == NULL && (*root)->right == NULL){
        *flag = 1;
        *key = (*root)->data;
        *root = NULL;
        return;
    }
    delete (&((*root)->left), key, flag);
    delete (&((*root)->right), key, flag);
}
void nsydeDeleteNode(struct tnode **root, int key){
    if (*root == NULL){return;}
    if ((*root)->data == key){
        int flag = 0;
        int replacementKey;
        if((*root)->left==NULL && (*root)->right ==NULL){*root=NULL;return;}
        else if ((*root)->left!=NULL && (*root)->right!=NULL){
            if(((*root)->left->streeSum)-((*root)->right->streeSum) >0){delete (&((*root)->left), &replacementKey, &flag);}
            else{delete (&((*root)->right), &replacementKey, &flag);}
        }
        else{
            if((*root)->left==NULL){delete (&((*root)->right), &replacementKey, &flag);}
            else if((*root)->right==NULL){delete (&((*root)->left), &replacementKey, &flag);}
        }
        
        (*root)->data = replacementKey;
    }
    nsydeDeleteNode(&((*root)->left), key);
    nsydeDeleteNode(&((*root)->right), key);
}
void deleteNode(struct tnode *root, int key){
    int flag = 0;
    check(root, key, &flag);
    if (flag == 0){printf("hai hi nahi!\n");return;}
    nsydeDeleteNode(&root, key);
}
//          Revised Inserting

void levelInsert(struct tnode* root, int level, int key, int* done){
    if(level==0 || *done ==1){return;}
    else if(level==1){
        if(root->left==NULL){root->left=newNode(key);*done=1;}
        else if(root->right==NULL){root->right=newNode(key);*done=1;}
    }
    else if(level>1){
        levelInsert(root->left,level-1,key,done);
        if(root->right==NULL && *done ==0){root->right= newNode(key);*done=1;}
        levelInsert(root->right,level-1,key,done);
    }
}
void levelCheck(struct tnode* root, int level, int key){
    int allNodes = power(2, level-1);
    int currNodes=0;
    countNodesAtLevel(root, level, &currNodes);
    int count = 0;
    countNodesAtLevel(root,level+1,&count);
    //printf("All nodes = %d , Curr Nodes = %d\n", allNodes,currNodes);
    //printf("nodes at level %d = %d\n",level+1,count);
    if(currNodes==allNodes-1 && count==0){
        levelCheck(root, level+1,key);
    }
    else{
        int done=0;
        levelInsert(root,level-1,key,&done);
    }
}
void reInsertChild(struct tnode *root, struct tnode **secondRoot, int key1, int key2){
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    check(root, key1, &checkFlag);
    check(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1){
        printf("pehle se hi ek hai\n");
        return;
    }
    if (keyTwoCheckFlag == 0){   
        if(*secondRoot==NULL){
            *secondRoot = newNode(key2);
            insert(*secondRoot,key1);
        }
        else{
            int count = 0;
            countNodes(*secondRoot,&count);
            if(count==6){
                (*secondRoot)->right->right = newNode(key1);
                int m = root->left->streeSum - root->right->streeSum;
                struct tnode * minSumNode = root;
                minSumD(root,&minSumNode,&m);
                printf("\n%d,,,,%d\n",m,minSumNode->data);
                int flag = 0;
                insertMinSumD(&minSumNode,*secondRoot, &flag);
                *secondRoot =NULL;
            }
            else if(count<6){
                int h = height(*secondRoot);
                levelCheck(*secondRoot,h,key1);
            }            
        }
    }
    nsydeInsertChild(root, key1, key2);
    updateTree(root);
}
//          Driver Code

int main()
{   struct tnode *root =NULL;
    struct tnode *secondRoot = NULL;
    while(1){
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("| 1.buildTree()\t\t\t\t\t\t|\n| 2.insertChild()\t\t\t\t\t|\n| 3.deleteNode()\t\t\t\t\t|\n| 4.reInsertChild()\t\t\t\t\t|\n| 5.print()\t\t\t\t\t\t|\n| 6.exit\t\t\t\t\t\t|\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter Your Choice:\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            // int size;
            // printf("Enter size of Inorder and Postorder arrays:");
            // scanf("%d",&size);
            // int inOrder[size],postOrder[size];
            // for(int i=0;i<size;i++){printf("Enter element at index %d fror inorder ",i);scanf("%d",&inOrder[i]);}
            // for(int i=0;i<size;i++){printf("Enter element at index %d fror postorder ",i);scanf("%d",&preOrder[i]);}
            int size = 9;int inOrder[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};int postOrder[] = {1, 4, 7, 6, 3, 13, 14, 10, 8};
            root = treeFromPostAndIn(postOrder, inOrder, size);
            updateTree(root);
            printf("\n");
            printInorder(root);printf("\n");
            printPostorder(root);printf("\n");
//            updateTree(root);
        }
        else if(ch==2){
            int key1,key2;
            printf("Enter key1\n");scanf("%d",&key1);
            printf("Enter key2\n");scanf("%d",&key2);
            insertChild(root,key1,key2);
            updateTree(root);
            printf("\n");
            printInorder(root);printf("\n");
            printPostorder(root);printf("\n");

        }
        else if(ch==3){
            int key;
            printf("Enter key to delete\n");
            scanf("%d",&key);
            deleteNode(root,key);
            printf("\n");
            printInorder(root);printf("\n");
            printPostorder(root);printf("\n");
            updateTree(root);
            printf("\n");
            printInorder(root);printf("\n");
            printPostorder(root);printf("\n");
        }
        else if(ch==4){
            int key1,key2;
            printf("Enter key1\n");
            scanf("%d",&key1);
            printf("Enter key2\n");
            scanf("%d",&key2);
            reInsertChild(root,&secondRoot,key1,key2);
            updateTree(root);
            updateTree(secondRoot);
        }
        else if(ch==5){
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
            printf("| 1.MainTree()\t\t\t\t|\n| 2.SecondTree()\t\t\t|\n");
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter YOur Choice:\n");
            int pch;
            scanf("%d",&pch);
            if(pch==1){
                int count=0;
                countNodes(root,&count);
                if(count==0){printf("Tree is Empty!\n");}
                else{print(root);printf("\n");}    
            }
            else if(pch==2){
                int count=0;
                countNodes(secondRoot,&count);
                if(count==0){printf("Tree is Empty!\n");}
                else{print(secondRoot);printf("\n");}
            }
            else{printf("Invalid Choice!\n");}            
        }
        else if(ch==6){exit(0);}
        else{printf("Invalid Choice!\n");}
    }
}