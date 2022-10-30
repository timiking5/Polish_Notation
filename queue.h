#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct Queue {
    struct Queue* next;
    struct Queue* prev;
    char item;
} q;

q* createNode();
q* init();
char remove_q(q* head);
void push(q* head, char val);
char* q_string(q* head);
char pop(q* head);
int is_empty(q* head);
char on_top(q* head);
void destroy(q* head);

#endif // QUEUE_H_INCLUDED
