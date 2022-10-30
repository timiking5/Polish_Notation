#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"

st* createNode_h() {
    st* temp = malloc(sizeof(st));
    temp -> next = NULL;
    return temp;
}


st* init_h() {
    st* head = createNode_h();
    head -> item = '?';
    return head;
}

void push_h(st* head, double val) {
    st* temp = head;
    st* p = createNode_h();
    p -> item = val;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = p;
}

double pop_h(st* head) {
    st* temp = head;
    while (temp -> next -> next != NULL)
        temp = temp -> next;
    double resp = temp -> next -> item;
    free(temp -> next);
    temp -> next = NULL;

    return resp;
}

void destroy_h(st* head) {
    if (head -> next == NULL) {
        free(head);
    } else {
        st* temp = head -> next;
        free(head);
        while (temp != NULL) {
            st* p = temp -> next;
            temp -> next = NULL;
            free(temp);
            temp = p;
        }
    }
}

int size_h(st* head) {
    st* temp = head -> next;
    int cnt = 0;
    while (temp != NULL) {
        cnt++;
        temp = temp -> next;
    }
    return cnt;
}
