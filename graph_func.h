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
void string_parser(char *input_str, char *output_str);
int initial_string_parser(char *input_str);
double calculation(char *output_str, double input_data, int *k);
void others(struct calc_stack **sp, char c, int *k);
void trigon(struct calc_stack **sp, char c, int *k);
void power(struct calc_stack **sp);
void divid(struct calc_stack **sp, int *k);
void mul(struct calc_stack **sp);
void sub(struct calc_stack **sp);
void add(struct calc_stack **sp);

#endif  // SRC_GRAPH_FUNC_H_"
