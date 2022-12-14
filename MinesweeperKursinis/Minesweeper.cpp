#include <iostream>
#include "Minesweeper.h"

using namespace std;

void enterMove(int* r, int* c)
{
    cout << "Enter row and column:";
    cin >> *r >> *c;
    return;
}

void printTable(char visibleTable[][EDGE])
{
    cout << "X ";

    for (int i = 0; i < EDGE; i++)
    {
        if(i == EDGE - 1) cout << i << endl;
        else cout << i << " ";
    }


    for (int i = 0; i < EDGE; i++)
    {
        cout << i << " ";

        for (int j = 0; j < EDGE; j++)
            cout << visibleTable[i][j] << " ";
        cout << endl;
    }
    return;
}

bool isInside(int row, int column)
{

    return (row >= 0) && (row < EDGE) &&
        (column >= 0) && (column < EDGE);
}

bool isMine(int row, int column, char table[][EDGE])
{
    if (table[row][column] == 'X')
        return (true);
    else
        return (false);
}


int scanMinesAround(int row, int column, int mines[][2],
    char hiddenTable[][EDGE])
{
    int amount = 0;

    if (isInside(row - 1, column) == true)
    {
        if (isMine(row - 1, column, hiddenTable) == true)
            amount++;
    }

    if (isInside(row + 1, column + 1) == true)
    {
        if (isMine(row + 1, column + 1, hiddenTable) == true)
            amount++;
    }

    if (isInside(row, column + 1) == true)
    {
        if (isMine(row, column + 1, hiddenTable) == true)
            amount++;
    }

    if (isInside(row + 1, column) == true)
    {
        if (isMine(row + 1, column, hiddenTable) == true)
            amount++;
    }

    if (isInside(row, column - 1) == true)
    {
        if (isMine(row, column - 1, hiddenTable) == true)
            amount++;
    }

    if (isInside(row - 1, column + 1) == true)
    {
        if (isMine(row - 1, column + 1, hiddenTable) == true)
            amount++;
    }

    if (isInside(row + 1, column - 1) == true)
    {
        if (isMine(row + 1, column - 1, hiddenTable) == true)
            amount++;
    }

    if (isInside(row - 1, column - 1) == true)
    {
        if (isMine(row - 1, column - 1, hiddenTable) == true)
            amount++;
    }

    return (amount);
}

bool checkStep(char visibleTable[][EDGE], char hiddenTable[][EDGE], int* stepsLeft, int mines[][2], int row, int column)
{

    if (visibleTable[row][column] != '?')
        return (true);

    if (hiddenTable[row][column] == 'X')
    {
        for (int i = 0; i < MINES; i++)
        {
            visibleTable[mines[i][0]][mines[i][1]] = 'X';
        }

        printTable(visibleTable);
        cout << "\nBOOM! :(" << endl;
        return (false);
    }

    else
    {
        int amount = scanMinesAround(row, column, mines, hiddenTable);
        visibleTable[row][column] = amount + '0';
        (*stepsLeft)--;

        if (!amount)
        {

            if (isInside(row - 1, column) == true)
            {
                if (isMine(row - 1, column, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft,  mines, row - 1, column);
            }

            if (isInside(row - 1, column + 1) == true)
            {
                if (isMine(row - 1, column + 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row - 1, column + 1);
            }

            if (isInside(row, column + 1) == true)
            {
                if (isMine(row, column + 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row, column + 1);
            }

            if (isInside(row + 1, column + 1) == true)
            {
                if (isMine(row + 1, column + 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row + 1, column + 1);
            }

            if (isInside(row + 1, column) == true)
            {
                if (isMine(row + 1, column, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row + 1, column);
            }

            if (isInside(row, column - 1) == true)
            {
                if (isMine(row, column - 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row, column - 1);
            }

            if (isInside(row + 1, column - 1) == true)
            {
                if (isMine(row + 1, column - 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row + 1, column - 1);
            }

            if (isInside(row - 1, column - 1) == true)
            {
                if (isMine(row - 1, column - 1, hiddenTable) == false)
                    checkStep(visibleTable, hiddenTable, stepsLeft, mines, row - 1, column - 1);
            }
        }

        return (true);
    }
}

void placeMines(int mines[][2], char hiddenTable[][EDGE])
{
    bool marked[EDGE * EDGE];

    memset(marked, false, sizeof(marked));

    for (int i = 0; i < MINES;)
    {
        int randomNumber = rand() % (EDGE * EDGE);
        int x = randomNumber / EDGE;
        int y = randomNumber % EDGE;

        if (marked[randomNumber] == false)
        {
            mines[i][0] = x;
            mines[i][1] = y;

            hiddenTable[mines[i][0]][mines[i][1]] = 'X';
            marked[randomNumber] = true;
            i++;
        }
    }

    return;
}

void tableFilling(char hiddenTable[][EDGE], char visibleTable[][EDGE])
{
    srand(time(NULL));

    for (int i = 0; i < EDGE; i++)
    {
        for (int j = 0; j < EDGE; j++)
        {
            visibleTable[i][j] = hiddenTable[i][j] = '?';
        }
    }
    return;
}


void minesweeperEngine()
{
    char hiddenTable[EDGE][EDGE], visibleTable[EDGE][EDGE];

    int stepsLeft = EDGE * EDGE - MINES, r, c;
    int mines[MINES][2]; 

    tableFilling(hiddenTable, visibleTable);
    placeMines(mines, hiddenTable);

    bool gameInPlay = true;

    while (gameInPlay == true)
    {
        cout << " Minesweeper GAME" << endl;

        printTable(visibleTable);
        enterMove(&r, &c);

        gameInPlay = checkStep(visibleTable, hiddenTable, &stepsLeft, mines, r, c);

        if ((gameInPlay == true) && (stepsLeft == 0))
        {
            cout << "\nYou won !" << endl;
            gameInPlay = false;
        }
    }
    return;
}


int main()
{
    minesweeperEngine();
    return(0);
}