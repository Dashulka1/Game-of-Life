#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GRID_SIZE 20 // Размер сетки
#define GENERATIONS 50 // Количество поколений

// Инициализация сетки
void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    int i, j;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

// Вывод сетки
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    int i, j;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            if(grid[i][j] == 0) {
                printf(".");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Проверка соседей клетки
int countNeighbors(int grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    int count = 0;
    int i, j;

    for(i = -1; i <= 1; i++) {
        for(j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            if(neighborX >= 0 && neighborX < GRID_SIZE && neighborY >= 0 && neighborY < GRID_SIZE) {
                count += grid[neighborX][neighborY];
            }
        }
    }

    return count;
}

// Обновление сетки
void updateGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    int newGrid[GRID_SIZE][GRID_SIZE];
    int i, j;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            int aliveNeighbors = countNeighbors(grid, i, j);
            
            if(grid[i][j] == 1) {
                if(aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = 0;
                } else {
                    newGrid[i][j] = 1;
                }
            } else {
                if(aliveNeighbors == 3) {
                    newGrid[i][j] = 1;
                } else {
                    newGrid[i][j] = 0;
                }
            }
        }
    }

    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE];

    // Инициализация случайного состояния сетки
    int i, j;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = rand() % 2;
        }
    }

    // Создание поколений
    for(i = 0; i < GENERATIONS; i++) {
        printGrid(grid);
        updateGrid(grid);
        usleep(500000); // Пауза в 0.5 секунды между поколениями
    }

    return 0;
}