#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define BOARD_SIZE 3
#define NAME_LENGTH 30

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
} ttt;


void init_board(ttt *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = '-';
        }
    }
}

void display_board(ttt *game) {
    printf("\nCurrent Board:\n");
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", game->board[i][j]);
        }
        printf("\n");
    }
}

bool game_over(ttt *game) {
   
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i][0] != '-' && game->board[i][0] == game->board[i][1] && game->board[i][1] == game->board[i][2]) {
            return true;
        }
    }
   
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (game->board[0][j] != '-' && game->board[0][j] == game->board[1][j] && game->board[1][j] == game->board[2][j]) {
            return true;
        }
    }

    if (game->board[0][0] != '-' && game->board[0][0] == game->board[1][1] && game->board[1][1] == game->board[2][2]) {
        return true;
    }
    if (game->board[0][2] != '-' && game->board[0][2] == game->board[1][1] && game->board[1][1] == game->board[2][0]) {
        return true;
    }

    return false;
}

bool board_full(ttt *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}


void update_board(ttt *game, int row, int col, char player) {
    game->board[row][col] = player;
}

int main() {

    ttt game;
    init_board(&game);
    display_board(&game);
    printf("\n");

    char player_X_name[NAME_LENGTH];
    char player_O_name[NAME_LENGTH];

    printf("Enter name for Player X: ");
    fgets(player_X_name, NAME_LENGTH, stdin);
    printf("Enter name for Player O: ");
    fgets(player_O_name, NAME_LENGTH, stdin);
    player_X_name[strlen(player_X_name) - 1] = '\0';
    player_O_name[strlen(player_O_name) - 1] = '\0';

    while(1){
      
        char player = 'X'; 
        int row, col;
        bool game_ended = false;

        while (!game_ended) {
            printf("\n%s's turn. Enter row and column: ", ((player == 'X') ? player_X_name : player_O_name));
            scanf("%d %d", &row, &col);

            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || game.board[row][col] != '-') {
                printf("\nInvalid move. Try again.\n");
            }
            else {
                update_board(&game, row, col, player);
                display_board(&game);
                player = ((player == 'X') ? 'O' : 'X');
            }

            if (game_over(&game)) {
                printf("\n%s wins!\n", ((player == 'O') ? player_X_name : player_O_name));
                game_ended = true;
                init_board(&game);

            } else if (board_full(&game)) {
                printf("\nIt's a tie!\n");
                game_ended = true;
                init_board(&game);
            }
          }
        }

    return 0;
}

