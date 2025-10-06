#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COLUMNS 25
#define ROWS 24    

char Board[COLUMNS * ROWS];
int UnseenTiles = 0;


void FillBoard() {
    UnseenTiles = 0;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (x == 0 || y == 0 || x == COLUMNS - 1 || y == ROWS - 1) {
                Board[y*COLUMNS + x] = '#';
            } else if (x % 2 == 0 || y % 2 == 0) {
                Board[y*COLUMNS + x] = '#';
            } else {
                Board[y*COLUMNS + x] = '*';
                UnseenTiles++;
            }
        }
    }
}

void DrawBoard() {
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (i % COLUMNS == 0) putchar('\n');
        putchar(Board[i]);
    }
}

void Shuffle(int *array, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);

        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void Carve(int x, int y) {
    int Directions[4] = {0, 1, 2, 3};
    Shuffle(Directions, 4);

    for (int i = 0; i < 4; i++) {
        int nx = x, ny = y;
        
        switch (Directions[i]) {
            case 0: nx += 2; break;
            case 1: nx -= 2; break;
            case 2: ny += 2; break;
            case 3: ny -= 2; break;
        }
        if (nx > 0 && nx < COLUMNS && ny > 0 && ny < ROWS && Board[ny*COLUMNS + nx] == '*') { // If next cell valid
            Board[(y + ny)/2 * COLUMNS + (x + nx)/2] = ' ';
            Board[ny * COLUMNS + nx] = ' ';

            Carve(nx, ny);
        }
    }
}

int DFS(int x, int y, int endX, int endY) {
    if (x == endX && y == endY) return 1;
    int Directions[4] = {0, 1, 2, 3};



    for (int i = 0; i < 4; i++) {
        int nx = x, ny = y;

        switch (Directions[i]) {
            case 0: nx += 1; break;
            case 1: nx -= 1; break;
            case 2: ny += 1; break;
            case 3: ny -= 1; break;
        }
        if (Board[ny*COLUMNS + nx] == ' ') {
            Board[ny*COLUMNS + nx] = '*';
            DrawBoard();
            usleep(80000);

            if (DFS(nx, ny, endX, endY)) return 1;

            DrawBoard();
            usleep(80000);
            Board[ny*COLUMNS + nx] = ' ';
        }
    }
    return 0;
}



int main() {
    srand(time(NULL));

    FillBoard();
    Carve(1, 1);
    DrawBoard();
    DFS(0, 1, COLUMNS-2, ROWS-3);
    DrawBoard();

    return 0;
}