#include <stdio.h>
#include <stdlib.h>
struct node
{
    int info;
    struct node *left;
    struct node *right;
    int streeSum;
};
struct node *addNode(int key)
{
    struct node *node = malloc(sizeof(struct node));
    node->info = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int exponent(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    return base * exponent(base, exp - 1);
}

int mod(int x)
{
    if (x > 0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}

void isPresent(struct node *curr, int key, int *flag)
{
    if (curr == NULL)
    {
        return;
    }
    if (curr->info == key)
    {
        *flag = 1;
    }
    isPresent(curr->left, key, flag);
    isPresent(curr->right, key, flag);
}

int subSum(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->info + subSum(root->left) + subSum(root->right);
}
void putSubSum(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    root->streeSum = subSum(root);
    putSubSum(root->left);
    putSubSum(root->right);
}

int height(struct node *root)
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

void minimumSumDiff(struct node *root, struct node **minimumNode, int *min)
{
    if (root != NULL)
    {
        int sSumDiff;
        if (root->left != NULL && root->right != NULL)
        {
            sSumDiff = root->left->streeSum - root->right->streeSum;
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                sSumDiff = 0;
            }
            else if (root->left == NULL)
            {
                sSumDiff = -root->right->streeSum;
            }
            else if (root->right == NULL)
            {
                sSumDiff = root->left->streeSum;
            }
        }
        if (sSumDiff < *min)
        {
            *min = sSumDiff;
            *minimumNode = root;
        }
        minimumSumDiff(root->left, minimumNode, min);
        minimumSumDiff(root->right, minimumNode, min);
    }
}
void insertMinSumD(struct node **minimumNode, struct node *secondRoot, int *flag)
{
    if (*minimumNode == NULL || *flag == 1)
    {
        return;
    }
    if ((*minimumNode)->left != NULL && (*minimumNode)->right != NULL)
    {
        int diff = (*minimumNode)->left->streeSum - (*minimumNode)->right->streeSum;
        if (diff < 0)
        {
            while ((*minimumNode)->left != NULL)
            {
                (*minimumNode) = (*minimumNode)->left;
            }
            (*minimumNode)->left = secondRoot;
        }
        else
        {
            while ((*minimumNode)->right != NULL)
            {
                (*minimumNode) = (*minimumNode)->right;
            }
            (*minimumNode)->right = secondRoot;
        }
    }
    else
    {
        if ((*minimumNode)->left == NULL && (*minimumNode)->right == NULL)
        {
            (*minimumNode)->left = secondRoot;
        }
        else if ((*minimumNode)->left == NULL)
        {
            (*minimumNode)->left = secondRoot;
        }
        else if ((*minimumNode)->right == NULL)
        {
            (*minimumNode)->right = secondRoot;
        }
    }

    *flag = 1;
}
void insertMaxHD(struct node *root, struct node *secondRoot, int *flag)
{
    if (root == NULL || *flag == 1)
    {
        return;
    }
    if ((root->left->streeSum) - (root->right->streeSum) < 0)
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

void getNNodes(struct node *root, int *NNodes)
{
    if (root == NULL)
    {
        return;
    }
    getNNodes(root->left, NNodes);
    (*NNodes)++;
    getNNodes(root->right, NNodes);
}
void getNNodesLevel(struct node *root, int level, int *NNodes)
{
    if (level == 0 || root == NULL)
    {
        return;
    }
    else if (level == 1)
    {
        (*NNodes)++;
    }
    else if (level > 1)
    {
        getNNodesLevel(root->left, level - 1, NNodes);
        getNNodesLevel(root->right, level - 1, NNodes);
    }
}

void getInorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    getInorder(root->left);
    printf("%d(sum = %d)\t", root->info, root->streeSum);
    getInorder(root->right);
}
void getPreorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d(sum = %d)\t", root->info, root->streeSum);
    getPreorder(root->left);
    getPreorder(root->right);
}
void getPostorder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    getPostorder(root->left);
    getPostorder(root->right);
    printf("%d(sum = %d)\t", root->info, root->streeSum);
}
void printMenu(struct node *root)
{
    int printch;
    printf("1.Inorder \n2.Preorder \n3.Postorder \n");
    printf("Enter Your Choice:\n");
    scanf("%d", &printch);
    if (printch == 1)
    {
        getInorder(root);
    }
    else if (printch == 2)
    {
        getPreorder(root);
    }
    else if (printch == 3)
    {
        getPostorder(root);
    }
    else
    {
        printf("Invalid Choice");
    }
}

struct node *buildTree(int inArray[], int postArray[], int start, int end, int *postIndex)
{
    if (start > end)
    {
        return NULL;
    }
    struct node *temp = addNode(postArray[(*postIndex)--]);
    int r;
    for (int i = start; i <= end; i++)
    {
        if (inArray[i] == temp->info)
        {
            r = i;
            break;
        }
    }
    temp->right = buildTree(inArray, postArray, r + 1, end, postIndex);
    temp->left = buildTree(inArray, postArray, start, r - 1, postIndex);
    return temp;
}
struct node *buildTreeLogic(int postArray[], int inArray[], int size)
{
    int postIndex = size - 1;
    return buildTree(inArray, postArray, 0, size - 1, &postIndex);
}

void add(struct node *root, int key)
{
    if (root->left == NULL)
    {
        root->left = addNode(key);
    }
    else if (root->right == NULL)
    {
        root->right = addNode(key);
    }
}
void insertChild_logic(struct node *root, int key1, int key2)
{
    if (root != NULL)
    {
        if (root->info == key2)
        {
            if (root->left != NULL && root->right != NULL)
            {
                if ((root->left->streeSum) - (root->right->streeSum) > 0)
                {
                    add(root->right, key1);
                }
                else
                {
                    add(root->left, key1);
                }
            }
            else
            {
                if (root->left == NULL)
                {
                    root->left = addNode(key1);
                }
                else
                {
                    root->right = addNode(key1);
                }
            }
        }
        else
        {
            insertChild_logic(root->left, key1, key2);
            insertChild_logic(root->right, key1, key2);
        }
    }
}
void insertChild(struct node *root, int key1, int key2)
{
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    isPresent(root, key1, &checkFlag);
    isPresent(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1)
    {
        printf("Key1 is already present\n");
        return;
    }
    if (keyTwoCheckFlag == 0)
    {
        printf("Key2 not found\n");
        return;
    }
    insertChild_logic(root, key1, key2);
    putSubSum(root);
}

void delete (struct node **root, int *key, int *flag)
{
    if (*root == NULL || *flag == 1)
    {
        return;
    }
    if ((*root)->left == NULL && (*root)->right == NULL)
    {
        *flag = 1;
        *key = (*root)->info;
        *root = NULL;
        return;
    }
    delete (&((*root)->left), key, flag);
    delete (&((*root)->right), key, flag);
}
void deleteNode_logic(struct node **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    if ((*root)->info == key)
    {
        int flag = 0;
        int replacementKey;
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            *root = NULL;
            return;
        }
        else if ((*root)->left != NULL && (*root)->right != NULL)
        {
            if (((*root)->left->streeSum) - ((*root)->right->streeSum) > 0)
            {
                delete (&((*root)->left), &replacementKey, &flag);
            }
            else
            {
                delete (&((*root)->right), &replacementKey, &flag);
            }
        }
        else
        {
            if ((*root)->left == NULL)
            {
                delete (&((*root)->right), &replacementKey, &flag);
            }
            else if ((*root)->right == NULL)
            {
                delete (&((*root)->left), &replacementKey, &flag);
            }
        }

        (*root)->info = replacementKey;
    }
    deleteNode_logic(&((*root)->left), key);
    deleteNode_logic(&((*root)->right), key);
}
void deleteNode(struct node *root, int key)
{
    int flag = 0;
    isPresent(root, key, &flag);
    if (flag == 0)
    {
        printf("hai hi nahi!\n");
        return;
    }
    deleteNode_logic(&root, key);
}

void addNodeLevel(struct node *root, int level, int key, int *comp)
{
    if (level == 0 || *comp == 1)
    {
        return;
    }
    else if (level == 1)
    {
        if (root->left == NULL)
        {
            root->left = addNode(key);
            *comp = 1;
        }
        else if (root->right == NULL)
        {
            root->right = addNode(key);
            *comp = 1;
        }
    }
    else if (level > 1)
    {
        addNodeLevel(root->left, level - 1, key, comp);
        if (root->right == NULL && *comp == 0)
        {
            root->right = addNode(key);
            *comp = 1;
        }
        addNodeLevel(root->right, level - 1, key, comp);
    }
}
void levelInsert(struct node *root, int level, int key)
{
    int allNodes = exponent(2, level - 1);
    int currNodes = 0;
    getNNodesLevel(root, level, &currNodes);
    int NNodes = 0;
    getNNodesLevel(root, level + 1, &NNodes);
    if (currNodes == allNodes - 1 && NNodes == 0)
    {
        levelInsert(root, level + 1, key);
    }
    else
    {
        int comp = 0;
        addNodeLevel(root, level - 1, key, &comp);
    }
}
void insertChildv2(struct node *root, struct node **secondRoot, int key1, int key2)
{
    int checkFlag = 0;
    int keyTwoCheckFlag = 0;
    isPresent(root, key1, &checkFlag);
    isPresent(root, key2, &keyTwoCheckFlag);
    if (checkFlag == 1)
    {
        printf("Key1 is already present\n");
        return;
    }
    if (keyTwoCheckFlag == 0)
    {
        if (*secondRoot == NULL)
        {
            *secondRoot = addNode(key2);
            add(*secondRoot, key1);
        }
        else
        {
            int NNodes = 0;
            getNNodes(*secondRoot, &NNodes);
            if (NNodes == 6)
            {
                (*secondRoot)->right->right = addNode(key1);
                int m = root->left->streeSum - root->right->streeSum;
                struct node *minimumNode = root;
                minimumSumDiff(root, &minimumNode, &m);
                int flag = 0;
                insertMinSumD(&minimumNode, *secondRoot, &flag);
                *secondRoot = NULL;
            }
            else if (NNodes < 6)
            {
                int h = height(*secondRoot);
                levelInsert(*secondRoot, h, key1);
            }
        }
    }
    insertChild_logic(root, key1, key2);
    putSubSum(root);
}

int main()
{
    struct node *root = NULL;
    struct node *secondRoot = NULL;
    while (1)
    {
        printf("*********************************************************\n");
        printf("1.Build Tree from Inorder and PostOrder\n2.Insert Child\n3.Delete Node\n4.Revised Insert Child\n5.Print Primary Tree\n6.Print Secondary Tree\n7.Exit\n");
        printf("*********************************************************\nEnter Your Choice:\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 1)
        {
            // int size;
            // printf("Enter size of arrays:");
            // scanf("%d",&size);
            // int inArray[size],postArray[size];
            // for(int i=0;i<size;i++){printf("\nEnter element for inorder:");scanf("%d",&inArray[i]);}
            // for(int i=0;i<size;i++){printf("\nEnter element for postorder:");scanf("%d",&postArray[i]);}
            int size = 9;
            int inArray[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
            int postArray[] = {1, 4, 7, 6, 3, 13, 14, 10, 8};
            root = buildTreeLogic(postArray, inArray, size);
            putSubSum(root);
        }
        else if (ch == 2)
        {
            int key1, key2;
            printf("Enter key1\n");
            scanf("%d", &key1);
            printf("Enter key2\n");
            scanf("%d", &key2);
            insertChild(root, key1, key2);
            putSubSum(root);
        }
        else if (ch == 3)
        {
            int key;
            printf("Enter key to delete\n");
            scanf("%d", &key);
            deleteNode(root, key);
            putSubSum(root);
        }
        else if (ch == 4)
        {
            int key1, key2;
            printf("Enter key1\n");
            scanf("%d", &key1);
            printf("Enter key2\n");
            scanf("%d", &key2);
            insertChildv2(root, &secondRoot, key1, key2);
            putSubSum(root);
            putSubSum(secondRoot);
        }
        else if (ch == 5)
        {
            int NNodes = 0;
            getNNodes(root, &NNodes);
            if (NNodes == 0)
            {
                printf("No Tree!\n");
            }
            else
            {
                printMenu(root);
                printf("\n");
            }
        }
        else if(ch==6){
            int NNodes = 0;
            getNNodes(secondRoot, &NNodes);
            if (NNodes == 0)
            {
                printf("No Tree!\n");
            }
            else
            {
                printMenu(secondRoot);
                printf("\n");
            }
        }
        else if (ch == 7)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}