#ifndef SOL_H_INCLUDED
#define SOL_H_INCLUDED

int in_operators(char val);
void needed_func(q* heap, q* queue, char op);
int oper_prec(char op);
int prec(q* heap, char op);
void push_bracket(q* heap, q* queue);
void terminate_heap(q* heap, q* queue);
int encode_polish(q* heap, q* queue, char* expression, int n);
double calculate(char* expr, int n, double val);
double oper_1(char op, double a, double b);
int in_operators_2(char val);
void draw(char* expr);

#define x_len 80
#define y_len 25

#endif // SOL_H_INCLUDED
