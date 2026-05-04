#include <iostream>

const int N = 8;

// Функция вывода доски на экран
void printBoard(const int board[N][N]) {
    std::cout << "\t";
    for (int i=0; i < N; ++i)
        std::cout << "  " << i << " ";
    std::cout << "\n";

    for (int i = 0; i < N; ++i) {
        std::cout << "\t";
        for (int j = 0; j < N; ++j)
            std::cout << "----";
        std::cout << "-\n";
        std::cout << "     " << i << "\t";

        for (int j = 0; j < N; ++j) {
            std::cout << "| ";
            if (board[i][j] == 1)
                std::cout << "Q ";
            else
                std::cout << "  ";
        }
        std::cout << "|\n";
    }
    std::cout << "\t";
    for (int j = 0; j < N; ++j)
        std::cout << "----";
    std::cout << "-\n\n\n";
}

// Проверка, можно ли поставить ферзя в клетку (col, row)
bool canPlaceQueen(const int board[N][N], int col, int row) {
    for (int r=0; r < row; ++r) {
        for (int c=0; c < N; ++c) {
            if (board[r][c] == 1) {
                if (col == c || row == r ||
                    col - row == c - r ||
                    (N - col) - row == (N - c) - r)
                    return false;
            }
        }
    }
    return true;
}

// Рекурсивный поиск всех решений; row – текущая строка, solutions – счётчик найденных решений
void solveNQueens(int board[N][N], int row, int& solutions) {
    for (int col=0; col < N; ++col) {
        if (canPlaceQueen(board, col, row)) {
            if (row == N - 1) {
                board[row][col] = 1;
                printBoard(board);
                board[row][col] = 0;
                ++solutions;
            } else {
                board[row][col] = 1;
                solveNQueens(board, row + 1, solutions);
                board[row][col] = 0;
            }
        }
    }
}

int main() {
    int board[N][N] = {};

    int totalSolutions = 0;
    solveNQueens(board, 0, totalSolutions);
    std::cout << "\tобщее количество досок: " << totalSolutions << "\n\n";

    return 0;
}
