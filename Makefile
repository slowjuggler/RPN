all: graph.c graph_func.c
	gcc -o graph -Wall -Werror -Wextra graph.c graph_func.c -lm
