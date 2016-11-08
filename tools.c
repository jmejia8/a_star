#include <stdio.h>
#include <stdlib.h>

const char names[] = {'A', 'B', 'C', 'D', 'E',
					'F', 'G', 'H', 'I', 'J',
					'K', 'L', 'M', 'N', 'O',
					'P', 'Q', 'R', 'S', 'T',
					'U', 'V', 'W', 'X', 'Y', 'Z',
					'1', '2', '3', '4', '5','6',
					'7', '8', '9', '0'
				};

int visited[100];
int visited_count = 0;

void greeting(){
	printf("=============================================\n");
	printf("\tBúsqueda de Costo Uniforme\n");
	printf("=============================================\n");
}


void printmatrix(int nodes, int matrix[nodes][nodes]){
	int i, j;

	printf("\n");
	
	for (i = 0; i < nodes; ++i)
	{
		for (j = 0; j < nodes; ++j)
		{
			printf("%d\t", matrix[i][j]);
		}

		printf("\n");
	}

	printf("\n");
}

void print_visited(){
	int i;
	printf("\nNodos expandidos:  ");
	for (i = 0; i < visited_count; ++i)
		printf("%c, ", names[visited[i]]);
	printf("\n");
}

int is_visited(int index){
	int i;
	for (i = 0; i < visited_count; ++i)
		if (visited[i] == index)
			return 1;
	return 0;
}