#ifndef SRC_GRAPH_FUNC_H_
#define SRC_GRAPH_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define COS "cos"
#define SIN "sin"
#define TAN "tg"
#define CTAN "ctg"
#define SQRT "sqrt"
#define LOG "ln"
#define EXP "exp"

struct stack {
    char data;
    struct stack *ptr;
};

struct calc_stack {
    double data;
    struct calc_stack *ptr;
};

void stack_destroy(struct stack *top);
void stack_calc_destroy(struct calc_stack *top);
void push(struct stack **top, char new_data);
void pop(struct stack **top, char *out);
void calc_push(struct calc_stack **top, double new_data);
void calc_pop(struct calc_stack **top, double *out);
void output(struct stack *top);
int get_priority(char c);
void string_parser(char *input_str, char *output_str, int *out_len);
int initial_string_parser(char *input_str);
double calculation(char *output_str, int *out_len, double input_data, int *k);

#endif  // SRC_GRAPH_FUNC_H_"
