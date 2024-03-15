#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// TODO: Fix the deleteData() function

struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
};

struct Node *newNode(void *data);
void insertBegin(struct Node **head, void *data);
void insertEnd(struct Node **head, void *data);
void insertIndex(struct Node **head, void *data, int index);
void *deleteBegin(struct Node **head);
void *deleteEnd(struct Node **head);
void *deleteData(struct Node **head, void *data);
void printList(struct Node *head, void (*printData)(void *));

void printInt(void *data) { printf("%d ", *((int *)data)); }

void printFloat(void *data) { printf("%f ", *((float *)data)); }

void printString(void *data) { printf("%s ", (char *)data); }

int main() {
  int *a = malloc(sizeof(int));
  *a = 5;
  // printf("%d\n", *(int *)a);
  printf("Hello World!\n");

  int x = 10, y = 15, z = 20;
  struct Node *head = newNode(&x);
  insertBegin(&head, &y);
  insertBegin(&head, &z);
  insertEnd(&head, &x);
  insertEnd(&head, &y);
  insertEnd(&head, &z);
  printList(head, printInt);
  insertIndex(&head, a, 3);
  printList(head, printInt);
  deleteBegin(&head);
  printList(head, printInt);
  deleteEnd(&head);
  printList(head, printInt);
  int *data = malloc(sizeof(int));
  *data = 15;
  deleteData(&head, data);
  printList(head, printInt);
}

struct Node *newNode(void *data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

void insertBegin(struct Node **head, void *data) {
  struct Node *node = newNode(data);
  (*head)->prev = node;
  node->next = *head;
  *head = node;
}

void insertEnd(struct Node **head, void *data) {
  struct Node *curr = *head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  struct Node *node = newNode(data);
  node->prev = curr;
  curr->next = node;
}

void insertIndex(struct Node **head, void *data, int index) {
  struct Node *curr = *head;
  int i = 1;
  while (curr not_eq NULL and i < index) {
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    printf("Out of index bound!\n");
    return;
  }
  struct Node *node = newNode(data);
  struct Node *temp = curr->next;
  curr->next = node;
  node->prev = curr;

  node->next = temp;
  temp->prev = node;
}

void *deleteBegin(struct Node **head) {
  void *temp = (*head)->data;
  *head = (*head)->next;
  return temp;
}

void *deleteEnd(struct Node **head) {
  struct Node *curr = *head;
  while (curr->next->next not_eq NULL) {
    curr = curr->next;
  }
  void *temp = curr->next->data;
  curr->next = NULL;
  return temp;
}

void *deleteData(struct Node **head, void *data) {
  struct Node *curr = *head;
  while (curr->next not_eq NULL) {
    if (curr->data == data) {
      break;
    }
    curr = curr->next;
  }
  if (curr->data == data) {
    struct Node *prev = curr->prev;
    struct Node *next = curr->next;
    void *temp = curr->data;
    prev->next = next;
    next->prev = prev;
    return temp;
  } else {
    printf("Data not found.\n");
    return NULL;
  }
}

void printList(struct Node *head, void (*printData)(void *)) {
  struct Node *curr = head;
  while (curr not_eq NULL) {
    printData(curr->data);
    curr = curr->next;
  }
  printf("\n");
}
