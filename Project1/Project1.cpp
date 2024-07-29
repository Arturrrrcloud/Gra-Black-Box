#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

struct Pole {
    char a[5];
    bool present;
    char type;
};

struct Atom {
    char a[5];
    bool present;
    char type;
};

struct Nearatom {
    char a[5];
    bool present;
    char type;
};

int playerRow = 0;
int playerCol = 1;
int row2 = 0;
int col2 = 0;
int row_begin;
int col_begin;
int row2_begin;
int col2_begin;
char save[5];
bool save1;
int temp = 0;
int j = 1;
int result;

void creatingBoard(Pole** pole, int size) {
    system("cls");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == 0 && j == 0) || (i == (size - 1) && j == (size - 1)) || (i == (size - 1) && j == 0) || (i == 0 && j == (size - 1))) {
                pole[i][j].a[0] = ' ';
                pole[i][j].a[1] = '_';
                pole[i][j].a[2] = ' ';
                pole[i][j].a[3] = ' ';
                pole[i][j].a[4] = '\0';
            }
            if (i == playerRow && j == playerCol && pole[i][j].a[1] == ' ') {
                pole[i][j].a[1] = 'P';
                row2 = i;
                col2 = j;
            }
            cout << pole[i][j].a;
        }
        cout << endl;
    }
}

void movePlayer(Pole** pole, char direction, int size) {
    int targetRow = playerRow;
    int targetCol = playerCol;

    if (direction == 'w') {
        targetRow = playerRow - 1;
    }
    else if (direction == 's') {
        targetRow = playerRow + 1;
    }
    else if (direction == 'a') {
        targetCol = playerCol - 1;
    }
    else if (direction == 'd') {
        targetCol = playerCol + 1;
    }

    if (targetRow >= 0 && targetRow < size && targetCol >= 0 && targetCol < size && pole[targetRow][targetCol].a[1] != '_' &&
        pole[targetRow][targetCol].a[1] != '2' && pole[targetRow][targetCol].a[1] != '3' && pole[targetRow][targetCol].a[1] != '4' &&
        pole[targetRow][targetCol].a[1] != '5' && pole[targetRow][targetCol].a[1] != '6' && pole[targetRow][targetCol].a[1] != '7' &&
        pole[targetRow][targetCol].a[1] != 'o' && pole[targetRow][targetCol].a[1] != 'A' && pole[targetRow][targetCol].a[1] != 'N' &&
        pole[targetRow][targetCol].a[1] != 'H' && pole[targetRow][targetCol].a[1] != 'R' && pole[targetRow][targetCol].a[1] != '1') {
        pole[playerRow][playerCol].a[1] = ' ';
        playerRow = targetRow;
        playerCol = targetCol;
        pole[playerRow][playerCol].a[1] = 'P';
        row2 = playerRow;
        col2 = playerCol;
    }
    row2 = targetRow;
    col2 = targetCol;
}



void creatingAtom(Atom** atom, Nearatom** nearatom, Pole** pole, int size) {
    int atomsToPlace = size - 4;
    while (atomsToPlace > 0) {
        int r = rand() % (size - 2) + 1;
        int c = rand() % (size - 2) + 1;
        if (pole[r][c].a[1] == ' ' && pole[r][c].type != 'A') {
            atom[r][c].type = 'A';
            pole[r][c].type = atom[r][c].type = 'A';
            for (int row1 = r - 1; row1 <= r + 1; row1 += 2) {
                for (int col1 = c - 1; col1 <= c + 1; col1 += 2) {
                    if (row1 >= 1 && row1 < (size - 1) && col1 >= 1 && col1 < (size - 1) && pole[row1][col1].type != 'A') {
                        nearatom[row1][col1].type = 'N';
                        pole[row1][col1].type = nearatom[row1][col1].type = 'N';
                    }
                }
            }
            atomsToPlace--;
        }
        if (atom[r][c].type == 'A' && atom[r - 1][c].type == 'A') {
            pole[r][c + 1].type = ' ';
            pole[r][c - 1].type = ' ';
            pole[r - 1][c + 1].type = ' ';
            pole[r - 1][c - 1].type = ' ';
        }
        else if (atom[r][c].type == 'A' && atom[r + 1][c].type == 'A') {
            pole[r][c + 1].type = ' ';
            pole[r][c - 1].type = ' ';
            pole[r + 1][c + 1].type = ' ';
            pole[r + 1][c - 1].type = ' ';
        }
        else if (atom[r][c].type == 'A' && atom[r][c - 1].type == 'A') {
            pole[r - 1][c].type = ' ';
            pole[r + 1][c].type = ' ';
            pole[r - 1][c - 1].type = ' ';
            pole[r + 1][c - 1].type = ' ';
        }
        else if (atom[r][c].type == 'A' && atom[r][c + 1].type == 'A') {
            pole[r - 1][c].type = ' ';
            pole[r + 1][c].type = ' ';
            pole[r - 1][c + 1].type = ' ';
            pole[r + 1][c + 1].type = ' ';
        }
    }
}

bool CreatingR(Pole** pole, int size) {
    if (row2 == 0 && col2 >= 2 && col2 <= (size - 3) && (pole[row2 + 1][col2 - 1].type == 'A' || pole[row2 + 1][col2 + 1].type == 'A')) {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 + 1][col2].a[1] == ' ') {
            playerRow++;
        }
        else if (pole[row2 + 1][col2].a[1] == '0') {
            playerRow++;
        }
        return true;
    }
    else if (row2 == 0 && col2 == 1 && pole[row2 + 1][col2 + 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 + 1][col2].a[1] == ' ') {
            playerRow++;
        }
        else if (pole[row2 + 1][col2].a[1] == '0') {
            playerRow++;
        }
        return true;
    }
    else if (row2 == 0 && col2 == (size - 2) && pole[row2 + 1][col2 - 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 + 1][col2].a[1] == ' ') {
            playerRow++;
        }
        else if (pole[row2 + 1][col2].a[1] == '0') {
            playerRow++;
        }
        return true;
    }
    if (row2 == (size - 1) && col2 >= 2 && col2 <= (size - 3) && (pole[row2 - 1][col2 - 1].type == 'A' || pole[row2 - 1][col2 + 1].type == 'A')) {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 - 1][col2].a[1] == ' ') {
            playerRow--;
        }
        else if (pole[row2 - 1][col2].a[1] == '0') {
            playerRow--;
        }
        return true;
    }
    else if (row2 == (size - 1) && col2 == 1 && pole[row2 - 1][col2 + 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 - 1][col2].a[1] == ' ') {
            playerRow--;
        }
        else if (pole[row2 - 1][col2].a[1] == '0') {
            playerRow--;
        }
        return true;
    }
    else if (row2 == (size - 1) && col2 == (size - 2) && pole[row2 - 1][col2 - 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2 - 1][col2].a[1] == ' ') {
            playerRow--;
        }
        else if (pole[row2 - 1][col2].a[1] == '0') {
            playerRow--;
        }
        return true;
    }
    if (col2 == 0 && row2 >= 2 && row2 <= (size - 3) && (pole[row2 - 1][col2 + 1].type == 'A' || pole[row2 + 1][col2 + 1].type == 'A')) {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 + 1].a[1] == ' ') {
            playerCol++;
        }
        else if (pole[row2][col2 + 1].a[1] == '0') {
            playerCol++;
        }
        return true;
    }
    else if (col2 == 0 && row2 == 1 && pole[row2 + 1][col2 + 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 + 1].a[1] == ' ') {
            playerCol++;
        }
        else if (pole[row2][col2 + 1].a[1] == '0') {
            playerCol++;
        }
        return true;
    }
    else if (col2 == 0 && row2 == (size - 2) && pole[row2 - 1][col2 + 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 + 1].a[1] == ' ') {
            playerCol++;
        }
        else if (pole[row2][col2 + 1].a[1] == '0') {
            playerCol++;
        }
        return true;
    }
    if (col2 == (size - 1) && row2 >= 2 && row2 <= (size - 3) && (pole[row2 + 1][col2 - 1].type == 'A' || pole[row2 - 1][col2 - 1].type == 'A')) {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 - 1].a[1] == ' ') {
            playerCol--;
        }
        else if (pole[row2][col2 - 1].a[1] == '0') {
            playerCol--;
        }
        return true;
    }
    else if (col2 == (size - 1) && row2 == 1 && pole[row2 + 1][col2 - 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 - 1].a[1] == ' ') {
            playerCol--;
        }
        else if (pole[row2][col2 - 1].a[1] == '0') {
            playerCol--;
        }
        return true;
    }
    else if (col2 == (size - 1) && row2 == (size - 2) && pole[row2 - 1][col2 - 1].type == 'A') {
        pole[row2][col2].a[1] = 'R';
        if (pole[row2][col2 - 1].a[1] == ' ') {
            playerCol--;
        }
        else if (pole[row2][col2 - 1].a[1] == '0') {
            playerCol--;
        }
        return true;
    }
    return false;
}

void ChangeDirection(Pole** pole, int size) {
    int i;
    char d;
    i = 1;
    row2_begin = row_begin;
    col2_begin = col_begin;
    if (row2_begin == 0) {
        d = 'w';
    }
    else if (row2_begin == (size - 1)) {
        d = 's';
    }
    else if (col2_begin == 0) {
        d = 'a';
    }
    else if (col2_begin == (size - 1)) {
        d = 'd';
    }
    while ((row2 > 0 && row2 < (size - 1)) && (col2 > 0 && col2 < (size - 1))) {
        if (d == 'w') {
            if (pole[row2 + 1][col2 + 1].type == 'A' && pole[row2 + 1][col2 - 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2--;
                    if (row2 == 0) {
                        pole[row2_begin][col2_begin].a[1] = 'R';
                        row2 = (size - 1);
                        if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                            playerRow++;
                        }
                        else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                            playerRow++;
                        }
                        d = 'E';
                        break;
                    }
                }
            }
            else if (pole[row2 + 1][col2 + 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2--;
                    if (col2 == 0) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                                playerRow++;
                            }
                            else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                                playerRow++;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                            playerRow++;
                        }
                        else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                            playerRow++;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                                playerRow++;
                            }
                            else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                                playerRow++;
                            }
                        }
                        d = 'd';
                        i++;
                        break;
                    }
                }
            }
            else if (pole[row2 + 1][col2 - 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2++;
                    if (col2 == (size - 1)) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                                playerRow++;
                            }
                            else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                                playerRow++;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                            playerRow++;
                        }
                        else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                            playerRow++;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin + 1][col2_begin].a[1] == ' ') {
                                playerRow++;
                            }
                            else if (pole[row2_begin + 1][col2_begin].a[1] == '0') {
                                playerRow++;
                            }
                        }
                        d = 'a';
                        i++;
                        break;
                    }
                }
            }
        }
        if (d == 's') {
            if (pole[row2 - 1][col2 + 1].type == 'A' && pole[row2 - 1][col2 - 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2++;
                    if (row2 == (size - 1)) {
                        pole[row2_begin][col2_begin].a[1] = 'R';
                        row2 = (size - 1);
                        if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                            playerRow--;
                        }
                        else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                            playerRow--;
                        }
                        d = 'E';
                        break;
                    }
                }
            }
            else if (pole[row2 - 1][col2 + 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2--;
                    if (col2 == 0) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                                playerRow--;
                            }
                            else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                                playerRow--;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                            playerRow--;
                        }
                        else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                            playerRow--;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                                playerRow--;
                            }
                            else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                                playerRow--;
                            }
                        }
                        d = 'd';
                        i++;
                        break;
                    }
                }
            }
            else if (pole[row2 - 1][col2 - 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2++;
                    if (col2 == (size - 1)) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                                playerRow--;
                            }
                            else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                                playerRow--;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                            playerRow--;
                        }
                        else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                            playerRow--;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin - 1][col2_begin].a[1] == ' ') {
                                playerRow--;
                            }
                            else if (pole[row2_begin - 1][col2_begin].a[1] == '0') {
                                playerRow--;
                            }
                        }
                        d = 'a';
                        i++;
                        break;
                    }
                }
            }
        }
        if (d == 'a') {
            if (pole[row2 - 1][col2 + 1].type == 'A' && pole[row2 + 1][col2 + 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2--;
                    if (col2 == 0) {
                        pole[row2_begin][col2_begin].a[1] = 'R';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                            playerCol++;
                        }
                        else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                            playerCol++;
                        }
                        d = 'E';
                        break;
                    }
                }
            }
            else if (pole[row2 - 1][col2 + 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2++;
                    if (row2 == (size - 1)) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                                playerCol++;
                            }
                            else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                                playerCol++;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                            playerCol++;
                        }
                        else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                            playerCol++;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                                playerCol++;
                            }
                            else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                                playerCol++;
                            }
                        }
                        d = 'w';
                        i++;
                        break;
                    }
                }
            }
            else if (pole[row2 + 1][col2 + 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2--;
                    if (row2 == 0) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                                playerCol++;
                            }
                            else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                                playerCol++;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                            playerCol++;
                        }
                        else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                            playerCol++;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i++) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                                playerCol++;
                            }
                            else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                                playerCol++;
                            }
                        }
                        d = 's';
                        i++;
                        break;
                    }
                }
            }
        }
        if (d == 'd') {
            if (pole[row2 - 1][col2 - 1].type == 'A' && pole[row2 + 1][col2 - 1].type == 'A') {
                while (col2 > 0 && col2 < (size - 1)) {
                    col2++;
                    if (col2 == (size - 1)) {
                        pole[row2_begin][col2_begin].a[1] = 'R';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin + 1].a[1] == ' ') {
                            playerCol++;
                        }
                        else if (pole[row2_begin][col2_begin + 1].a[1] == '0') {
                            playerCol++;
                        }
                        d = 'E';
                        break;
                    }
                }
            }
            else if (pole[row2 - 1][col2 - 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2++;
                    if (row2 == (size - 1)) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                                playerCol--;
                            }
                            else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                                playerCol--;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        }
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                            playerCol--;
                        }
                        else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                            playerCol--;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                                playerCol--;
                            }
                            else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                                playerCol--;
                            }
                        }
                        d = 'w';
                        i++;
                        break;
                    }
                }
            }
            else if (pole[row2 + 1][col2 - 1].type == 'A') {
                while (row2 > 0 && row2 < (size - 1)) {
                    row2--;
                    if (row2 == 0) {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            pole[row2][col2].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                                playerCol--;
                            }
                            else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                                playerCol--;
                            }
                            j++;
                            d = 'E';
                            break;
                        }
                        else {
                            pole[row2][col2].a[1] = '0' + j;
                            j++;
                            d = 'E';
                            break;
                        };
                    }
                    else if (pole[row2][col2].type == 'A') {
                        pole[row2_begin][col2_begin].a[1] = 'H';
                        row2 = (size - 1);
                        if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                            playerCol--;
                        }
                        else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                            playerCol--;
                        }
                        d = 'E';
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        if (i == 1) {
                            pole[row2_begin][col2_begin].a[1] = '0' + j;
                            if (pole[row2_begin][col2_begin - 1].a[1] == ' ') {
                                playerCol--;
                            }
                            else if (pole[row2_begin][col2_begin - 1].a[1] == '0') {
                                playerCol--;
                            }
                        }
                        d = 's';
                        i++;
                        break;
                    }
                }
            }
        }
    }
}

void Lazer(Pole** pole, int size) {
    int i;
    i = 1;
    row_begin = row2;
    col_begin = col2;
    while ((col2 >= 0 && col2 < size) && (row2 >= 0 && row2 < size)) {
        if (CreatingR(pole, size) && i == 1) {
            break;
        }
        else if (pole[row2][col2].a[1] == 'P' && row2 == 0) {
            row2++;
            while (row2 >= 0 && row2 < size) {
                if (pole[row2][col2].type == 'A') {
                    pole[row2 - i][col2].a[1] = 'H';
                    if (pole[row2 - i + 1][col2].a[1] == ' ') {
                        playerRow++;
                    }
                    else if (pole[row2 - i + 1][col2].a[1] == 'o') {
                        playerRow++;
                    }
                    break;
                }
                else if (pole[row2][col2].type == 'N') {
                    ChangeDirection(pole, size);
                    i++;
                    break;
                }
                else if (pole[row2][col2].type != 'A' && pole[row2][col2].type != 'N') {
                    row2++;
                    if (row2 == (size - 1)) {
                        pole[row2][col2].a[1] = '0' + j;
                        pole[row2 - (size - 1)][col2].a[1] = '0' + j;
                        if (pole[row2 - i + 1][col2].a[1] == ' ') {
                            playerRow++;
                        }
                        else if (pole[row2 - i + 1][col2].a[1] == 'o') {
                            playerRow++;
                        }
                        j++;
                        break;
                    }
                    i++;
                }
            }
        }
        else if (pole[row2][col2].a[1] == 'P' && row2 == (size - 1)) {
            row2--;
            while (row2 >= 0 && row2 < size) {
                \
                    if (pole[row2][col2].type == 'A') {
                        pole[row2 + i][col2].a[1] = 'H';
                        if (pole[row2 + i - 1][col2].a[1] == ' ') {
                            playerRow--;
                        }
                        else if (pole[row2 + i - 1][col2].a[1] == 'o') {
                            playerRow--;
                        }
                        break;
                    }
                    else if (pole[row2][col2].type == 'N') {
                        ChangeDirection(pole, size);
                        i++;
                        break;
                    }
                    else if (pole[row2][col2].type != 'A' && pole[row2][col2].type != 'N') {
                        row2--;
                        if (row2 == 0) {
                            pole[row2][col2].a[1] = '0' + j;
                            pole[row2 + (size - 1)][col2].a[1] = '0' + j;
                            if (pole[row2 + i - 1][col2].a[1] == ' ') {
                                playerRow--;
                            }
                            else if (pole[row2 + i - 1][col2].a[1] == 'o') {
                                playerRow--;
                            }
                            j++;
                            break;
                        }
                        i++;
                    }
            }
        }
        else if (pole[row2][col2].a[1] == 'P' && col2 == 0) {
            col2++;
            while (col2 >= 0 && col2 < size) {
                if (pole[row2][col2].type == 'A') {
                    pole[row2][col2 - i].a[1] = 'H';
                    if (pole[row2][col2 - i + 1].a[1] == ' ') {
                        playerCol++;
                    }
                    else if (pole[row2][col2 - i + 1].a[1] == 'o') {
                        playerCol++;
                    }
                    break;
                }
                else if (pole[row2][col2].type == 'N') {
                    ChangeDirection(pole, size);
                    i++;
                    break;
                }
                else if (pole[row2][col2].type != 'A' && pole[row2][col2].type != 'N') {
                    col2++;
                    if (col2 == (size - 1)) {
                        pole[row2][col2].a[1] = '0' + j;
                        pole[row2][col2 - (size - 1)].a[1] = '0' + j;
                        if (pole[row2][col2 - i + 1].a[1] == ' ') {
                            playerCol++;
                        }
                        else if (pole[row2][col2 - i + 1].a[1] == 'o') {
                            playerCol++;
                        }
                        j++;
                        break;
                    }
                    i++;
                }
            }
        }
        else if (pole[row2][col2].a[1] == 'P' && col2 == (size - 1)) {
            col2--;
            while (col2 >= 0 && col2 < size) {
                if (pole[row2][col2].type == 'A') {
                    pole[row2][col2 + i].a[1] = 'H';
                    if (pole[row2][col2 + i - 1].a[1] == ' ') {
                        playerCol--;
                    }
                    else if (pole[row2][col2 + i - 1].a[1] == 'o') {
                        playerCol--;
                    }
                    break;
                }
                else if (pole[row2][col2].type == 'N') {
                    ChangeDirection(pole, size);
                    i++;
                    break;
                }
                else if (pole[row2][col2].type != 'A' && pole[row2][col2].type != 'N') {
                    col2--;
                    if (col2 == 0) {
                        pole[row2][col2].a[1] = '0' + j;
                        pole[row2][col2 + (size - 1)].a[1] = '0' + j;
                        if (pole[row2][col2 + i - 1].a[1] == ' ') {
                            playerCol--;
                        }
                        else if (pole[row2][col2 + i - 1].a[1] == 'o') {
                            playerCol--;
                        }
                        j++;
                        break;
                    }
                    i++;
                }
            }
        }
        else if (pole[row2][col2].a[1] != 'P') {
            break;
        }
    }
    creatingBoard(pole, size);
}

void CreatingO(Pole** pole, int size) {
    if (pole[row2][col2].a[1] != '0' && temp < (size - 4)) {
        pole[row2][col2].a[1] = 'o';
        if (pole[row2][col2 + 1].a[1] == ' ') {
            playerCol++;
        }
        else if (pole[row2][col2 - 1].a[1] == ' ') {
            playerCol--;
        }
        else if (pole[row2 + 1][col2].a[1] == ' ') {
            playerRow++;
        }
        else if (pole[row2 - 1][col2].a[1] == ' ') {
            playerRow--;
        }
        temp++;
    }
    creatingBoard(pole, size);
}

void End(Pole** pole, int size) {
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            if (temp == (size - 4)) {
                if (pole[z][x].type == 'A' && pole[z][x].a[1] == 'o') {
                    pole[z][x].a[1] = 'O';
                    result++;
                }
                else if (pole[z][x].type != 'A' && pole[z][x].a[1] == 'o') {
                    pole[z][x].a[1] = 'X';
                }
            }

        }
    }
    creatingBoard(pole, size);
    cout << "Score:" << result << endl;
}

void TrueRe(Pole** pole, int size) {
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            if (pole[z][x].type == 'A') {
                pole[z][x].a[1] = 'O';
            }
        }
    }
    creatingBoard(pole, size);
}

void Help(Pole** pole, int size) {
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            if (pole[z][x].type == 'A') {
                pole[z][x].a[1] = 'O';
            }
        }
    }
    creatingBoard(pole, size);
}

void AfterHelp(Pole** pole, int size) {
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            if (pole[z][x].type == 'A' && pole[z][x].a[1] == 'o') {
                pole[z][x].a[1] = 'o';
            }
            else if (pole[z][x].type == 'A') {
                pole[z][x].a[1] = ' ';
            }
        }
    }
    creatingBoard(pole, size);
}

int main() {
    srand(time(NULL));
    int size;
    cout << "Gra Black Box, Nuso Artur, numer indeksu 201272" << endl;
    cout << "5x5(7)  8x8(10) 10x10(12)" << endl;
    cout << "Choose Difficulty: ";
    cin >> size;
    Pole** pole = new Pole * [size];
    for (int i = 0; i < size; i++) {
        pole[i] = new Pole[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pole[i][j].a[0] = '[';
            pole[i][j].a[1] = ' ';
            pole[i][j].a[2] = ']';
            pole[i][j].a[3] = ' ';
            pole[i][j].a[4] = '\0';
        }
    }
    Atom** atom = new Atom * [size];
    for (int i = 0; i < size; i++) {
        atom[i] = new Atom[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pole[i][j].a[0] = '[';
            pole[i][j].a[1] = ' ';
            pole[i][j].a[2] = ']';
            pole[i][j].a[3] = ' ';
            pole[i][j].a[4] = '\0';
        }
    }

    Nearatom** nearatom = new Nearatom * [size];
    for (int i = 0; i < size; i++) {
        nearatom[i] = new Nearatom[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pole[i][j].a[0] = '[';
            pole[i][j].a[1] = ' ';
            pole[i][j].a[2] = ']';
            pole[i][j].a[3] = ' ';
            pole[i][j].a[4] = '\0';
        }
    }
restart:
    creatingAtom(atom, nearatom, pole, size);
    creatingBoard(pole, size);
    cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
    char move;
    while (true) {
        cout << "Moving(w, s, a, d)" << "  " << "Shoot(b)" << "  " << "Atom na planszy(o)" << endl;
        cout << "Move: ";
        cin >> move;
        if (move == 'o') {
            if ((row2 >= 1 && row2 <= (size - 2)) && (col2 >= 1 && col2 <= (size - 2))) {
                CreatingO(pole, size);
                cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
            }
        }
        else if (move == 'b') {
            movePlayer(pole, move, size);
            Lazer(pole, size);
            cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
        }
        else if (move == 'k') {
            End(pole, size);
            cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
            break;
        }
        else if (move == 'p') {
            TrueRe(pole, size);
            cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
            break;
        }
        else if (move == 'h') {
            Help(pole, size);
            Sleep(1000);
            AfterHelp(pole, size);
            cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
        }
        else if (move == 'q') {
            cout << "Exit(l)" << endl;
            cout << "New game(n)" << endl;
            cin >> move;
            if (move == 'l') {
                break;
            }
            if (move == 'n') {
                for (int z = 0; z < size; z++) {
                    for (int x = 0; x < size; x++) {
                        if ((z == 0 && x == 0) || (z == (size - 1) && x == (size - 1)) || (z == (size - 1) && x == 0) || (z == 0 && x == (size - 1))) {
                            pole[z][x].a[0] = ' ';
                            pole[z][x].a[1] = '_';
                            pole[z][x].a[2] = ' ';
                            pole[z][x].a[3] = ' ';
                            pole[z][x].a[4] = '\0';
                        }
                        else {
                            pole[z][x].a[1] = ' ';
                            pole[z][x].type = ' ';
                        }
                    }
                }
                goto restart;
                break;
            }
        }
        else {
            movePlayer(pole, move, size);
            creatingBoard(pole, size);
            cout << "Menu(q)" << "  " << "Verify(k)" << "  " << "Help(h)" << "  " << "Solve Game(p)" << endl;
        }
    }
    for (int i = 0; i < size; i++) {
        delete[] pole[i];
        delete[] atom[i];
        delete[] nearatom[i];

    }
    delete[] atom;
    delete[] pole;
    delete[] nearatom;


    return 0;
}