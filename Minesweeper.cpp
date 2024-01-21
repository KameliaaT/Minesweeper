#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

using namespace std;

constexpr int MAX_SIZE = 10;
constexpr int MIN_SIZE = 3;
constexpr char MINE = '*';
constexpr char NOT_OPEN = '-';
constexpr char MARKED = 'M';
int BOARDSIZE, MINES;

int maxMoves(unsigned int size, unsigned int minesCount)
{
    return size * size - minesCount;
}

bool isValidSize(int size)
{
    return size >= MIN_SIZE && size <= MAX_SIZE;
}

bool isValidRowOrCol(int x)
{
    return x >= 0 && x < BOARDSIZE;
}

bool isValidCountOfMines(unsigned int size, unsigned int minesCount)
{
    return minesCount >= 1 && minesCount <= 3 * size;
}
//i do not know if i am allowed to use that function, but it wokrs way more faster than the one below.
//std::random_device rd; : Creates a random_device object, which is a source of 
// non - deterministic random numbers.It is used to obtain a seed for the random number generator.
//
//std::mt19937 gen(rd()); : Creates a Mersenne Twister engine(std::mt19937) with 
// the seed obtained from the random_device.The Mersenne Twister is a high - quality pseudo - 
// random number generator.
//
//std::uniform_int_distribution<> dis(0, size - 1); : Creates a uniform distribution object
//for generating random integers.In this case, it is configured to generate integers in the range[0, size - 1].
void generateRandom(unsigned int& row, unsigned int& column, unsigned int size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);

    row = dis(gen);
    column = dis(gen);
} 
// This is the initial function , that i used , but when the mines are more than three, it generates them too slow.
// However, it still works right.
//void generateRandom(unsigned int& row, unsigned int& column, unsigned int size)
//{
//    srand(static_cast<unsigned>(time(0)));
//    row = rand() % size;
//    column = rand() % size;
//}

void gameStartMessages()
{
    cout << "Enter a number between 3 and 10, which will be the size of the game board: ";
    while (cin >> BOARDSIZE && !isValidSize(BOARDSIZE))
    {
        cout << "Please enter a valid size!" << endl;
    }
    cout << endl;
    int maxMinesCount = 3 * BOARDSIZE;
    cout << "Enter a number between 1 and " << maxMinesCount << ", which will be the count of mines in the current game.";
    while (cin >> MINES && !isValidCountOfMines(BOARDSIZE, MINES))
    {
        cout << "Please enter a valid count of mines!" << endl;
    }
    cout << endl;
    int maxMove = maxMoves(BOARDSIZE, MINES);
    cout << "In case you do not choose a cell with a mine not once in the game, you have a total of " << maxMove << " moves." << endl;
    cout << "You only lose moves when opening a cell." << endl;
}

void printBoard(char toPrint[MAX_SIZE][MAX_SIZE], unsigned int size)
{
    int consoleWidth = 80;
    int leftMargin = (consoleWidth - size * 3) / 2;

    cout << setw(leftMargin + 2) << ' ';
    for (int i = 0; i < size; ++i)
    {
        cout << setw(3) << i;
    }
    cout << endl << setw(leftMargin + 2) << ' ';
    for (int i = 0; i < size; ++i)
    {
        cout << setw(3) << ".";
    }
    cout << endl;

    for (int i = 0; i < size; ++i)
    {
        cout << setw(leftMargin) << i << ' ' << '.';

        for (int j = 0; j < size; ++j)
        {
            cout << setw(3) << toPrint[i][j];
        }
        cout << endl;
    }
}

int countMinesAround(int row, int column, char gameBoard[MAX_SIZE][MAX_SIZE], int size)
{
    int count = 0;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int newRow = row + i;
            int newCol = column + j;

            if (isValidRowOrCol(newRow) && isValidRowOrCol(newCol))
            {
                if (gameBoard[newRow][newCol] == MINE)
                {
                    count++;
                }
            }
        }
    }

    return count;
}
void revealAllSellsAroundIfCurrentIsNull(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE], int x, int y)
{
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {

            if ((i == 0 || j == 0) && !(i == 0 && j == 0))
            {
                int newRow = x + i;
                int newCol = y + j;

                if (isValidRowOrCol(newRow) && isValidRowOrCol(newCol) && toPrint[newRow][newCol] == NOT_OPEN)
                {
                    int minesAround = countMinesAround(newRow, newCol, minesBoard, BOARDSIZE);
                    toPrint[newRow][newCol] = minesAround + '0';

                    if (minesAround == 0)
                    {
                        revealAllSellsAroundIfCurrentIsNull(toPrint, minesBoard, newRow, newCol);
                    }
                }
            }
        }
    }
}

bool isMine(char board[MAX_SIZE][MAX_SIZE], int x, int y)
{
    return board[x][y] == MINE;
}

void initBothBoards(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            toPrint[i][j] = NOT_OPEN;
            minesBoard[i][j] = NOT_OPEN;
        }
    }
}

void placeMines(char minesBoard[MAX_SIZE][MAX_SIZE])
{
    int minesCount = MINES;
    while (minesCount--)
    {
        unsigned int row, column;
        generateRandom(row, column, BOARDSIZE);
        if (minesBoard[row][column] != MINE)
        {
            minesBoard[row][column] = MINE;
        }
        else
        {
            minesCount++;
        }
    }
}

void placeMinesToPrintBoard(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (minesBoard[i][j] == MINE)
            {
                toPrint[i][j] = MINE;
            }
        }
    }
}
void printMinesLocations(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE], unsigned int size)
{
    cout << "Mines Locations:" << endl;
    placeMinesToPrintBoard(toPrint, minesBoard);
    printBoard(toPrint, size);
}
int countOpened(char toPrint[MAX_SIZE][MAX_SIZE], int& previousOpenedCount)
{
    int count = 0;
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (toPrint[i][j] != NOT_OPEN)
            {
                count++;
            }
        }
    }

    int newlyOpened = count - previousOpenedCount;
    previousOpenedCount = count;  

    return newlyOpened;
}

int openCell(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE], int x, int y, int& movesLeft, int& previousOpenedCount)
{
    if (toPrint[x][y] == MARKED)
    {
        cout << "Cell is marked as mine. Please unmark it first." << endl;
        return false;
    }

    if (isMine(minesBoard, x, y))
    {
        cout << "Game Over! You hit a mine." << endl;
        toPrint[x][y] = MINE;
        return true;
    }
    else
    {
        int minesAround = countMinesAround(x, y, minesBoard, BOARDSIZE);
        toPrint[x][y] = minesAround + '0';
        if (minesAround == 0)
        {
            revealAllSellsAroundIfCurrentIsNull(toPrint, minesBoard, x, y);
            cout << "If you uncover a cell with a value of 0, you will lose as many moves as the number of cells that were opened simultaneously." << endl;
            movesLeft -= countOpened(toPrint, previousOpenedCount);
            movesLeft++;
        }
        movesLeft--;
        return false;
    }
}


void markCell(char toPrint[MAX_SIZE][MAX_SIZE], int x, int y)
{
    if (toPrint[x][y] == MARKED)
    {
        cout << "Cell is already marked as mine." << endl;
    }
    else if (toPrint[x][y] != NOT_OPEN)
    {
        cout << "You can not mark opened cells.";
    }
    else
    {
        toPrint[x][y] = MARKED;
        cout << "Cell marked as mine." << endl;
    }
}

void unmarkCell(char toPrint[MAX_SIZE][MAX_SIZE], int x, int y)
{
    if (toPrint[x][y] == MARKED)
    {
        toPrint[x][y] = NOT_OPEN;
        cout << "Cell unmarked." << endl;
    }
    else
    {
        cout << "Cell is not marked. Can't unmark." << endl;
    }
}

void commands(char command, char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE], int x, int y, int& movesLeft, int& previousOpenedCount)
{
    switch (command)
    {
    case 'o':
        openCell(toPrint, minesBoard, x, y, movesLeft, previousOpenedCount);
        break;
    case 'm':
        markCell(toPrint, x, y);
        break;
    case 'u':
        unmarkCell(toPrint, x, y);
        break;
    default:
        cout << "Invalid command. Please enter a valid command (o, m, u)." << endl;
        cout << "Make sure you are using the Latin alphabet!" << endl;
        break;
    }
}


bool allMinesAreMarked(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE])
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (minesBoard[i][j] == MINE && toPrint[i][j] != MARKED)
            {
                return false;
            }

        }
    }
    return true;
}

bool isValidCommand(char command)
{
    return command == 'o' || command == 'm' || command == 'u';
}

void playMinesweeper(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE])
{
    int movesLeft = maxMoves(BOARDSIZE, MINES);
    bool gameOver = false;
    int previousOpenedCount = 0;

    while (!gameOver)
    {
        printBoard(toPrint, BOARDSIZE);
        cout << endl;
        char command;
        int x, y;

        cout << "Enter your command (o - open, m - mark, u - unmark) and two numbers between 0 and " << BOARDSIZE - 1 << " representing row and column: ";
        cout << endl << "Make sure you are using the Latin alphabet and that there are spaces between the command and each of the numbers" << endl;
        cin >> command >> x >> y;
        if (!isValidCommand(command))
        {
            cout << "Invalid command ! Please enter a valid command." << endl;
            cout << "Make sure you are using the Latin alphabet and that there are spaces between the command and each of the numbers" << endl;
            continue;
        }

        if (!isValidRowOrCol(x) || !isValidRowOrCol(y))
        {
            cout << "Invalid move! Please enter valid row and column." << endl;
            continue;
        }

        commands(command, toPrint, minesBoard, x, y, movesLeft, previousOpenedCount);
        if (toPrint[x][y] == MINE)
        {
            gameOver = true;
        }
        else if (allMinesAreMarked(toPrint, minesBoard))
        {
            gameOver = true;
            cout << "Congratulations! You've cleared the board without hitting a mine." << endl;
        }
        else
        {
            if (movesLeft == 0)
            {
                cout << "Congratulations! You've cleared the board without hitting a mine." << endl;
                gameOver = true;
            }
        }
        if (!gameOver)
        {
           cout << "Moves left: " << movesLeft << endl;
           cout<<"In case you have for example one move left and only mines left on board, just mark all of the mines"<<endl;
        }
    }
}

void play(char toPrint[MAX_SIZE][MAX_SIZE], char minesBoard[MAX_SIZE][MAX_SIZE])
{
    gameStartMessages();
    initBothBoards(toPrint, minesBoard);
    placeMines(minesBoard);
    playMinesweeper(toPrint, minesBoard);
    cout << "Final board with mine locations:" << endl;
    printMinesLocations(toPrint, minesBoard, BOARDSIZE);
}

int main()
{

    char toPrint[MAX_SIZE][MAX_SIZE], minesBoard[MAX_SIZE][MAX_SIZE];
    play(toPrint, minesBoard);

    return 0;
}
