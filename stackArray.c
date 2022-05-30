#include <stdio.h>

void push(int* min,int stack[],int* top,int n){
    int x;
    printf("Enter Data");
    scanf("%d",&x);
    if(*top==-1){
        stack[n-1]=x;
        *top = n-1;
        *min = x;
    }
    else if(*top==0){
        printf("Stack is full\n");
    }
    else{
        if(x>*min){
            stack[(*top)-1]=x;
            *top=*top-1;
            }
        else{
        stack[(*top)-1]=2*x-(*min);
        *min = x;
        *top=*top-1;}
    }
}

void pop(int *min, int stack[], int *top, int n){
    if(*top==-1){printf("Stack is Empty\n");}
    else{
        int x = stack[(*top)];
        if(x<*min){*min =2*(*min) - x;} 
    }
    if((*top)==n-1){
        (*top)=-1;}
    else{(*top)++;}

}

int top(int stack[],int *top){
    if(*top==-1){printf("Stack is Empty\n");}
    else{return stack[(*top)];}
}

int isEmpty(int *top){
    if(*top==-1){return 1;}
    else{return 0;}
}

int isFull(int *top){
    if(*top==0){
        return 1;
    }else{
    return 0;}

}

int findMin(int *min){
    return *min;
}

int main()
{
    int n;
    printf("Length of the array\n");
    scanf("%d",&n);
    int top =-1;
    int min = -1;
    int minStack[n];
    for(int i=0;i<n;i++){
    push(&min,minStack,&top,n);}

    return 0;
}
