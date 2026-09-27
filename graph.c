#include <stdio.h>

#define V 6

char vertex[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

/* Undirected graph:
   A-B, A-C, B-D, B-E, C-F, E-F
*/

/* Adjacency Matrix */
int matrix[V][V] = {
    {0, 1, 1, 0, 0, 0},  /* A */
    {1, 0, 0, 1, 1, 0},  /* B */
    {1, 0, 0, 0, 0, 1},  /* C */
    {0, 1, 0, 0, 0, 0},  /* D */
    {0, 1, 0, 0, 0, 1},  /* E */
    {0, 0, 1, 0, 1, 0}   /* F */
};

/* Adjacency List */
int adj[V][V] = {
    {1, 2, -1, -1, -1, -1},  /* A -> B,C */
    {0, 3, 4, -1, -1, -1},   /* B -> A,D,E */
    {0, 5, -1, -1, -1, -1},  /* C -> A,F */
    {1, -1, -1, -1, -1, -1}, /* D -> B */
    {1, 5, -1, -1, -1, -1},  /* E -> B,F */
    {2, 4, -1, -1, -1, -1}   /* F -> C,E */
};

void printMatrix(void) {
    int i, j;
    printf("ADJACENCY MATRIX\n");
    printf("    A B C D E F\n");

    for (i = 0; i < V; i++) {
        printf("%c : ", vertex[i]);
        for (j = 0; j < V; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void printList(void) {
    int i, j;
    printf("\nADJACENCY LIST\n");

    for (i = 0; i < V; i++) {
        printf("%c -> ", vertex[i]);
        for (j = 0; j < V && adj[i][j] != -1; j++)
            printf("%c ", vertex[adj[i][j]]);
        printf("\n");
    }
}

/* BFS using adjacency matrix */
void bfsMatrix(int start) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int current, i;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS using Adjacency Matrix: ");

    while (front < rear) {
        current = queue[front++];
        printf("%c ", vertex[current]);

        for (i = 0; i < V; i++) {
            if (matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

/* BFS using adjacency list */
void bfsList(int start) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int current, j, n;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS using Adjacency List  : ");

    while (front < rear) {
        current = queue[front++];
        printf("%c ", vertex[current]);

        for (j = 0; j < V && adj[current][j] != -1; j++) {
            n = adj[current][j];
            if (!visited[n]) {
                visited[n] = 1;
                queue[rear++] = n;
            }
        }
    }
    printf("\n");
}

/* DFS using adjacency matrix */
void dfsMatrixUtil(int current, int visited[]) {
    int i;

    visited[current] = 1;
    printf("%c ", vertex[current]);

    for (i = 0; i < V; i++) {
        if (matrix[current][i] && !visited[i])
            dfsMatrixUtil(i, visited);
    }
}

void dfsMatrix(int start) {
    int visited[V] = {0};

    printf("DFS using Adjacency Matrix: ");
    dfsMatrixUtil(start, visited);
    printf("\n");
}

/* DFS using adjacency list */
void dfsListUtil(int current, int visited[]) {
    int j, n;

    visited[current] = 1;
    printf("%c ", vertex[current]);

    for (j = 0; j < V && adj[current][j] != -1; j++) {
        n = adj[current][j];
        if (!visited[n])
            dfsListUtil(n, visited);
    }
}

void dfsList(int start) {
    int visited[V] = {0};

    printf("DFS using Adjacency List  : ");
    dfsListUtil(start, visited);
    printf("\n");
}

/*
   Search for a specified vertex starting from A using BFS.
   We count:
   1. vertices examined (dequeued)
   2. neighbour/position checks performed by the representation.

   This makes the search comparison meaningful:
   - Matrix must inspect all V positions for every processed vertex.
   - List inspects only the stored neighbours.
*/
int searchMatrix(char target, int *vertexChecks, int *positionChecks) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int current, i;

    *vertexChecks = 0;
    *positionChecks = 0;

    visited[0] = 1;
    queue[rear++] = 0;

    while (front < rear) {
        current = queue[front++];
        (*vertexChecks)++;

        if (vertex[current] == target)
            return 1;

        for (i = 0; i < V; i++) {
            (*positionChecks)++;

            if (matrix[current][i] && !visited[i]) {
                if (vertex[i] == target)
                    return 1;

                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    return 0;
}

int searchList(char target, int *vertexChecks, int *neighbourChecks) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;
    int current, j, n;

    *vertexChecks = 0;
    *neighbourChecks = 0;

    visited[0] = 1;
    queue[rear++] = 0;

    while (front < rear) {
        current = queue[front++];
        (*vertexChecks)++;

        if (vertex[current] == target)
            return 1;

        for (j = 0; j < V && adj[current][j] != -1; j++) {
            (*neighbourChecks)++;
            n = adj[current][j];

            if (!visited[n]) {
                if (vertex[n] == target)
                    return 1;

                visited[n] = 1;
                queue[rear++] = n;
            }
        }
    }

    return 0;
}

/* Edge checking for E-F */
void checkEdgeEF(void) {
    int i;
    int listChecks = 0;

    printf("\nEDGE CHECK: E-F\n");

    /* Matrix: one direct access */
    printf("Matrix: matrix[E][F] = %d -> 1 direct lookup.\n",
           matrix[4][5]);

    /* List: scan E's neighbours until F is found */
    for (i = 0; i < V && adj[4][i] != -1; i++) {
        listChecks++;
        if (adj[4][i] == 5)
            break;
    }

    printf("List  : E's neighbours are B, F -> %d neighbour checks.\n",
           listChecks);
}

int main(void) {
    char target;
    int matrixVertexChecks, matrixPositionChecks;
    int listVertexChecks, listNeighbourChecks;

    printMatrix();
    printList();

    printf("\nTRAVERSALS STARTING FROM A\n");
    bfsMatrix(0);
    bfsList(0);
    dfsMatrix(0);
    dfsList(0);

    printf("\nEnter vertex to search from A (A-F): ");
    scanf(" %c", &target);

    if (searchMatrix(target, &matrixVertexChecks, &matrixPositionChecks)) {
        printf("\nSEARCH USING ADJACENCY MATRIX\n");
        printf("Vertex %c found.\n", target);
        printf("Vertices examined: %d\n", matrixVertexChecks);
        printf("Matrix position checks: %d\n", matrixPositionChecks);
    } else {
        printf("\nVertex %c not found using adjacency matrix.\n", target);
    }

    if (searchList(target, &listVertexChecks, &listNeighbourChecks)) {
        printf("\nSEARCH USING ADJACENCY LIST\n");
        printf("Vertex %c found.\n", target);
        printf("Vertices examined: %d\n", listVertexChecks);
        printf("Neighbour checks: %d\n", listNeighbourChecks);
    } else {
        printf("\nVertex %c not found using adjacency list.\n", target);
    }

    checkEdgeEF();

    return 0;
}
