#include <stdio.h>
#include <stdlib.h>


/*************************
 *  Function Prototypes  *
 *************************/
void clearBoard(char[3][3]);
void printBoard(char[3][3]);
void makeMark(char, char[3][3]);
int isMatching(char, char, char, char);
char checkForWinner(char, char[3][3]);
int playAgain();


/**************************
 *  Function definitions  *
 **************************/
void clearBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        };
    };
    return;
};

void printBoard(char board[3][3]) {
    // system("clear");
    printf("  | A | B | C |\n");
    printf("---------------\n");
    for (int i = 0; i < 3; i++) {
        printf("%d | %c | %c | %c |\n", i+1, board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf("---------------\n");
        };
    };
    return;
};

void makeMark(char player, char board[3][3]) {
    char col = '\0';
    int row = 0;

    while (col == '\0' || row == 0) {
        printf("Player %c, enter coords (1Q to quit): ", player);
        scanf(" %d%c", &row, &col);
        while ((getchar()) != '\n');  // clear the stdin buffer in case of invalid input.
        printf("%c\n", col);
        if (col == 'Q') {
            printf("Player %c quits.", player);
            exit(0);
        } else if (col < 'A' || col > 'C') {
            printf("invalid column!\n");
            col = '\0';
            continue;
        };
        if (row < 1 || row > 3) {
            printf("invalid row!\n");
            row = 0;
            continue;
        };
        if (board[row-1][col-'A'] != ' ') {
            printf("space unavailable!\n");
            col = '\0';
            row = 0;
            continue;
        } else {
            board[row-1][col-'A'] = player;
            break;
        };
    };
    return;
};

int isMatching(char a, char b, char c, char p) {
    return (a == p && b == p && c == p);
};

char checkForWinner(char player, char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (isMatching(board[i][0], board[i][1], board[i][2], player) ||
            isMatching(board[0][i], board[1][i], board[2][i], player)) {
            return player;
        };
    };
    if (isMatching(board[0][0], board[1][1], board[2][2], player) ||
        isMatching(board[2][0], board[1][1], board[0][2], player)) {
        return player; 
    };
    return ' ';
};

int playAgain() {
    char response;
    while (1) {
        printf("Play again? (y/n): ");
        while ((getchar()) != '\n');  // clear the stdin buffer in case of invalid input.
        scanf(" %c", &response);
        if (response == 'y' || response == 'Y') {
            return 1;
        } else if (response == 'n' || response == 'N') {
            return 0;
        };
    };
};


/**********
 *  Main  *
 **********/
int main() {

    int playGame = 1;
    char winner = ' ';
    char players[2] = { 'X', 'O' };
    char board[3][3] = {
        {'O', ' ', ' '},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
    };

    printf("Tic-Tac-Toe!!!!\n");
    while (playGame == 1) {
        clearBoard(board);
        while (winner == ' ') {
            for (int i = 0; i < sizeof(players); i++) {
                printBoard(board);
                makeMark(players[i], board);
                winner = checkForWinner(players[i], board);
                if (winner == players[i]) { break; };
            };
        };
        printf("Player %c wins!\n", winner);
        winner = ' ';
        playGame = playAgain();
    };
    return 0;
};
