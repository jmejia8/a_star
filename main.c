#include "tools.c"
#include "queue.c"

void a_star(int nodes,
            int matrix[nodes][nodes],
            int heuristic[nodes],
            char names[nodes][LEN_STRING],
            int goal,
            Queue** _front)
{

	Queue* front = *_front;
	
	int i, j;

	// Se extrae el nodo con el menor costo de la
	// cola de prioridad
	Queue* tmp = dequeue(&front);
	
	// La cola vacía significa que
	// el objetivo no puede ser alcanzado
	// con los parámetros dados
	if (tmp == NULL){
		printf("Objetivo No encontrado.\n");
		exit(0);
	}

	// Extraemos los valores del nodo
	int root = tmp->index;
	int cost = tmp->cost;

	// Si no se ha marcado como visitado,
	// entonces se hace.
	if (!is_visited(root)){
		visited[visited_count] = root;
		visited_count++;
	}


	// Imprime los nodos visitados o expandidos
	print_visited(nodes, names);

	// Si encontramos el objetivo se muestra
	// la cola y se imprime la solución
	if (is_goal(root, goal)){
		print_queue(&front, nodes, names);

		printf("\n\nSolución:\n");

		// imprime la solución
		for ( i = 0; i < tmp->path_len; ++i){
			printf("%s -> ", names[tmp->path[i]]);
		}

		// imprime el costo y termina ejecución del programa
		printf("(%d)\n", tmp->cost);
		printf("\n===================================\n");
		exit(0);
	}

	// Se expande el nodo root
	for (i = 0; i < nodes; ++i){
		
		if (matrix[root][i] == 0) continue;

		// Crea el nuevo nodo para agregarlo a la cola
		// Se agrega su identificador y el costo
		Queue* new_node = create_node(i, cost + matrix[root][i], heuristic[i]);
		matrix[i][root] = 0;

		// Se agrega la ruta para llegar a este nodo
		for (j = 0; j < tmp->path_len; ++j)
			new_node->path[j] = tmp->path[j];

		new_node->path[j] = i;
		new_node->path_len = tmp->path_len + 1;

		// Se agrega a la cola de prioridad
		enqueue(&front, new_node);

	}

	// imprime la cola
	print_queue(&front, nodes, names);

	// Se libera la memoria
	free(tmp);

	// Hacer esto hasta que la cola esté vacía
	a_star(nodes, matrix, heuristic, names, goal, &front);
}


int main(int argc, char const *argv[])
{

	greeting();

	int nodes, root, goal;
	scanf("%d", &nodes);

	if (nodes <= 0)
	{
		printf("Error, parámetro no válido\n");
		exit(0);
	}

	// matriz de adyacencia
	int matrix[nodes][nodes];
	int heuristic[nodes];
	char names[nodes][LEN_STRING];

	// Incializa la matriz de adyacencia, el nodo fuente y el
	// objetivo a localizar
	read_data(nodes, matrix, heuristic, names, &root, &goal);

	// apuntador de la cola
	Queue* front = NULL;

	// Creamos el nodo fuente y se agrega a la 
	// cola vacía
	Queue* new_node = create_node(root, 0, heuristic[root]);
	new_node->path[0] = root;
	new_node->path_len = 1;

	enqueue(&front, new_node);

	// Inicia búsqueda de costo uniforme 
	a_star(nodes, matrix, heuristic, names, goal, &front);


	return 0;
}