#include <stdio.h>

#define SIZE 10
#define SHIP_SIZE 3

void initialize_board(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) 
            board[i][j] = 0;
}

void isert_ship(int board[SIZE][SIZE], int x_cord, int y_cord, int is_vert)
{
    for (int i = 0; i < SHIP_SIZE; i++)
    {
        board[x_cord][y_cord] = 1;
        if (is_vert)
        {
            x_cord++;
            continue;
        }
        y_cord++;
    }
}

int main(void)
{
    int board[SIZE][SIZE];
    initialize_board(board);
    isert_ship(board, 0, 0, 0);
    isert_ship(board, 6, 4, 1);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) printf("%d ",board[i][j]);
        printf("\n");
    }
    return 0;
}