#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "vector.h"
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

void greetings();
void readTheGrid(Grid<char>& cells);
void checkAliveNeighbours(Grid<char>& cells, int& alive, int r, int j);
bool isCellAlive(Grid<char>& cells,int r, int c);
void checkUpper(Grid<char>& cells,int& alive,int r, int c);
void checkDown(Grid<char>& cells,int& alive,int r, int c);
void checkLeft(Grid<char>& cells,int& alive,int r, int c);
void checkRight(Grid<char>& cells,int& alive,int r, int c);
void checkUpperLeft(Grid<char>& cells,int& alive,int r, int c);
void checkUpperRight(Grid<char>& cells,int& alive,int r, int c);
void checkDownLeft(Grid<char>& cells,int& alive,int r, int c);
void checkDownRight(Grid<char>& cells,int& alive,int r, int c);
void generateNextGeneration(Grid<char>& cells, Grid<char> temp, Grid<int> alivecells, int& alive);
// Now what I want to do is create a temporary grid and store in it the original grid then compute the next generation
// on the copy and then reassign it to the original grid and then repeat

int main2134() {
    greetings();
    int alive;
    Grid<char> cells;
    Grid<char> temp;
    Grid<int> aliveCells;
    readTheGrid(cells);
    temp.resize(cells.numRows(),cells.numCols());
    aliveCells.resize(cells.numRows(),cells.numCols());
    string prompt;
    prompt = "x";
    while(prompt != "q")
    {
        cout << "a)nimate, q)uit, t)ick?";
        cin >> prompt;
        if(prompt == "t")
        {
            generateNextGeneration(cells, temp, aliveCells, alive);
        }
        if(prompt == "a")
        {
            int frames;
            cout << "How many frames?";
            cin >> frames;
            for(int f = 0; f < frames; f++)
            {
                clearConsole();
                generateNextGeneration(cells, temp, aliveCells, alive);
                pause(50);
            }
        }
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}
void greetings(){
    cout << "Welcome to the CS106B Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells(X) live and die by the following rules:" << endl
         << "- A cell with 1 or fewer neighbors dies." << endl
         << "- Locations with 2 neighbors remain stable." << endl
         << "- Locations with 3 neighbors will create life." << endl
         << "- A cell with 4 or more neighbors dies" << endl;
}
void readTheGrid(Grid<char>& cells)
{
    int r;
    int c;
    ifstream file;
    string word;
    cout << "Grid input file name? ";
    file.open(promptUserForFile());
    getline(file,word) ;
    r = stringToInteger(word);
    getline(file,word) ;
    c = stringToInteger(word);\
    cells.resize(r, c);
    for(int i = 0; i < r; i++)
    {
        getline(file, word);
        for(int j = 0; j < c; j++)
        {
            cells[i][j] = word[j];
        }
    }
    file.close();
}

void checkAliveNeighbours(Grid<char>& cells, int& alive, int r, int c)
{
    alive = 0;
    checkUpper(cells, alive, r ,c);
    checkDown(cells, alive, r ,c);
    checkLeft(cells, alive, r ,c);
    checkRight(cells, alive, r ,c);
    checkUpperLeft(cells, alive, r ,c);
    checkUpperRight(cells, alive, r ,c);
    checkDownLeft(cells, alive, r ,c);
    checkDownRight(cells, alive, r ,c);
}

bool isCellAlive(Grid<char>& cells, int r, int c)
{
    if(cells[r][c] == 'X')
    {
        return true;
    }
    return false;
}

void checkUpper(Grid<char>& cells, int& alive, int r, int c){
    if(cells.inBounds(r - 1, c))
    {
        if(isCellAlive(cells, r - 1, c))
        {
            alive++;
        }
    }
}

void checkDown(Grid<char>& cells, int& alive, int r, int c){
    if(cells.inBounds(r + 1, c))
    {
        if(isCellAlive(cells, r + 1, c))
        {
            alive++;
        }
    }
}

void checkLeft(Grid<char>& cells,int& alive,int r, int c){

    if(cells.inBounds(r, c - 1))
    {
        if(isCellAlive(cells, r, c - 1))
        {
            alive++;
        }
    }
}

void checkRight(Grid<char>& cells,int& alive,int r, int c){
    if(cells.inBounds(r, c + 1))
    {
        if(isCellAlive(cells, r, c + 1))
        {
            alive++;
        }
    }
}

void checkUpperLeft(Grid<char>& cells,int& alive,int r, int c){
    if(cells.inBounds(r - 1, c - 1))
    {
        if(isCellAlive(cells, r - 1, c - 1))
        {
            alive++;
        }
    }
}

void checkUpperRight(Grid<char>& cells,int& alive,int r, int c){
    if(cells.inBounds(r - 1, c + 1))
    {
        if(isCellAlive(cells, r - 1, c + 1))
        {
            alive++;
        }
    }
}

void checkDownLeft(Grid<char>& cells,int& alive,int r, int c){
    if(cells.inBounds(r + 1, c - 1))
    {
        if(isCellAlive(cells, r + 1, c - 1))
        {
            alive++;
        }
    }
}

void checkDownRight(Grid<char>& cells,int& alive,int r, int c){
    if(cells.inBounds(r + 1, c + 1))
    {
        if(isCellAlive(cells, r + 1, c + 1))
        {
            alive++;
        }
    }

}

void generateNextGeneration(Grid<char>& cells, Grid<char> temp, Grid<int> aliveCells, int& alive)
{
    bool currentCell;
    temp = cells;
    for(int i = 0; i < cells.numRows(); i++)
    {
        for(int j = 0; j < cells.numCols(); j++)
        {
            int souls = aliveCells[i][j];
            currentCell = isCellAlive(cells, i, j);
            checkAliveNeighbours(cells, alive, i, j);
            souls = alive;
            if(!currentCell && souls == 3)
            {
                temp[i][j] = 'X';
            }
            else if(currentCell && souls >= 4)
            {
               temp[i][j] = '-';
            }
            else if(currentCell && souls < 2)
            {
                temp[i][j] = '-';
            }
        }
    }
        cells = temp;
        for(int r = 0; r < temp.numRows(); r++)
        {
        for(int c = 0; c < temp.numCols(); c++)
        {
            cout << temp[r][c];
        }
        cout << endl;
        }

}
