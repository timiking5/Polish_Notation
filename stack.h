#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct Stack {
    struct Stack* next;
    double item;
} st;

st* createNode_h();
st* init_h();
void push_h(st* head, double val);
double pop_h(st* head);
void destroy_h(st* head);
int size_h(st* head);

#endif // STACK_H_INCLUDED
