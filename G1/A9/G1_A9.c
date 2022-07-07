#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *newNode(int data)
{
    struct node *new = malloc(sizeof(struct node));
    new->data = data;
    return new;
}

struct node *insert(struct node *node, int data)
{
    if (node == NULL)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    return node;
}
void inorderGenerator(int array[], int *i, struct node *root)
{
    if (root == NULL)
    {
        // printf("yes\n");
        return;
    }

    // printf("root->data : %d, i: %d", root->data, *i);
    inorderGenerator(array, i, root->left);

    array[(*i)++] = root->data;

    inorderGenerator(array, i, root->right);
}

int isSorted(int array[], int lowerLimit, int upperLimit)
{
    for (int i = lowerLimit; i < upperLimit - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

int isEqual(int inorder1[], int inorder2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (inorder1[i] != inorder2[i])
        {
            return 0;
        }
    }
    return 1;
}

int range(int inorder[], int size, int k1, int k2)
{
    for (int i = 0; i < size; i++)
    {
        if (inorder[i] < k2 && inorder[i] > k1)
        {
            printf("%d ", inorder[i]);
        }
    }
}

void print(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void Q1()
{
    struct node *root = newNode(20);
    root->left = newNode(40);
    root->right = newNode(30);
    root->left->left = newNode(50);
    int size = 4;
    int inorder[size];
    int idx = 0;
    inorderGenerator(inorder, &idx, root);
    print(inorder, 4);
    if (isSorted(inorder, 0, size - 1))
    {
        printf("Given Binary Tree is a BST\n");
    }
    else
    {
        printf("Not a BST\n");
    }
}

void Q2()
{
    struct node *BST1 = NULL;
    struct node *BST2 = NULL;
    int size;
    printf("enter size\n");
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter data\n");
        int data;
        scanf("%d", &data);
        BST1 = insert(BST1, data);
    }
    for (int i = 0; i < size; i++)
    {
        printf("Enter data\n");
        int data;
        scanf("%d", &data);
        BST2 = insert(BST2, data);
    }
    int inorder1[size], inorder2[size];
    int idx = 0;
    inorderGenerator(inorder1, &idx, BST1);
    idx = 0;
    inorderGenerator(inorder2, &idx, BST2);
    if (isEqual(inorder1, inorder2, size))
    {
        printf("Equal\n");
    }
    else
    {
        printf("Not Equal\n");
    }
}

void Q3()
{
    struct node *BST = NULL;
    int size;
    printf("enter size\n");
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        printf("Enter data\n");
        int data;
        scanf("%d", &data);
        BST = insert(BST, data);
    }
    int inorder[size];
    int idx = 0;
    inorderGenerator(inorder, &idx, BST);
    printf("Enter k1 and k2\n");
    int k1, k2;
    scanf("%d %d", &k1, &k2);
    range(inorder, size, k1, k2);
    
}

void Q4() {}

int main()
{
    while (1)
    {
        printf("*********************************************\n");
        printf("1 - Q1\n2 - Q2\n3 - Q3\n");
        printf("*********************************************\n");
        int q;
        scanf("%d", &q);
        if (q == 1)
        {
            Q1();
            printf("\n");
        }
        else if (q == 2)
        {
            Q2();
            printf("\n");
        }
        else if (q == 3)
        {
            Q3();
            printf("\n");
        }
        else if (q == 4)
        {
            Q4();
            printf("\n");
        }
        else if (q == 5)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice\n");
        }
    }
}