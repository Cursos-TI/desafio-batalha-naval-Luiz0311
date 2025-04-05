#include <stdio.h>

#define SIZE      10
#define SHIP_SIZE 3

#define GREEN     "\x1B[32m"
#define NORMAL    "\x1B[0m"

void initialize_board(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) 
            board[i][j] = 0;
}

/*
dir: 1: horizontal | 2: vertical | 3: diagonal
*/
void isert_ship(int board[SIZE][SIZE], int x_cord, int y_cord, int dir)
{
    int board_number = 3;

    for (int i = 0; i < SHIP_SIZE; i++)
    {
        board[x_cord][y_cord] = board_number;

        switch (dir)
        {
            case 1:
            x_cord++; break;
            case 2:
            y_cord++; break;
            case 3:
            x_cord++; y_cord++; break;
        }
    }
}

int main(void)
{
    int board[SIZE][SIZE];
    initialize_board(board);
    isert_ship(board, 0, 0, 1);
    isert_ship(board, 6, 4, 2);
    isert_ship(board, 2, 7, 3);
    isert_ship(board, 5, 1, 3);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) 
        {
            int board_num = board[i][j];
            printf("%s%d ", (board_num != 0 ? GREEN : NORMAL), board_num);
        }
        printf("\n");
    }
    return 0;
}