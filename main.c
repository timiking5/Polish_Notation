#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "sol.h"



int main() {
    // стадия 1
    int err = 0;
    char express[100];
    int z = 0;
    scanf("%c", &express[z]);
    z++;
    while (express[z - 1] != '\n') {
        scanf("%c", &express[z]);
        z++;
    }
    express[z - 1] = '\0';
    q* heap = init();
    q* queue = init();
    if (encode_polish(heap, queue, express, strlen(express)) == 1) {
        char * answer = q_string(queue);
        // стадия 1 закончилась
        draw(answer);  // стадия 2 началась и закончилась
        // стадия 3 - прорисовка
        destroy(heap);
        destroy(queue);
        free(answer);
    } else {
        err = 1;
    }

    if (err == 1) {
        printf("n/a");
    }
    return 0;
}

void draw(char* expr) {
    char field[y_len][x_len];
    char c = '*';
    for (int i = 0; i < y_len; i++)
        for (int j = 0; j< x_len; j++)
            field[i][j] = '.';
    for (double i = 0; i <= 4 * M_PI; i += 4 * M_PI / 160) {
        double resp = calculate(expr, strlen(expr), i);
        if ((resp >= -1) && (resp <= 1))
            field[(int)(round(12 * resp + 12))][(int)(round(i * 6.36))] = c;
    }
    for (int i = 0; i < y_len; i++) {
        for (int j = 0; j < x_len; j++) {
            printf("%c", field[i][j]);
        }
        if (i != y_len - 1) printf("\n");
    }
}

double oper_1(char op, double a, double b) {
    double resp = 1;
    if (op == '+') {
        resp = a + b;
    } else if (op == '-') {
        resp = a - b;
    } else if (op == '*') {
        resp = a * b;
    } else if (op == '^') {
        resp = pow(a, b);
    } else if (op == '/') {
        resp = a / b;
    }
    return resp;
}

double oper_2(char op, double a) {
    double resp = 1;
    if (op == 't') {
        resp = tan(a);
    } else if (op == 'g') {
        resp =  pow(tan(a), -1);
    } else if (op == 'c') {
        resp =  cos(a);
    } else if (op == 's') {
        resp = sin(a);
    } else if (op == 'l') {
        resp = log(a);
    } else if (op == 'q') {
        resp = sqrt(a);
    } else if (op == '|') {
        resp = (-1)*a;
    }
    return resp;
}

double calculate(char* expr, int n, double val) {
    st* stack = init_h();
    for (int i = 0; i < n; i++) {
        if (expr[i] == 'x') {
            push_h(stack, val);
        } else if ((expr[i] == '-') && (size_h(stack) == 1)) {
            double a = pop_h(stack) * (-1);
            push_h(stack, a);
        } else if ((expr[i] >= '0') && (expr[i] <= '9')) {
            push_h(stack, expr[i] - '0');
        } else if (in_operators(expr[i]) == 1) {
            double a = pop_h(stack);
            double b = pop_h(stack);
            push_h(stack, oper_1(expr[i], b, a));
        } else if (in_operators_2(expr[i]) == 1) {
            double a = pop_h(stack);
            push_h(stack, oper_2(expr[i], a));
        }
    }
    double resp = pop_h(stack);
    destroy_h(stack);
    return resp;
}

int in_operators(char val) {
    int err = 0;
    char operator[] = {'^', '*', '/', '+', '-'};
    for (int i = 0; i < 5; i++) {
        if (val == operator[i]) err = 1;
    }
    return err;
}

int in_operators_2(char val) {
    int err = 0;
    char operator[] = {'|', 'q', 'l', 't', 'g', 'c', 's'};
    for (int i = 0; i < 7; i++) {
        if (val == operator[i]) err = 1;
    }
    return err;
}

void needed_func(q* heap, q* queue, char op) {
    if (is_empty(heap)) {
        push(heap, op);
    } else if (on_top(heap) == '(') {
        push(heap, op);
    } else if (prec(heap, op) == 0) {
        push(queue, pop(heap));
        push(heap, op);
    } else if (prec(heap, op) == 1) {
        push(queue, pop(heap));
        push(heap, op);
    } else if (prec(heap, op) == -1) {
        push(heap, op);
    }
}

int oper_prec(char op) {
    int err = -1;
    char operator[] = {'|', 'q', 'l', 't', 'g', 'c', 's', '^', '*', '/', '+', '-'};
    const int precedence[] = {3, 5, 5, 5, 5, 5, 5, 4, 3, 3, 2, 2};
    for (int i = 0; i < 12; i++) {
        if (err == -1) {
            if (op == operator[i]) {
                err = precedence[i];
            }
        }
    }
    return err;
}

int prec(q* heap, char op) {
    q* temp = heap;
    int err = 6;
    while (temp -> next != NULL)
        temp = temp -> next;
    if (op == '^' && (oper_prec(on_top(heap)) == 4)) {
        err = -1;
    } else if (oper_prec(temp -> item) > oper_prec(op)) {
        err = 1;
    } else if (oper_prec(temp -> item) == oper_prec(op)) {
        err = 0;
    } else if (oper_prec(temp -> item) < oper_prec(op)) {
        err = -1;
    }
    return err;
}

void push_bracket(q* heap, q* queue) {
    q* temp = heap;
    if (!is_empty(heap) && (on_top(heap) != '(')) {
        while (temp -> next != NULL)
            temp = temp -> next;
        temp = temp -> prev;
        push(queue, pop(heap));
        while (temp -> item != '(') {
            temp = temp -> prev;
            push(queue, pop(heap));
        }
        pop(heap);
    } else {
        pop(heap);
    }
}

void terminate_heap(q* heap, q* queue) {
    while (!is_empty(heap)) {
        push(queue, pop(heap));
    }
}


int encode_polish(q* heap, q* queue, char* expression, int n) {
    int err = 1;
    for (int i = 0; i < n; i++) {
        if (expression[i] == 'x') {
            push(queue, expression[i]);
        } else if ((expression[i] >= '0') && (expression[i] <= '9')) {
            push(queue, expression[i]);
        } else if ((expression[i] == '-') && !((expression[i - 1] >= '0') \
                && (expression[i - 1] <= '9')) && !(expression[i - 1] == 'x')) {
            needed_func(heap, queue, '|');
        } else if (in_operators(expression[i])) {
            needed_func(heap, queue, expression[i]);
        } else if (expression[i] == '(') {
            push(heap, expression[i]);
        } else if (expression[i] == ')') {
            push_bracket(heap, queue);
        } else if ((expression[i] == 's') && (expression[i + 1] == 'i') && (expression[i + 2] == 'n')) {
            needed_func(heap, queue, expression[i]);
            i += 2;
        } else if ((expression[i] == 'c') && (expression[i + 1] == 'o') && (expression[i + 2] == 's')) {
            needed_func(heap, queue, expression[i]);
            i += 2;
        } else if ((expression[i] == 'c') && (expression[i + 1] == 't') && (expression[i + 2] == 'g')) {
            needed_func(heap, queue, 'g');
            i += 2;
        } else if ((expression[i] == 't') && (expression[i + 1] == 'a') && (expression[i + 2] == 'n')) {
            needed_func(heap, queue, expression[i]);
            i += 2;
        } else if ((expression[i] == 'l') && (expression[i + 1] == 'n')) {
            needed_func(heap, queue, expression[i]);
            i += 1;
        } else if ((expression[i] == 's') && (expression[i + 1] == 'q') \
        && (expression[i + 2] == 'r') && (expression[i + 3] == 't')) {
            needed_func(heap, queue, 'q');
            i += 3;
        } else {
            err = 0;
        }
    }
    terminate_heap(heap, queue);
    return err;
}
