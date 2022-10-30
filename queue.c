#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


q* createNode() {
    q* temp = malloc(sizeof(q));
    temp -> next = NULL;
    return temp;
}

q* init() {
    q* head = createNode();
    head -> item = '?';
    head -> prev = NULL;
    return head;
}

int is_empty(q* head) {
    if (head -> next == NULL) return 1;
    return 0;
}

//    char remove_q(q* head) {
//    char bebra = head -> next -> item;
//    q* tmp = head -> next;
//    head -> next = head -> next -> next;
//    free(tmp);
//    return bebra;
//    }

void push(q* head, char val) {
    q* temp = head;
    q* p = createNode();
    p -> item = val;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    p -> prev = temp;
    temp -> next = p;
}

char pop(q* head) {
    q* temp = head;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    char resp = temp -> item;
    temp -> prev -> next = NULL;
    free(temp);
    return resp;
}

char* q_string(q* head) {
    q* tmp = head;
    int i = 0;
    while (tmp -> next != NULL) {
        i++;
        tmp = tmp -> next;
    }
    char* resp = malloc(sizeof(char) * (i + 1));
    tmp = head;
    i = 0;
    while (tmp -> next != NULL) {
        resp[i] = tmp -> next -> item;
        tmp = tmp -> next;
        i++;
    }
    resp[i] = '\0';
    return resp;
}

char on_top(q* head) {
    q* temp = head;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    return temp -> item;
}

void destroy(q* head) {
    q* temp;
    if (head -> next != NULL) {
        temp = head -> next;
        free(head);
    } else {
        free(head);
        return;
    }
    while (temp != NULL) {
        q* p = temp -> next;
        free(temp);
        temp = p;
    }
}

