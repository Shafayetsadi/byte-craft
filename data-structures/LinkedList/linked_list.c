#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

Node *newNode(void *data);
void insertBegin(Node **head, void *data);
void insertEnd(Node **head, void *data);
void insertIndex(Node **head, void *data, size_t index);
void *deleteBegin(Node **head);
void *deleteEnd(Node **head);
void *deleteIndex(Node **head, size_t index);
void printList(Node *head, void (*printData)(void *));
void freeList(Node *head);

void printInt(void *data) { printf("%d ", *((int *)data)); }
void printFloat(void *data) { printf("%f ", *((float *)data)); }
void printString(void *data) { printf("%s ", (char *)data); }

int main() {
  printf("Hello World!\n");

  int x = 10, y = 15, z = 20;
  Node *head = newNode(&x);
  insertBegin(&head, &y);
  insertBegin(&head, &z);
  printList(head, printInt);

  int *a = malloc(sizeof(int));
  *a = 5;
  // printf("%d\n", *(int *)a);
  insertIndex(&head, a, 3);
  printList(head, printInt);
  insertIndex(&head, a, 5);
  printList(head, printInt);

  insertEnd(&head, &x);
  insertEnd(&head, &y);
  insertEnd(&head, &z);
  printList(head, printInt);

  printf("Delete:\n");
  deleteBegin(&head);
  printList(head, printInt);
  deleteEnd(&head);
  printList(head, printInt);
  deleteIndex(&head, 2);
  printList(head, printInt);

  freeList(head);
}

Node *newNode(void *data) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

void insertBegin(Node **head, void *data) {
  Node *node = newNode(data);
  if (*head not_eq NULL) {
    (*head)->prev = node;
    node->next = *head;
  }
  *head = node;
}

void insertEnd(Node **head, void *data) {
  Node *curr = *head;
  if (curr == NULL) {
    insertBegin(head, data);
    return;
  }
  while (curr->next not_eq NULL) {
    curr = curr->next;
  }
  Node *node = newNode(data);
  node->prev = curr;
  curr->next = node;
}

void insertIndex(Node **head, void *data, size_t index) {
  if (index == 0) {
    insertBegin(head, data);
    return;
  }
  Node *curr = *head;
  size_t i = 1;
  while (curr not_eq NULL and i < index) {
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    printf("Index out of bound\n");
    return;
  }
  Node *node = newNode(data);
  if (curr->next == NULL) {
    curr->next = node;
    node->prev = curr;
  } else {
    node->next = curr->next;
    curr->next->prev = node;
    curr->next = node;
    node->prev = curr;
  }
}

void *deleteBegin(Node **head) {
  if (*head == NULL) {
    printf("List is empty\n");
    return NULL;
  }
  Node *temp = *head;
  *head = (*head)->next;
  if (*head not_eq NULL) {
    (*head)->prev = NULL;
  }
  void *data = temp->data;
  free(temp);
  return data;
}

void *deleteEnd(Node **head) {
  if (*head == NULL) {
    printf("List is empty\n");
    return NULL;
  }
  Node *curr = *head;
  while (curr->next not_eq NULL) {
    curr = curr->next;
  }
  if (curr->prev not_eq NULL) {
    curr->prev->next = NULL;
  } else {
    *head = NULL;
  }
  void *data = curr->data;
  free(curr);
  return data;
}

void *deleteIndex(Node **head, size_t index) {
  if (*head == NULL) {
    printf("List is empty\n");
    return NULL;
  }
  if (index == 0) {
    void *data = (*head)->data;
    deleteBegin(head);
    return data;
  }
  Node *curr = *head;
  size_t i = 0;
  while (curr not_eq NULL and i < index) {
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    printf("Index out of bound\n");
    return NULL;
  }
  void *data = curr->data;
  if (curr->prev not_eq NULL) {
    curr->prev->next = curr->next;
  }
  if (curr->next not_eq NULL) {
    curr->next->prev = curr->prev;
  }
  free(curr);
  return data;
}

void printList(Node *head, void (*printData)(void *)) {
  Node *curr = head;
  while (curr not_eq NULL) {
    printData(curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void freeList(Node *head) {
  while (head not_eq NULL) {
    Node *temp = head;
    head = head->next;
    temp->data = NULL;
    free(temp);
  }
}
