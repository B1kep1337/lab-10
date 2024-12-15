#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

// Функция создания графа
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            G[i][j] = (rand() % 2) ? rand() % 10 : 0;// Генерация веса
            G[j][i] = (i == j) ? 0 : G[j][i];// Вес самопетли 0
        }
    }
    return G;
}

int** createGear(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[j][i];
        }
    }
    return G;
}

void more(int** G, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            G[j][i] = G[i][j];
        }
    }
}

void printG(int** G, int size) {
    printf("  ");
    for (int i = 0; i < size; ++i) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%2d ", (G[i][j] != INT_MAX) ? G[i][j] : -1);
        }
        printf("\n");
    }
    printf("\n");
}

void DiFS(int** G, int size, int* dist, int s) {
    queue <int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        s = q.front();
        q.pop();

        for (int i = 0; i < size; ++i) {
            if (G[s][i] && dist[i] > dist[s] + G[s][i]) {
                q.push(i);
                dist[i] = dist[s] + G[s][i];

            }
        }
    }
}

void createDist(int** G, int size, int** D) {
    int* dist = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) dist[j] = INT_MAX;
        DiFS(G, size, dist, i);
        for (int j = 0; j < size; ++j) D[i][j] = dist[j];
    }
}

void getEtc(int** D, int size, int* etc) {
    int max;
    for (int i = 0; i < size; ++i) {
        max = INT_MIN;
        for (int j = 0; j < size; ++j) {
            max = (D[i][j] > max && D[i][j] != INT_MAX) ? D[i][j] : max;
        }
        etc[i] = max;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    int n = 3;
    int weighted = 0, oriented = 0;
    int** G = NULL;
    srand(time(NULL));
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-n") == 0) {
                n = atoi(argv[i + 1]);
                ++i;
            }
            else if (strcmp(argv[i], "-w") == 0) weighted = 1;
            else if (strcmp(argv[i], "-o") == 0) oriented = 1;
        }
    }
    G = createG(n);
    if (!oriented) more(G, n);
    printG(G, n);

    int** D = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        D[i] = (int*)malloc(n * sizeof(int));
    }
    createDist(G, n, D);

    printf("Матрица расстояний:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%2d ", (D[i][j] != INT_MAX) ? D[i][j] : -1);
        }
        printf("\n");
    }

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        free(G[i]);
        free(D[i]);
    }
    free(G);
    free(D);

    return 0;
}