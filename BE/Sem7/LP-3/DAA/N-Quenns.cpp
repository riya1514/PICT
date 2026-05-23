/*
Assignment 4 (DAA)
Write a program to design n-Queens matrix having first Queen placed. Use backtracking to place
remaining Queens to generate the final n-queen
*/

#include <iostream>
#include <vector>
using namespace std;

int totalSolutions = 0;

//------------------------------------------------------------------------------
// Print a single board configuration
//------------------------------------------------------------------------------
void printBoard(vector<vector<char>> &board)
{
    for (auto &row : board)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//------------------------------------------------------------------------------
// Check if a queen can be safely placed at board[row][col]
//------------------------------------------------------------------------------
bool isSafe(vector<vector<char>> &board, int row, int col, int n)
{
    // Check column
    for (int i = 0; i < n; i++)
    {
        if (board[i][col] == 'Q' && i != row)
        {
            return false;
        }
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    // Check lower-left diagonal
    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    // Check lower-right diagonal
    for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// Backtracking function to solve N-Queens
//------------------------------------------------------------------------------
void solveNQueens(vector<vector<char>> &board, int row, int n, int fixedRow)
{
    if (row == n)
    {
        totalSolutions++;
        printBoard(board);
        return;
    }

    // Skip the row where the first queen is already placed
    if (row == fixedRow)
    {
        solveNQueens(board, row + 1, n, fixedRow);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col, n))
        {
            board[row][col] = 'Q';
            solveNQueens(board, row + 1, n, fixedRow);
            board[row][col] = '.'; // backtrack
        }
    }
}

int main()
{
    int n;
    cout << "\nEnter value of N for N-Queens: ";
    cin >> n;

    vector<vector<char>> board(n, vector<char>(n, '.'));

    int startRow, startCol;
    cout << "\nEnter starting Queen position (row and column, 0-indexed): ";
    cin >> startRow >> startCol;
    cout << endl;

    if (startRow < 0 || startRow >= n || startCol < 0 || startCol >= n)
    {
        cout << "Invalid position!" << endl;
        return 0;
    }

    board[startRow][startCol] = 'Q';

    cout << "Solving N-Queens: First Queen at (" << startRow << ", " << startCol << ")\n"
         << endl;

    solveNQueens(board, 0, n, startRow);

    if (totalSolutions == 0)
    {
        cout << "No Solution!" << endl;
    }

    return 0;
}
