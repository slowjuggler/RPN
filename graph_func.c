#include "graph_func.h"

void stack_destroy(struct stack *top) {
    struct stack *temp;
    temp = top;
    while (temp != NULL) {
        struct stack *prev = temp;
        temp = temp->ptr;
        free(prev);
    }
}

void stack_calc_destroy(struct calc_stack *top) {
    struct calc_stack *temp;
    temp = top;
    while (temp != NULL) {
        struct calc_stack *prev = temp;
        temp = temp->ptr;
        free(prev);
    }
}

void push(struct stack **top, char new_data) {
    struct stack *new_ptr = (struct stack*)malloc(sizeof(struct stack));
    if (new_ptr == NULL) {
		stack_destroy(*top);
        printf("can't get memory");
        exit(1);
    }
    new_ptr->data = new_data;
    if (top == NULL) {
        *top = new_ptr;
    } else {
        new_ptr->ptr = *top;
        *top = new_ptr;
    }
}

void pop(struct stack **top, char *out) {
    struct stack *temp;
    temp = *top;
    *out = temp->data;
    *top = temp->ptr;
    free(temp);
}

void calc_push(struct calc_stack **top, double new_data) {
    struct calc_stack *new_ptr = (struct calc_stack*)malloc(sizeof(struct calc_stack));
    if (new_ptr == NULL) {
		stack_calc_destroy(*top);
        printf("can't get memory");
        exit(1);
    }
    new_ptr->data = new_data;
    if (top == NULL) {
        *top = new_ptr;
    } else {
        new_ptr->ptr = *top;
        *top = new_ptr;
    }
}

void calc_pop(struct calc_stack **top, double *out) {
    struct calc_stack *temp;
    temp = *top;
    *out = temp->data;
    *top = temp->ptr;
    free(temp);
}

void output(struct stack *top) {
    struct stack *temp, *prev;
    temp = top;
    while (temp) {
        prev = temp;
        temp = temp->ptr;
        printf("%c %p\n", prev->data, temp);
    }
}

int get_priority(char c) {
    int res = 0;
    if (c == '(') {
	res = 1;
    }
    if (c == '+' || c == '-') {
    	res = 2;
    }
    if (c == '*' || c == '/' || (c >= 'a' && c<= 'z')) {
       res = 3;
    }
    if (c == '^') {
       res = 4;
    }
    return res;
}

int initial_string_parser(char *input_str) {
	int res = 0;
	int brack_open = 0;
	int brack_close = 0;
	for (char *p = input_str; *p != '\0'; p++) {
		if (*p == 's' && !strncmp(p, SIN, 3)) {
			p = p + 3;
		}
		if (*p == 's' && !strncmp(p, SQRT, 4)) {
			p = p + 4;
		}
		if (*p == 't' && !strncmp(p, TAN, 2)) {
			p = p + 2;
		}
		if (*p == 'c' && !strncmp(p, COS, 3)) {
			p = p + 3;
		}
		if (*p == 'c' && !strncmp(p, CTAN, 3)) {
			p = p + 3;
		}	
		if (*p == 'l' && !strncmp(p, LOG, 2)) {
			p = p + 2;
		}
		if (*p == 'e' && !strncmp(p, EXP, 3)) {
			p = p + 3;
		}
		if (*p == '(') {
			brack_open++;
		}
		if (*p == ')') {
			brack_close++;
		}
		if ((*p >= 'a' && *p < 'x') || (*p > 'x' && *p <= 'z')) {
			res = 1;
		}
		if (*p == '(' && *(p + 1) == '-') {
			res = 1;
		}
	}
	res = res + (brack_open - brack_close);
	return res;
}
		
void string_parser(char *input_str, char *output_str) {
    struct stack *sp = NULL;
    int k = 0;
    for (char *p = input_str; *p != '\0'; p++) {
	if (*p == '-' && *(p - 1) == '(') {
	    output_str[k++] = 'z';
	}
        if ((*p >= '0' && *p <= '9') || *p == 'x') {
            output_str[k++] = *p;
        }
        if (*p == 's' && !strncmp(p, SIN, 3)) {
            push(&sp, 's');
            p += 3;
        }
        if (*p == 'c' && !strncmp(p, COS, 3)) {
            push(&sp, 'c');
            p += 3;
        }
        if (*p == 't' && !strncmp(p, TAN, 2)) {
            push(&sp, 't');
            p += 2;
        }
        if (*p == 'c' && !strncmp(p, CTAN, 3)) {
            push(&sp, 'g');
            p += 3;
        }
        if (*p == 's' && !strncmp(p, SQRT, 4)) {
            push(&sp, 'q');
            p += 4;
        }
        if (*p == 'l' && !strncmp(p, LOG, 2)) {
            push(&sp, 'l');
            p += 2;
        }
        if (*p == 'e' && !strncmp(p, EXP, 3)) {
	    push(&sp, 'e');
	    p +=3;
	}
        if (*p == '(') {
            push(&sp, '(');
        }
        if (*p == ')') {
            while (sp->data != '(') {
                char temp;
                pop(&sp, &temp);
                output_str[k++] = temp;
            }
            char temp;
            pop(&sp, &temp);
        }
        if (*p == '/' || *p == '+' || *p == '*' || *p == '-' || *p == '^') {
            if (sp != NULL) {
                int n = get_priority(*p);
                char t = sp->data;
                int m = get_priority(t);
                if (m >= n) {
                    char temp;
                    pop(&sp, &temp);
                    output_str[k++] = temp;
                }
                push(&sp, *p);
            }
            if (sp == NULL) {
                push(&sp, *p);
            }
        }
    }
    while (sp != NULL) {
        char temp;
        pop(&sp, &temp);
        output_str[k++] = temp;
    }
    output_str[k] = '\0';
    stack_destroy(sp);
}

void add(struct calc_stack **sp) {
    double x, y, z;
    calc_pop(sp, &x);
    calc_pop(sp, &y);
    z = x + y;
    calc_push(sp, z);
}
           
void sub(struct calc_stack **sp) {
     double x, y, z;
     calc_pop(sp, &x);
     calc_pop(sp, &y);
     z = y - x;
     calc_push(sp, z);
}

void mul(struct calc_stack **sp) {
    double x, y, z;
    calc_pop(sp, &x);
    calc_pop(sp, &y);
    z = y * x;
    calc_push(sp, z);
}

void divid(struct calc_stack **sp, int *k) {
    double x, y, z;
    calc_pop(sp, &x);
    calc_pop(sp, &y);
    if (x == 0) {
	*k = 1;
	return;
    }
    z = y / x;
    calc_push(sp, z);
}

void power(struct calc_stack **sp) {
    double x, y, z;
    calc_pop(sp, &x);
    calc_pop(sp, &y);
    z = pow(y, x);
    calc_push(sp, z);
}

void trigon(struct calc_stack **sp, char c, int *k) {
    if (c == 's') {
        double x, y;
        calc_pop(sp, &x);
        y = sin(x);
        calc_push(sp, y);
    }
    if (c == 'c') {
        double x, y;
        calc_pop(sp, &x);
        y = cos(x);
        calc_push(sp, y);
    }
    if (c == 't') {
        double x, y;
        calc_pop(sp, &x);
	if (x >= (M_PI/2)) {
            *k = 1;
             return;
	}
        y = tan(x);
        calc_push(sp, y);
     }
     if (c == 'g') {
         double x, y;
         calc_pop(sp, &x);
         if (x >= (M_PI/2) || x == 0) {
             *k = 1;
             return;
         }
         y = 1/tan(x);
         calc_push(sp, y);
     }
}

void others(struct calc_stack **sp, char c, int *k) {
    if (c == 'q') {
        double x, y;
        calc_pop(sp, &x);
        if (x < 0) {
            *k = 1;
             return;
        }
        y = sqrt(x);
        calc_push(sp, y);
    }
    if (c == 'e') {
        double x, y;
        calc_pop(sp, &x);
        y = exp(x);
        calc_push(sp, y);
    }
    if (c == 'l') {
	double x, y;
	calc_pop(sp, &x);
	if (x <= 0) {
            *k = 1;
             return;
        }
        y = log(x);
        calc_push(sp, y);
    }
}
	
double calculation(char *output_str, double input_data, int *k) {
    double result = 0;
    struct calc_stack *sp = NULL;
    for (char *p = output_str; *p != '\0'; p++) {
	if (*p == 'z' && *(p + 1) >= '0' && *(p + 1) <= '9') {
            double x = *(p + 1) - '0';
            double temp = (-1) * x;
            calc_push(&sp, temp);
        } else 	if (*p >= '0' && *p <= '9' && *(p - 1) != 'z') {
            double x = *p - '0';
            calc_push(&sp, x);
        }
	if (*p == 'x') {
	    calc_push(&sp, input_data);
        }
        if (*p == '+') {
	    add(&sp);
        }
        if (*p == '-') {
	    sub(&sp);
        }
        if (*p == '*') {
            mul(&sp);
        }
        if (*p == '/') {
            divid(&sp, k);
        }
        if (*p == '^') {
            power(&sp);
        }
        if (*p == 'l' || *p == 'q' || *p == 'e') {
            others(&sp, *p, k);
        }
        if (*p == 's' || *p == 'c' || *p == 'g' || *p == 't') {
            trigon(&sp, *p, k);
        }
    }
    calc_pop(&sp, &result);
    stack_calc_destroy(sp);
    return result;
}
