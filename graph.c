#include "graph_func.h"

#define MAX_SIZE 100
#define MAX_Y 25
#define MAX_X 80
#define ZERO 13
#define C_DEL 12
#define COEFF 0.5

void data_process(char *output_str, int *out_len) {
    int output_array[MAX_Y][MAX_X] = {0};
    int j = 0;
    int k = 0;
    for (int i = 0; i < MAX_X; i++) {
        double t = M_PI * 4 / MAX_X * i;
        double temp = calculation(output_str, out_len, t, &k);
        j = (int)(ZERO + temp * C_DEL - COEFF);
        if (k == 0) {
            if (j < MAX_Y) {
                output_array[j][i] = 1;
            }
        }
        k = 0;
    }
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (output_array[i][j] == 1)  {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main() {
    char input_str[MAX_SIZE] = {0};
    char output_str[MAX_SIZE] = {0};
    int out_len = 0;
    scanf("%s", input_str);
    int n = strlen(input_str);
    input_str[n] = '\0';
    if (initial_string_parser(input_str) == 0) {
		string_parser(input_str, output_str, &out_len);
		data_process(output_str, &out_len);
	} else {
		printf("Uncorrect equation! Please try again!\n");
	}
    return 0;
}


