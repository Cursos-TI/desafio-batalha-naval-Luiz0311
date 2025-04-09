#include <stdio.h>

#define SIZE        10     // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE   3      // Tamanho padrão da nave

// Códigos ANSI para colorir a saída no terminal
#define GREEN       "\x1B[32m"
#define RED         "\x1B[31m"
#define NORMAL      "\x1B[0m"

// Tipo tabuleiro: matriz 10x10 de inteiros
typedef int Board[SIZE][SIZE];


// Inicializa todo o tabuleiro com zeros (sem navios ou marcadores).
void initialize_board(Board board) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
}

/*
Imprime o tabuleiro no terminal com cores:
- NORMAL (sem cor) para células vazias (0)
- VERDE para navios (3)
- VERMELHO para marcadores de área/ataque (5)
*/
void print_board(Board board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char *color;
            switch (board[i][j]) {
                case 3: color = GREEN; break;
                case 5: color = RED; break;
                default: color = NORMAL; break;
            }
            printf("%s%d ", color, board[i][j]);
        }
        printf("\n");
    }
}

/*
Insere uma nave no tabuleiro a partir de uma coordenada inicial (x, y)
em uma direção:
- dir = 1: horizontal (move x)
- dir = 2: vertical (move y)
- dir = 3: diagonal (move x e y)
*/
void insert_ship(Board board, int x, int y, int dir) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
            board[x][y] = 3;

        switch (dir) {
            case 1: x++; break;             // Horizontal
            case 2: y++; break;             // Vertical
            case 3: x++; y++; break;        // Diagonal
        }
    }
}

/*
Insere um "cone" de ataque com base em (x, y).
Formato:
      x
    x x x
  x x x x x
O ponto central é (x, y) e o cone se expande para baixo.
*/
void insert_cone(Board board, int x, int y) {
    // Coordenadas relativas ao ponto central
    int dx[] = {-1,  0, 0, 0, 1, 1, 1, 1, 1};
    int dy[] = { 0, -1, 0, 1,-2,-1, 0, 1, 2};

    for (int i = 0; i < 9; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
            board[nx][ny] = 5;
    }
}

/*
Insere uma cruz centrada em (x, y).
Formato:
    x
  x x x
    x
*/
void insert_cross(Board board, int x, int y) {
    int dx[] = {-1,  0, 0, 0, 1};
    int dy[] = { 0, -2, -1, 0, 0};

    for (int i = 0; i < 5; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
            board[nx][ny] = 5;
    }

    // Completa os dois lados direitos da cruz
    if (x >= 0 && x < SIZE) {
        for (int j = 1; j <= 2; j++) {
            if (y + j < SIZE)
                board[x][y + j] = 5;
        }
    }

    // Parte inferior da cruz
    if (x + 1 < SIZE)
        board[x + 1][y] = 5;
}

/*
Insere um padrão octaédrico centrado em (x, y).
Formato:
    x
  x x x
    x
*/
void insert_octahedron(Board board, int x, int y) {
    int dx[] = {-1,  0, 0, 0, 1};
    int dy[] = { 0, -1, 0, 1, 0};

    for (int i = 0; i < 5; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
            board[nx][ny] = 5;
    }
}

/*
Função principal: inicializa o tabuleiro, insere naves e padrões,
e imprime o resultado.
*/
int main(void) {
    Board board;
    initialize_board(board);

    // Inserção de naves em diferentes direções
    insert_ship(board, 0, 0, 1); // horizontal
    insert_ship(board, 6, 4, 2); // vertical
    insert_ship(board, 2, 7, 3); // diagonal
    insert_ship(board, 5, 1, 3); // diagonal

    // Inserção de padrões de ataque
    insert_cone(board, 1, 3);
    insert_cross(board, 5, 5);
    insert_octahedron(board, 8, 2);

    // Impressão final do tabuleiro
    print_board(board);
    return 0;
}
