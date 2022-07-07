#include <stdio.h>
#include <stdlib.h>
struct tnode
{
    int data;
    struct tnode *left;
    struct tnode *right;
    int hd;
};
struct node
{
    struct tnode *tree;
    struct node *next;
};
struct tnode *newNode(int key)
{
    struct tnode *tnode = malloc(sizeof(struct tnode));
    tnode->data = key;
    tnode->left = NULL;
    tnode->right = NULL;
    return tnode;
}
struct node *newTree(struct tnode *root)
{
    struct node *tempTree = malloc(sizeof(struct node));
    tempTree->tree = root;
    tempTree->next = NULL;
    return tempTree;
}

//              Utilities
int power(int base, int exp) { return exp == 0 ? 1 : base * power(base, exp - 1); }
int absolute(int x) { return x > 0 ? x : -x; }
int height(struct tnode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left = height(root->left);
        int right = height(root->right);
        if (left > right)
        {
            return (left + 1);
        }
        else
        {
            return (right + 1);
        }
    }
}
void check(struct tnode *curr, int key, int *flag)
{
    if (curr == NULL)
    {
        return;
    }
    if (curr->data == key)
    {
        *flag = 1;
    }
    check(curr->left, key, flag);
    check(curr->right, key, flag);
}
void updateTree(struct tnode *root)
{
    if (root == NULL)
    {
        return;
    }
    root->hd = height(root->left) - height(root->right);
    updateTree(root->left);
    updateTree(root->right);
}
void maxHD(struct tnode *root, int *maxhd)
{
    if (root == NULL)
    {
        return;
    }
    if (absolute(root->hd) > absolute(*maxhd))
    {
        *maxhd = root->hd;
    }
    maxHD(root->left, maxhd);
    maxHD(root->right, maxhd);
}
void insertMaxHD(struct tnode *root, struct tnode *secondRoot, int maxhd, int *flag)
{
    if (root == NULL || *flag == 1)
    {
        return;
    }
    if (root->hd == maxhd)
    {
        if ((root->hd) > 0)
        {
            if (root->left == NULL)
            {
                root->left = secondRoot;
            }
            else
            {
                while (root->left != NULL)
                {
                    root = root->left;
                }
                root->left = secondRoot;
            }
        }
        else
        {
            if (root->right == NULL)
            {
                root->right = secondRoot;
            }
            else
            {
                while (root->right != NULL)
                {
                    root = root->right;
                }
                root->right = secondRoot;
            }
        }
        *flag = 1;
    }
    insertMaxHD(root->left, secondRoot, maxhd, flag);
    insertMaxHD(root->right, secondRoot, maxhd, flag);
}
void countNodes(struct tnode *root, int *count)
{
    if (root == NULL)
    {
        return;
    }
    (*count)++;
    countNodes(root->left, count);
    countNodes(root->right, count);
}
void countNodesAtLevel(struct tnode *root, int level, int *count)
{
    if (level == 0 || root == NULL)
    {
        return;
    }
    else if (level == 1)
    {
        (*count)++;
    }
    else if (level > 1)
    {
        countNodesAtLevel(root->left, level - 1, count);
        countNodesAtLevel(root->right, level - 1, count);
    }
}

//          Printing
void printInorder(struct tnode *root)
{
    if (root == NULL)
    {
        return;
    }
    printInorder(root->left);
    printf("%d -> height-difference : %d\t", root->data, root->hd);
    printInorder(root->right);
}
void printPreorder(struct tnode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d -> height-difference : %d\t", root->data, root->hd);
    printPreorder(root->left);
    printPreorder(root->right);
}
void printPostorder(struct tnode *root)
{
    if (root == NULL)
    {
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d -> height-difference : %d\t", root->data, root->hd);
}
void print(struct tnode *root)
{
    int printch;
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| 1.Inorder()\t\t\t|\n| 2.Preorder()\t\t\t|\n| 3.Postorder()\t\t\t|\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter YOur Choice:\n");
    scanf("%d", &printch);
    if (printch == 1)
    {
        printInorder(root);
    }
    else if (printch == 2)
    {
        printPreorder(root);
    }
    else if (printch == 3)
    {
        printPostorder(root);
    }
    else
    {
        printf("Invalid Choice");
    }
}
void showSecondaryTrees(struct node *trees)
{
    printf("Current secondary trees: rootNode(no. of nodes)\n");
    struct node *temp = trees->next;
    while (temp != NULL)
    {
        int count = 0;
        countNodes(temp->tree, &count);
        printf("%d(%d)\t", temp->tree->data, count);
        temp = temp->next;
    }
    printf("\n");
}
//          Tree Host
void addTree(struct node **tree, struct tnode *root)
{
    if (*tree == NULL)
    {
        *tree = newTree(root);
    }
    else
    {
        struct node *temp = *tree;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTree(root);
    }
}
struct tnode *find(struct node *tree, int key)
{
    struct node *temp = tree->next;
    while (temp != NULL)
    {
        if (temp->tree->data == key)
        {
            return temp->tree;
        }
        temp = temp->next;
    }
    return NULL;
}
//          Building

struct tnode *initTreeFromPreAndIn(int inOrder[], int preOrder[], int front, int rear, int *preIndex)
{
    if (front > rear)
    {
        return NULL;
    }
    struct tnode *newnode = newNode(preOrder[(*preIndex)++]);
    int r;
    for (int i = front; i <= rear; i++)
    {
        if (inOrder[i] == newnode->data)
        {
            r = i;
            break;
        }
    }
    newnode->left = initTreeFromPreAndIn(inOrder, preOrder, front, r - 1, preIndex);
    newnode->right = initTreeFromPreAndIn(inOrder, preOrder, r + 1, rear, preIndex);
    return newnode;
}
struct tnode *treeFromPreAndIn(int preOrder[], int inOrder[], int size)
{
    int preIndex = 0;
    return initTreeFromPreAndIn(inOrder, preOrder, 0, size - 1, &preIndex);
}
//          Inserting

void insert(struct tnode *root, int key)
{
    if (root->left == NULL)
    {
        root->left = newNode(key);
        
    }
    else if (root->right == NULL)
    {
        root->right = newNode(key);
    
    }
}
void nsydeInsertChild(struct tnode *root, int key1, int key2)
{
    if (root != NULL)
    {
        if (root->data == key2)
        {
            if (root->left != NULL && root->right != NULL)
            {
                if (root->hd > 0)
                {
                    insert(root->right, key1);
                }
                else
                {
                    insert(root->left, key1);
                }
            }
            else
            {
                if (root->left == NULL)
                {
                    root->left = newNode(key1);
                }
                else
                {
                    root->right = newNode(key1);
                }
            }
        }
        else
        {
            nsydeInsertChild(root->left, key1, key2);
            nsydeInsertChild(root->right, key1, key2);
        }
    }
}
void insertChild(struct tnode *root, int key1, int key2)
{
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    check(root, key1, &checkFlag);
    check(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1)
    {
        printf("pehle se hi ek hai\n");
        return;
    }
    if (keyTwoCheckFlag == 0)
    {
        printf("Nahi mila\n");
        return;
    }
    nsydeInsertChild(root, key1, key2);
    updateTree(root);
}
//          Deleting

void delete (struct tnode **root, int *key, int *flag)
{
    if (*root == NULL || *flag == 1)
    {
        return;
    }
    if ((*root)->left == NULL && (*root)->right == NULL)
    {
        *flag = 1;
        *key = (*root)->data;
        *root = NULL;
        return;
    }
    delete (&((*root)->left), key, flag);
    delete (&((*root)->right), key, flag);
}
void nsydeDeleteNode(struct tnode **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    if ((*root)->data == key)
    {
        int flag = 0;
        int replacementKey;
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            *root = NULL;
            return;
        }
        else
        {
            if ((*root)->hd >= 0)
            {
                delete (&((*root)->left), &replacementKey, &flag);
            }
            else
            {
                delete (&((*root)->right), &replacementKey, &flag);
            }
            (*root)->data = replacementKey;
        }
    }
    nsydeDeleteNode(&((*root)->left), key);
    nsydeDeleteNode(&((*root)->right), key);
}
void deleteNode(struct tnode *root, int key)
{
    int flag = 0;
    check(root, key, &flag);
    if (flag == 0)
    {
        printf("hai hi nahi!\n");
        return;
    }
    nsydeDeleteNode(&root, key);
}
//          Revised Inserting

void levelInsert(struct tnode *root, int level, int key, int *done)
{
    if (level == 0 || *done == 1)
    {
        return;
    }
    else if (level == 1)
    {
        if (root->left == NULL)
        {
            root->left = newNode(key);
            *done = 1;
        }
        else if (root->right == NULL)
        {
            root->right = newNode(key);
            *done = 1;
        }
    }
    else if (level > 1)
    {
        levelInsert(root->left, level - 1, key, done);
        if (root->right == NULL && *done == 0)
        {
            root->right = newNode(key);
            *done = 1;
        }
        levelInsert(root->right, level - 1, key, done);
    }
}
void levelCheck(struct tnode *root, int level, int key)
{
    int allNodes = power(2, level - 1);
    int currNodes = 0;
    countNodesAtLevel(root, level, &currNodes);
    int count = 0;
    countNodesAtLevel(root, level + 1, &count);
    // printf("All nodes = %d , Curr Nodes = %d\n", allNodes,currNodes);
    // printf("nodes at level %d = %d\n",level+1,count);
    if (currNodes == allNodes - 1 && count == 0)
    {
        levelCheck(root, level + 1, key);
    }
    else
    {
        int done = 0;
        levelInsert(root, level - 1, key, &done);
    }
}
void reInsertChild(struct tnode *root, struct tnode **secondRoot, int key1, int key2)
{
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    check(root, key1, &checkFlag);
    check(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1)
    {
        printf("pehle se hi ek hai\n");
        return;
    }
    if (keyTwoCheckFlag == 0)
    {
        if (*secondRoot == NULL)
        {
            *secondRoot = newNode(key2);
            insert(*secondRoot, key1);
        }
        else
        {
            int count = 0;
            countNodes(*secondRoot, &count);
            if (count == 6)
            {
                (*secondRoot)->right->right = newNode(key1);
                int m = 0;
                maxHD(root, &m);
                int flag = 0;
                insertMaxHD(root, *secondRoot, m, &flag);
                *secondRoot = NULL;
            }
            else if (count < 6)
            {
                int h = height(*secondRoot);
                levelCheck(*secondRoot, h, key1);
            }
        }
    }
    nsydeInsertChild(root, key1, key2);
    updateTree(root);
}
//          Driver Code

int main()
{
    struct node *treeHost = NULL;
    while (1)
    {
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("| 1.buildTree()\t\t\t\t\t\t|\n| 2.insertChild()\t\t\t\t\t|\n| 3.deleteNode()\t\t\t\t\t|\n| 4.reInsertChild()\t\t\t\t\t|\n| 5.print()\t\t\t\t\t\t|\n| 6.exit\t\t\t\t\t\t|\n");
        printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter Your Choice:\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 1)
        {
            int size;
            printf("Enter size of Inorder and Preorder arrays:");
            scanf("%d",&size);
            int inOrder[size],preOrder[size];
            for(int i=0;i<size;i++){printf("Enter element at index %d fror inorder ",i);scanf("%d",&inOrder[i]);}
            for(int i=0;i<size;i++){printf("Enter element at index %d fror preorder ",i);scanf("%d",&preOrder[i]);}
            // int size = 9;int inOrder[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};int preOrder[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
            // int size = 9;
            // int inOrder[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
            // int preOrder[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
            addTree(&treeHost, treeFromPreAndIn(preOrder, inOrder, size));
            updateTree(treeHost->tree);
            printInorder(treeHost->tree);
            printf("\n");
        }
        else if (ch == 2)
        {
            int key1, key2;
            printf("Enter key1\n");
            scanf("%d", &key1);
            printf("Enter key2\n");
            scanf("%d", &key2);
            insertChild(treeHost->tree, key1, key2);
            updateTree(treeHost->tree);
        }
        else if (ch == 3)
        {
            int key;
            printf("Enter key to delete\n");
            scanf("%d", &key);
            deleteNode(treeHost->tree, key);
            updateTree(treeHost->tree);
        }
        else if (ch == 4)
        {
            int key1, key2;
            printf("Enter key1\n");
            scanf("%d", &key1);
            printf("Enter key2\n");
            scanf("%d", &key2);
            struct tnode *secondRoot = find(treeHost, key2);
            if (secondRoot == NULL)
            {
                struct tnode *secondRoot = newNode(key2);
                secondRoot->left = newNode(key1);
                addTree(&treeHost, secondRoot);
            }
            else
            {
                reInsertChild(treeHost->tree, &secondRoot, key1, key2);
            }
            updateTree(treeHost->tree);
            updateTree(secondRoot);
        }
        else if (ch == 5)
        {
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
            printf("| 1.MainTree()\t\t\t\t|\n| 2.AnyOtherTree()\t\t\t|\n");
            printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\nEnter YOur Choice:\n");
            int pch;
            scanf("%d", &pch);
            if (pch == 1)
            {
                int count = 0;
                countNodes(treeHost->tree, &count);
                if (count == 0)
                {
                    printf("Tree is Empty!\n");
                }
                else
                {
                    print(treeHost->tree);
                    printf("\n");
                }
            }
            else if (pch == 2)
            {
                showSecondaryTrees(treeHost);
                int key;
                printf("Enter Value of root node\n");
                scanf("%d", &key);
                struct tnode *secondRoot = find(treeHost, key);
                if (secondRoot == NULL)
                {
                    printf("No tree found!\n");
                }
                else
                {
                    print(secondRoot);
                    printf("\n");
                }
            }
            else
            {
                printf("Invalid Choice!\n");
            }
        }
        else if (ch == 6)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}