// By: Eddy Zhang (GitHub: edzhangg)
#include <iostream>
#include <cstdlib>
using namespace std;

// constants
const int MAX_ROW_COL = 9;

// returns list of allowed numbers - void return type, but allowedNum is treated as pass by reference (array)
// allowedNum is an array that stores integers from 1-9
void allowed(int board[MAX_ROW_COL][MAX_ROW_COL], int col, int row, int allowedNum[MAX_ROW_COL])
{
    // iterating vertically from current unknown number
    for (int countCol = 0; countCol < MAX_ROW_COL; countCol++)
    {
        int index = (board[row][countCol]) - 1;
        // if a non-zero number is found, remove from allowedNum array
        if (board[row][countCol] > 0 && board[row][countCol] < 10)
        {
            int index = (board[row][countCol]) - 1;
            allowedNum[index] = 0;
        }
    }
    // iterating horizontally from current unknown number
    for (int countRow = 0; countRow < MAX_ROW_COL; countRow++)
    {
        if (board[countRow][col] > 0)
        {
            int index = (board[countRow][col]) - 1;
            allowedNum[index] = 0;
        }
    }
}

// check if there is the given value within the 3x3 "section" - true = value in square, false = not in square
bool inSquare(int board[MAX_ROW_COL][MAX_ROW_COL], int col, int row, int value)
{
    // result in integers 0-2 (int division), when multiplied by 3 will result in index to start checking from
    int groupRow = row / 3;
    int groupCol = col / 3;
    // iterating through square to check if value is already in square
    for (int countRow = (3 * groupRow); countRow < (3 * groupRow) + 3; countRow++)
    {
        for (int countCol = (3 * groupCol); countCol < (3 * groupCol) + 3; countCol++)
        {
            if (board[countRow][countCol] == value)
            {
                return true;
            }
        }
    }
    return false;
}

// check if board is solved
bool solved(int board[MAX_ROW_COL][MAX_ROW_COL])
{
    // iterating through the board to check for any 0
    for (int row = 0; row < MAX_ROW_COL; row++)
    {
        for (int col = 0; col < MAX_ROW_COL; col++)
        {
            if (board[row][col] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// prints the board out to the console
void printBoard(int board[MAX_ROW_COL][MAX_ROW_COL])
{
    for (int row = 0; row < MAX_ROW_COL; row++)
    {
        for (int col = 0; col < MAX_ROW_COL; col++)
        {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// main solving algorithm - uses recursion & backtracking (DFS)
// parameters: current state of board, col and row to check
void solveBoard(int board[MAX_ROW_COL][MAX_ROW_COL], int col, int row)
{
    bool finished = false;
    int nextRow = 0;
    int nextCol = 0;
    // if value is 0, check for possible solutions
    if (board[row][col] == 0)
    {
        // array of allowed numbers - updates in allowed function
        int allowedNum[MAX_ROW_COL] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        allowed(board, col, row, allowedNum);
        int index = 0;
        // puzzle not finished and possible solutions remain
        while ((!finished) && index < 9)
        {
            board[row][col] = 0;
            // if number in allowedIndex is non-zero AND it's not already in the "square", add to board
            if (allowedNum[index] > 0 && (!inSquare(board, col, row, allowedNum[index])))
            {
                nextRow = row;
                nextCol = col;
                board[row][col] = allowedNum[index];
                // calculate location of next element
                if (col == 8)
                {
                    nextRow = row + 1;
                    nextCol = 0;
                }
                else
                {
                    nextRow = row;
                    nextCol = col + 1;
                }
                // recursive call
                solveBoard(board, nextCol, nextRow);
            }
            index += 1;
            finished = solved(board);
            allowed(board, col, row, allowedNum);
        }
        // if no solution is found, reset value to 0
        if (!finished)
        {
            board[row][col] = 0;
        }
    }
    // non-zero - continue on to next element
    else
    {
        // calculate location of next element
        if (col == 8)
        {
            nextRow = row + 1;
            nextCol = 0;
        }
        else
        {
            nextRow = row;
            nextCol = col + 1;
        }
        solveBoard(board, nextCol, nextRow);
    }
}

int main()
{
    /*
    sudoku boards taken from https://sandiway.arizona.edu/sudoku/examples.html and https://sudoku.com
    test cases for the sudoku solver are listed below
    int board[MAX_ROW_COL][MAX_ROW_COL] = {{0, 0, 0, 2, 6, 0, 7, 0, 1},
                                           {6, 8, 0, 0, 7, 0, 0, 9, 0},
                                           {1, 9, 0, 0, 0, 4, 5, 0, 0},
                                           {8, 2, 0, 1, 0, 0, 0, 4, 0},
                                           {0, 0, 4, 6, 0, 2, 9, 0, 0},
                                           {0, 5, 0, 0, 0, 3, 0, 2, 8},
                                           {0, 0, 9, 3, 0, 0, 0, 7, 4},
                                           {0, 4, 0, 0, 5, 0, 0, 3, 6},
                                           {7, 0, 3, 0, 1, 8, 0, 0, 0}};
    int board[MAX_ROW_COL][MAX_ROW_COL] = {{1, 0, 0, 4, 8, 9, 0, 0, 6},
                                           {7, 3, 0, 0, 0, 0, 0, 4, 0},
                                           {0, 0, 0, 0, 0, 1, 2, 9, 5},
                                           {0, 0, 7, 1, 2, 0, 6, 0, 0},
                                           {5, 0, 0, 7, 0, 3, 0, 0, 8},
                                           {0, 0, 6, 0, 9, 5, 7, 0, 0},
                                           {9, 1, 4, 6, 0, 0, 0, 0, 0},
                                           {0, 2, 0, 0, 0, 0, 0, 3, 7},
                                           {8, 0, 0, 5, 1, 2, 0, 0, 4}};
    int board[MAX_ROW_COL][MAX_ROW_COL] = {{0, 7, 0, 5, 3, 0, 9, 0, 0},
                                           {3, 4, 0, 6, 0, 2, 8, 5, 1},
                                           {2, 0, 0, 0, 8, 0, 4, 7, 0},
                                           {0, 0, 0, 3, 9, 0, 5, 0, 0},
                                           {9, 1, 5, 7, 0, 0, 3, 0, 2},
                                           {6, 0, 0, 0, 0, 0, 0, 0, 7},
                                           {1, 0, 0, 9, 0, 7, 0, 8, 5},
                                           {5, 9, 0, 2, 1, 6, 0, 0, 0},
                                           {0, 6, 4, 0, 0, 0, 0, 0, 0}};
    int board[MAX_ROW_COL][MAX_ROW_COL] = {{0, 0, 6, 0, 0, 0, 0, 0, 0},
                                           {9, 2, 0, 0, 0, 3, 4, 0, 0},
                                           {0, 0, 0, 0, 8, 0, 0, 0, 1},
                                           {5, 6, 0, 0, 3, 0, 0, 8, 0},
                                           {0, 0, 7, 0, 0, 0, 5, 0, 0},
                                           {0, 0, 4, 0, 0, 6, 0, 0, 0},
                                           {7, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 9, 0, 0, 0, 4, 0},
                                           {3, 5, 0, 0, 0, 2, 9, 0, 0}};
    */
    int board[MAX_ROW_COL][MAX_ROW_COL] = {};
    cout << "Enter the sudoku board:" << endl;
    for (int enteredRows = 0; enteredRows < 9; enteredRows++)
    {
        for (int enteredCols = 0; enteredCols < 9; enteredCols++)
        {
            cin >> board[enteredRows][enteredCols];
        }
    }
    cout << "Sudoku Board: " << endl;
    printBoard(board);
    solveBoard(board, 0, 0);
    if (!solved(board))
    {
        cout << "No solution found." << endl;
    }
    else
    {
        cout << "Solution: " << endl;
        printBoard(board);
    }
}