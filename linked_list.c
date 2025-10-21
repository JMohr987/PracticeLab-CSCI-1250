#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"    

void push_back(List *list, void *item){
    Node *node = (Node *)malloc(sizeof(Node));
    node->element = item;
    node->nextElement = NULL;
    ++((*list).length);
    if(!list->tail){
        list->tail = node;
        list->head = node;
        return;
    }

    list->tail->nextElement = node; 
    list->tail = node;

}

void push_front(List *list, void *item){
    Node *node = (Node *)malloc(sizeof(Node));
    node->element = item;
    node->nextElement = NULL;
    ++((*list).length);
    if(!list->head){
        list->tail = node;
        list->head = node;
        return;
    }

    node->nextElement = list->head;
    list->head = node;
}

void pop(List *list, int index){
    if(index == 1){
        Node *temp = list->head;
        list->head = list->head->nextElement;
        if(temp->element){
            free(temp->element);
        }
        free(temp);
        temp = NULL;
        --(list->length);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    Node *previous = list->head;
    int i = 2;
    for(Node *it = list->head->nextElement; it != NULL; it = it->nextElement, ++i){
        if(i != index){
            previous = it;
            continue;
        }

        previous->nextElement = it->nextElement;
        if(it->element){
           free(it->element);
        }
        free(it);
        --(list->length);
        break;
    }
    
    if(previous->nextElement == NULL){
        list->tail = previous;
    }
}

void cleanup(List *list){
    for(Node *it = list->head; it != NULL; it = list->head){
        list->head = it->nextElement;
        if(it->nextElement){
            free(it->element);
        }
        free(it);
    }
    list->tail = NULL;
}
