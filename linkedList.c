#include <stdio.h>

#include <stdlib.h>

struct node {
  int data;
  struct node * next;
}* main_list = NULL;
void reverse(struct node ** main_list) {
  struct node * prev = NULL;
  struct node * now = * main_list;
  struct node * next = NULL;
  while (now != NULL) {
    next = now -> next;
    now -> next = prev;
    prev = now;
    now = next;
  }* main_list = prev;
}
void insert(struct node ** main_list, int i, int k) {
  struct node * trav, * last, * t, * k_list = NULL;
  k_list = (struct node * ) malloc(sizeof(struct node));
  int temp;
  printf("Enter data:\n");
  scanf("%d", & temp);
  k_list -> data = temp;
  k_list -> next = NULL;
  last = k_list;
  for (int _ = 0; _ < k - 1; _++) {
    t = (struct node * ) malloc(sizeof(struct node));
    printf("Enter data:\n");
    scanf("%d", & temp);
    t -> data = temp;
    t -> next = NULL;
    last -> next = t;
    last = t;
  }
  trav = * main_list;
  for (int _ = 0; _ < i; _++) {
    trav = trav -> next;
  }
  struct node * nex;
  nex = trav -> next;
  trav -> next = k_list;
  last -> next = nex;
}
void del(struct node ** main_list, int i, int k) {
  struct node * trav;
  trav = * main_list;
  for (int _ = 0; _ < i; _++) {
    trav = trav -> next;
  }
  struct node * tempdel;
  tempdel = trav -> next;
  for (int _ = 0; _ < k; _++) {
    tempdel = tempdel -> next;
  }
  trav -> next = tempdel -> next;
}

void printList(struct node * main_list, int i, int k) {
  struct node * trav = main_list;
  for (int _ = 0; _ < i; _++) {
    trav = trav -> next;
  }
  for (int _ = 0; _ < k; _++) {
    printf("%d", trav -> data);
    trav = trav -> next;
  }
  printf("\n");
}
void printFullList(struct node * main_list) {
  struct node * trav = main_list;
  while (trav != NULL) {
    printf("%d ", trav -> data);
    trav = trav -> next;
  }
  printf("\n");
}

int main() {
  struct node * last, * t;
  main_list = (struct node * ) malloc(sizeof(struct node));
  int n, tempdata;
  printf("Enter no. Of Elements");
  scanf("%d", & n);
  printf("Enter data:\n");
  scanf("%d", & tempdata);
  main_list -> data = tempdata;
  main_list -> next = NULL;
  last = main_list;
  for (int i = 0; i < n - 1; i++) {
    t = (struct node * ) malloc(sizeof(struct node));
    printf("Enter data:\n");
    scanf("%d", & tempdata);
    t -> data = tempdata;
    t -> next = NULL;
    last -> next = t;
    last = t;
  }
  printFullList(main_list);
  while (1 > 0) {
    printf("Choose:\n 1.Insert Values\n2.Delete Values\n3.Reverse List\n4.Display List\n5.Display Full list.");
    int ch;
    scanf("%d", & ch);
    if (ch == 1) {
      int i, k;
      printf("Enter the position at which you want to add new elements\n");
      scanf("%d", & i);
      printf("Enter the number of elements\n");
      scanf("%d", & k);
      insert( & main_list, i, k);
    } else if (ch == 2) {
      int id, kd;
      printf("Enter the position at which you want to start deleting elements\n");
      scanf("%d", & id);
      printf("Enter the number of elements to delete");
      scanf("%d", & kd);
      del( & main_list, id, kd);
    } else if (ch == 3) {
      reverse( & main_list);
      printf("Reversed");
    } else if (ch == 4) {
      int ip, kp;
      printf("Enter the position to at which you want to start printing elements\n");
      scanf("%d", & ip);
      printf("Enter the number of elements to print\n");
      scanf("%d", & kp);
      printList(main_list, ip, kp);
    } else if (ch == 5) {
      printFullList(main_list);
    } else {
      printf("Invalid Choice");
    }
  }
}
