#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

// Board cells: ' ' empty, 'X' player1, 'O' player2/AI
void init_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
}

void print_board(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; ++i) {
        printf(" ");
        for (int j = 0; j < SIZE; ++j) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) {
            printf(" ---+---+---\n");
        }
    }
    printf("\n");
}

int is_full(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// Check if someone wins: return 'X' or 'O' or ' ' if none
char check_winner(char board[SIZE][SIZE]) {
    // rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        } 
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    // diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    return ' ';
}

// Minimax for AI: returns score from perspective of maximizer ('O')
int minimax(char board[SIZE][SIZE], int depth, int isMax) {
    char winner = check_winner(board);
    if (winner == 'O') return 10 - depth;   // prefer faster wins
    if (winner == 'X') return depth - 10;   // prefer slower losses
    if (is_full(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (val > best) best = val;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimax(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (val < best) best = val;
                }
            }
        }
        return best;
    }
}

// AI move using minimax (perfect play). Chooses first best move.
void ai_move(char board[SIZE][SIZE]) {
    int bestVal = -1000;
    int bestMoveRow = -1, bestMoveCol = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMoveRow = i; bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    if (bestMoveRow != -1) {
        board[bestMoveRow][bestMoveCol] = 'O';
        printf("AI places O at %d %d\n", bestMoveRow + 1, bestMoveCol + 1);
    } else {
        // fallback: random
        int r, c;
        do { r = rand() % SIZE; c = rand() % SIZE; } while (board[r][c] != ' ');
        board[r][c] = 'O';
        printf("AI (random) places O at %d %d\n", r + 1, c + 1);
    }
}

// Human move: prompt for row,col (1..3)
void human_move(char board[SIZE][SIZE], char symbol) {
    int r, c;
    while (1) {
        printf("Player %c, enter row and column (1-%d 1-%d): ", symbol, SIZE, SIZE);
        if (scanf("%d %d", &r, &c) != 2) {
            while (getchar() != '\n'); // flush
            printf("Invalid input. Enter two numbers.\n");
            continue;
        }
        if (r < 1 || r > SIZE || c < 1 || c > SIZE) {
            printf("Out of range. Try again.\n");
            continue;
        }
        r--; c--;
        if (board[r][c] != ' ') {
            printf("Cell already occupied. Pick another.\n");
            continue;
        }
        board[r][c] = symbol;
        break;
    }
}

// Menu and game loop
void play_game(int vs_ai) {
    char board[SIZE][SIZE];
    int current_player = 1; // 1 -> X, 2 -> O
    int rounds = 0;
    int scoreX = 0, scoreO = 0, ties = 0;

    while (1) {
        init_board(board);
        rounds++;
        printf("\n=== Round %d ===\n", rounds);
        print_board(board);

        while (1) {
            if (current_player == 1) {
                human_move(board, 'X');
            } else {
                if (vs_ai) {
                    ai_move(board);
                } else {
                    human_move(board, 'O');
                }
            }

            print_board(board);
            char winner = check_winner(board);
            if (winner == 'X') {
                printf("Player X wins this round!\n");
                scoreX++;
                break;
            } else if (winner == 'O') {
                printf("Player O wins this round!\n");
                scoreO++;
                break;
            } else if (is_full(board)) {
                printf("This round is a tie.\n");
                ties++;
                break;
            }
            current_player = 3 - current_player; // toggle 1<->2
        }

        printf("Scoreboard: X=%d, O=%d, Ties=%d\n", scoreX, scoreO, ties);

        // Ask user for next action
        int choice = 0;
        while (1) {
            printf("\nOptions:\n");
            printf(" 1 - Play another round\n");
            printf(" 2 - Reset scores and play again\n");
            printf(" 3 - Exit to main menu\n");
            printf("Enter choice: ");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                printf("Invalid input.\n");
                continue;
            }
            if (choice < 1 || choice > 3) {
                printf("Invalid choice.\n");
                continue;
            }
            break;
        }

        if (choice == 1) {
            current_player = (rounds % 2) ? 2 : 1; // alternate who starts
            continue;
        } else if (choice == 2) {
            scoreX = scoreO = ties = 0;
            rounds = 0;
            current_player = 1;
            printf("Scores reset.\n");
            continue;
        } else {
            break;
        }
    }
}

// Small help/controls print
void print_help() {
    printf("\nTic-Tac-Toe Help:\n");
    printf("- Board coordinates are row and column numbers 1 through 3.\n");
    printf("- Player X always plays first by default.\n");
    printf("- In Human vs AI mode, AI plays O and uses perfect play.\n\n");
}

int main() {
    srand((unsigned int)time(NULL));
    int mode = 0;
    while (1) {
        printf("\n==== TIC-TAC-TOE ====\n");
        printf("Select mode:\n");
        printf(" 1 - Human vs Human\n");
        printf(" 2 - Human vs AI\n");
        printf(" 3 - Help\n");
        printf(" 4 - Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &mode) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        if (mode == 1) {
            play_game(0);
        } else if (mode == 2) {
            play_game(1);
        } else if (mode == 3) {
            print_help();
        } else if (mode == 4) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
