#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * newList = (List*)malloc(sizeof(List));

  if (newList != NULL)
  {
    newList->head = NULL;
  }
     return newList;
}

void * firstList(List * list) {
    if(list->head == NULL)
    {
      return NULL;
    }

  list->current = list->head;
  
  return list->current->data;
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL) 
  {
      return NULL;
  }
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list->head == NULL || list->tail == NULL)
  {
    return NULL;
  }

  list->current = list->tail;

  return list->current->data;
}

void * prevList(List * list) {
    if (list->head == NULL || list->current == NULL || list->current->prev == NULL) 
    {
        return NULL;
    }

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *newNode = createNode(data);

  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode; 
  }
  else
  {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  struct Node* newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        if (list->current == NULL) {
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        } else {
            newNode->prev = list->current;
            newNode->next = list->current->next;
            if (list->current->next != NULL) {
                list->current->next->prev = newNode;
            } else {
                list->tail = newNode;
            }
            list->current->next = newNode;
        }
    }
    list->current = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL)
    {
      return NULL;
    }
    
    struct Node* currentNode = list->current;
    void* data = currentNode->data;

    if (currentNode->prev != NULL) {
        currentNode->prev->next = currentNode->next;
    } else {
        list->head = currentNode->next;
    }

    if (currentNode->next != NULL) {
        currentNode->next->prev = currentNode->prev;
    } else {
        list->tail = currentNode->prev;
    }

    list->current = currentNode->next; 

    free(currentNode);

    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}