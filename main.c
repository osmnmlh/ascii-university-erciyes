#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// Moves the console cursor to the specified x, y coordinate
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Uses the high-resolution Windows timer to create a custom sleep function in milliseconds
void sleep_ms(double milliseconds) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    do {
        QueryPerformanceCounter(&end);
    } while (((double)(end.QuadPart - start.QuadPart) / frequency.QuadPart) < (milliseconds / 1000.0));
}

// Stage1# Prints underscores (_) row by row and shows current cursor coordinates
void display_stage1() {
    system("cls");  
    int row, col;

    for (row = 0; row < 23; row++) {
        for (col = 0; col < 80; col++) {
            gotoxy(col, row);
            printf("_");

            gotoxy(0, 25);
            printf("Row: %2d,  Column: %d\n", row + 1, col + 1); 
            gotoxy(col , row);
            sleep_ms(0.995);
        }
    }
}

// Stage#2 Randomly fills a 23x80 grid with block characters
void display_stage2() {
    int row, col;
    int totalCells = 80 * 23;
    int remainingCells = totalCells;
    int grid[23][80] = {0};
        // generates mixed numbers
        srand(time(NULL));
        // the program continues as long as the remaining cell is greater than 0
    while (remainingCells > 0) {
        int randX = rand() % 80; //Selects a column between 0-79
        int randY = rand() % 23; //Selects a line between 0-22
        // this if checks whether the selected cell is filled or not, if it is filled it does not reduce the remaining cell
        if (grid[randY][randX] == 0) {
            grid[randY][randX] = 1;
            remainingCells--;

            gotoxy(randX, randY);
            printf("%c", 219);  // ASCII full block character

            sleep_ms(3);

            gotoxy(0, 25);
            printf("Row: %2d,  Column: %d\n", randY + 1, randX + 1);
            gotoxy(randX, randY);
        }
    }
}

// Stage3# Randomly renders the word "ERCIYES" using green asterisks on a black background
void display_stage3() {
    int totalCells = 5 * 41;
    int remainingCells = totalCells;
    int grid[5][41] = {0};

    char erciyes[5][41] = {
        "***** ****   ***   ***  *   * *****  ****",
        "*     *   * *   *   *    * *  *     *    ",
        "***   ****  *       *     *   ****   *** ",
        "*     * *   *   *   *     *   *         *",
        "***** *  **  ***   ***    *   ***** **** "
    };

    srand(time(NULL));

    while (remainingCells > 0) {
        int randX = rand() % 41;
        int randY = rand() % 5;

        if (grid[randY][randX] == 0) {
            grid[randY][randX] = 1;
            remainingCells--;

            gotoxy(19 + randX, 5 + randY); // starts printing from coordinate (19.5)
            gotoxy(0, 25);
            printf("Row: %2d,  Column: %d\n", randY + 6, randX + 20);
            gotoxy(19 + randX, 5 + randY);

            if (erciyes[randY][randX] == '*') {
                printf("\033[32m\033[40m*\033[0m"); // green * on black
            } else {
                printf("\033[1;30m\033[40m \033[0m"); // black background
            }

            sleep_ms(8);
        }
    }
}

// Stage4# Randomly renders the word "UNIVERSITESI" using green asterisks on black background
void display_stage4() {
    int totalCells = 5 * 70;
    int remainingCells = totalCells;
    int grid[5][70] = {0};

    char universitesi[5][70] = {
        "*   * *   *  ***  *   * ***** ****   ****  *** ***** *****  ****  *** ",
        "*   * **  *   *   *   * *     *   * *       *    *   *     *       *  ",
        "*   * * * *   *   *   * ***   ****   ***    *    *   ***    ***    *  ",
        "*   * *  **   *    * *  *     * *       *   *    *   *         *   *  ",
        " ***  *   *  ***    *   ***** *  ** ****   ***   *   ***** ****   *** "
    };

    srand(time(NULL));

    while (remainingCells > 0) {
        int randX = rand() % 70;
        int randY = rand() % 5;

        if (grid[randY][randX] == 0) {
            grid[randY][randX] = 1;
            remainingCells--;

            gotoxy(5 + randX, 12 + randY);
            gotoxy(0, 25);
            printf("Row: %2d, Column: %2d\n", randY + 13, randX + 6);
            gotoxy(5 + randX, 12 + randY);


            if (universitesi[randY][randX] == '*') {
                printf("\033[32m\033[40m*\033[0m");
            } else {
                printf("\033[1;30m\033[40m \033[0m");
            }

            sleep_ms(6);
        }
    }
}


int main() {
    display_stage1();
    gotoxy(0, 25);
    printf("                            "); // this space clears the area for what will be written when the counter is done
    gotoxy(0, 25);
    printf("Press a key!");
    getch();

    display_stage2();
    gotoxy(0, 25);
    printf("                            ");
    gotoxy(0, 25);
    printf("Press a key!");
    getch();

    display_stage3();
    display_stage4();
    gotoxy(0, 25);
    printf("Being a hero means fighting back even when it seems impossible!\n");
    printf("And sometimes heroes even achieve the impossible!\n\n");

    return 0;
}
