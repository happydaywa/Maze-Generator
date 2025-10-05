#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // for usleep

#define COLUMNS 25 // keep odd
#define ROWS 24    // keep odd

char Board[COLUMNS * ROWS];
int UnseenTiles = 0;

// Fill the board with walls '#' and cells '*' to be carved
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

// Draw the board in console
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
            Board[ny * COLUMNS + nx] = ' '; // carve cell

            Carve(nx, ny);
        }
    }
}



int main() {
    srand(time(NULL));

    FillBoard();
    Carve(1, 1);
    DrawBoard();

    return 0;
}