#include <iostream>
#include <vector>
#include <complex>

using namespace std;

// Variables for tic tac toe
const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';
const string GAME_OVER_PLAYER = "[ GAME OVER ]\nPlayer Wins";
const string GAME_OVER_COMPUTER = "[ GAME OVER ]\nComputer Wins";
const string GAME_OVER_TIE = "[ GAME OVER ]\nNo one Wins, it's a Tie";
int general_score = 0;
char board[3][3] =
    {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
    };


// 3 in a row = 100 points
// 2 in a row = 10 points ( if no enemy on the same line, otherwise 0 )
// 1 in a row = 10 points ( if enemy on the same line = 15 points, otherwise 0 )
// center position = 4 points
// corner position = 3 points
// middle position = 2 points


// Gives points for the position
int checkPosition(int x, int y)
{
    if ( x==1 && y==1 )
        return 4;

    if ( (x==0 && y==0) || (x==0 && y==2) || (x==2 && y==0) || (x==2 && y==2) )
        return 3;

    if( (x==0 && y==1) || (x==1 && y==2) || (x==2 && y==1) || (x==1 && y==0) )
        return 2;

    return 0;
}


// Gives points if there are 2 in a row, 0 if there is an enemy
// Gives points if there are 2 enemy in a row, 0 otherwise
int checkTwoInRow(int x, int y)
{
    char character = board[x][y];
    int count = 0;
    int countEnemy = 0;

    for(int column=0;column<3;column++)
    {
        if(board[x][column] == character)
            count++;
        else
            if(board[x][column] != EMPTY)
                countEnemy++;
    }

    switch(count)
    {
        case 1:
            if( countEnemy == 2 )
                return 20;
            return 0;
        case 2:
            if( countEnemy == 1 )
                return 0;
            return 10;
        case 3:
            return 100;
        default:
            return 0;
    }
}


// Gives points if there are 2 in a column, 0 if there is an enemy
// Gives points if there are 2 enemy in a column, 0 otherwise
int checkTwoInColumn(int x, int y)
{
    char character = board[x][y];
    int count = 0;
    int countEnemy = 0;

    for(int row=0;row<3;row++)
    {
        if(board[row][y] == character)
            count++;
        else
            if(board[row][y] != EMPTY)
                countEnemy++;
    }


    switch(count)
    {
        case 1:
            if( countEnemy == 2 )
                return 20;
            return 0;
        case 2:
            if( countEnemy == 1 )
                return 0;
            return 10;
        case 3:
            return 100;
        default:
            return 0;
    }
}


// Checks if the position is on a diagonal
bool isInDiagonal(int x, int y)
{
    if( (x==0 && y==1) || (x==1 && y==2) || (x==2 && y==1) || (x==1 && y==0) )
        return false;
    return true;
}


// Gives points if there are 2 in a diagonal, 0 if there is an enemy
// Gives points if there are 2 enemy in a diagonal, 0 otherwise
int checkTwoInDiagonal(int x, int y)
{
    char character = board[x][y];
    int count = 0;
    int countEnemy = 0;
    int sum = 0;

    if (!isInDiagonal(x, y))
        return 0;

    if( x==1 && y==1 )
    {
        int count2 = 0;
        int countEnemy2 = 0;
        for(int i=0;i<3;i++)
        {
            if( board[i][i] == character )
                count++;
            else
                if(board[i][i] != EMPTY)
                    countEnemy++;

            if( board[i][2-i] == character )
                count2++;
            else
                if(board[i][2-i] != EMPTY)
                    countEnemy2++;
        }


        switch(count)
        {
            case 1:
                if ( countEnemy == 2 )
                {
                    sum += 20;
                    break;
                }
                sum += 0;
                break;
            case 2:
                if( countEnemy == 1 )
                {
                    sum += 0;
                    break;
                }
                sum += 10;
                break;
            case 3:
                sum += 100;
                break;
            default:
                sum += 0;
                break;
        }

        switch(count2)
        {
            case 1:
                if ( countEnemy2 == 2 )
                {
                    sum += 20;
                    break;
                }
                sum += 0;
                break;
            case 2:
                if( countEnemy == 1 )
                {
                    sum += 0;
                    break;
                }
                sum += 10;
                break;
            case 3:
                sum += 100;
                break;
            default:
                sum += 0;
                break;
        }
    }
    else
    {
        if( x==y )
        {
            for(int i=0;i<3;i++)
            {
                if( board[i][i] == character )
                    count++;
                else
                    if(board[i][i] != EMPTY)
                        countEnemy++;
            }
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                if( board[i][2-i] == character )
                    count++;
                else
                    if(board[i][2-i] != EMPTY)
                        countEnemy++;
            }
        }

        switch(count)
        {
            case 1:
                if( countEnemy == 2)
                {
                    sum += 20;
                    break;
                }
                sum += 0;
                break;
            case 2:
                if( countEnemy == 1 )
                {
                    sum += 0;
                    break;
                }
                sum += 10;
                break;
            case 3:
                sum += 100;
                break;
            default:
                sum += 0;
                break;
        }
    }

    return sum;
}


// Gives the points for that position
int givePoints(int x, int y)
{
    return checkPosition(x,y) + checkTwoInRow(x,y) + checkTwoInColumn(x,y) + checkTwoInDiagonal(x,y);
}


// Draws the board
void drawBoard()
{
    cout<<endl;
    cout<<"-------------\n";

    for(int i = 0; i < 3; i++)
    {
        cout<<"| ";
        for(int j = 0; j < 3; j++)
        {
            cout<<board[i][j] << " | ";
        }
        cout<<endl;
        cout<<"-------------\n";
    }
}


// Checks if there is a winner
char checkWin()
{
    if( board[0][0] == board[1][1] && board[0][0] == board[2][2]  && board[0][0] != EMPTY )
        return board[0][0];

    if( board[0][2] == board[1][1] && board[0][2] == board[2][0]  && board[0][2] != EMPTY )
        return board[0][2];

    for(int i=0; i<3; i++)
    {
        if( board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY )
        {
            return board[i][0];
        }

        if( board[0][i] == board[1][i] && board[0][i] == board[2][i]  && board[0][i] != EMPTY )
        {
            return board[0][i];
        }
    }

    return EMPTY;
}


// Checks if there are any moves left
bool checkGameOver()
{
    char winner = checkWin();

    if( winner != EMPTY )
    {
        drawBoard();
        switch(winner)
        {
            case 'X':
                cout<<GAME_OVER_PLAYER;
                break;
            case 'O':
                cout<<GAME_OVER_COMPUTER;
                break;
            default:
                cout<<GAME_OVER_TIE;
                break;
        }
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if( board[i][j] == EMPTY )
                    return false;
            }
        }
        drawBoard();
        cout<<GAME_OVER_TIE;
    }
    return true;
}


// Gets the best move for the computer
void computerMove()
{
    pair<int, int> move;
    move.first = -1;
    move.second = -1;
    int bestScore = -905;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if( board[i][j] == EMPTY )
            {
                board[i][j] = COMPUTER;
                int scoreComputer = givePoints(i,j);

                for(int ii=0;ii<3;ii++)
                {
                    for(int jj=0;jj<3;jj++)
                    {
                        if(board[ii][jj] == EMPTY)
                        {
                            board[ii][jj] = PLAYER;
                            int scorePlayer = givePoints(ii,jj);

                            if(scoreComputer - scorePlayer > bestScore)
                            {
                                bestScore = scoreComputer - scorePlayer;
                                move.first = i;
                                move.second = j;
                                cout<<"["<<ii<<", "<<jj<<"]"<<endl;
                            }

                            board[ii][jj] = EMPTY;
                        }
                    }
                }
                board[i][j] = EMPTY;
            }
        }
    }
    board[move.first][move.second] = COMPUTER;
    general_score -= givePoints(move.first,move.second);
}


// Gets the input of the player
void playerMove()
{
    pair<int, int> move;
    cout<<"Enter your x and y: ";
    cin>>move.first>>move.second;

    while(board[move.first][move.second] != EMPTY || move.first < 0 || move.second < 0 || move.first > 3 || move.second > 3)
    {
        cout<<"The choice is not valid!\nPlease try again.";
        cout<<"Enter your x and y: ";
        cin>>move.first>>move.second;
    }

    board[move.first][move.second] = PLAYER;

    general_score += givePoints(move.first,move.second);
}


int main()
{
    while(true)
    {
        drawBoard();

        playerMove();
        if( checkGameOver() ) break;

        computerMove();
        if( checkGameOver() ) break;
    }

    return 0;
}
