#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_STRING 20

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
	printf("\tBúsqueda usando A*\n");
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

void print_visited(int nodes, char names[nodes][LEN_STRING]){
	int i;
	printf("\n\n*******************************\n");
	printf("Nodos expandidos:  ");
	for (i = 0; i < visited_count; ++i)
		printf("%s, ", names[visited[i]]);
	printf("\n");
}

int is_visited(int index){
	int i;
	for (i = 0; i < visited_count; ++i)
		if (visited[i] == index)
			return 1;
	return 0;
}


int index_of(int nodes,
              char names[nodes][LEN_STRING],
              char name[LEN_STRING])
{
	int i;
	for (i = 0; i < nodes; ++i)
		if (!strcmp(name, names[i]))
			return i;

	return -1;
}

void put_error(const char *msg){
	printf("%s\n", msg);
	exit(0);
}

void read_data(int nodes,
               int matrix[nodes][nodes],
               int heuristic[nodes],
               char names[nodes][LEN_STRING],
               int* root, int* goal)
{
	// Inicializa los valores de entrada.

	int i, children, father, w;
	char tmp_name[LEN_STRING];

	// Se lee la tabla de la heurística
	// y se inicializa la matriz de adyacencia
	for (i = 0; i < nodes; ++i){
		scanf("%s %d", names[i], &heuristic[i]);

		for (w = 0; w < nodes; ++w)
			matrix[i][w] = 0;
	}

	// lectura de nodo fuente
	scanf("%s", tmp_name);

	*root = index_of(nodes, names, tmp_name);

	if (*root < 0)
		put_error("Parámetro no válido (fuente).\n");


	// lectura del objetivo
	scanf("%s", tmp_name);
	*goal = index_of(nodes, names, tmp_name);

	if (*goal < 0)
		put_error("Parámetro no válido (objetivo).\n");

	for (i = 0; i < nodes; ++i)
		matrix[i][*root] = 0;	

	// lee la cantidad de hijos
	scanf("%d", &children);

	while(children > 0) {
		// lee el nombre del padre
		scanf("%s", &tmp_name);
		
		father = index_of(nodes, names, tmp_name);

		if (father < 0)
			put_error("No se ha encontrado ese nodo (padre).\n");
		
		// comienza la lectura de los nombres
		// de lo hijos para generarlo a la matriz de adyacencia
		for (i = 0; i < children; ++i) {
			scanf("%s", &tmp_name);
			
			int child = index_of(nodes, names, tmp_name);

			if (child < 0)
				put_error("No se ha encontrado ese nodo (hijo).\n");

			scanf("%d", &w);

			matrix[father][child] = w;
		}

		scanf("%d", &children);
	}
	
	scanf("%d", root);

}

int is_goal(int root, int goal){
	if (root == goal)
		return 1;
	return 0;
}