#include "tictactoeAgent.h"
#include <iostream>

tictactoeAgent::tictactoeAgent()
{
    //ctor
}

tictactoeAgent::~tictactoeAgent()
{
    //dtor
}
char tictactoeAgent::win(char field[3][3])
{
    /*
    return 'o' if player with character 'o' won the game
    return ' ' if the game is not won yet or a stalemate
    */

    for(int i = 0; i < 3; i++)
    {
        char horizontal = field[0][i];
        char vertical = field[i][0];

        bool horizontalWin = horizontal != ' ';
        bool verticalWin = vertical != ' ';

        for(int j = 1; j < 3; j++)
        {
            if(field[j][i] != horizontal)
                horizontalWin = false;
            if(field[i][j] != vertical)
                verticalWin = false;
        }

        if(verticalWin)
            return vertical;
        if(horizontalWin)
            return horizontal;
    }

    if(field[0][0] == field[1][1] && field[0][0] == field[2][2] && field[0][0] != ' ')
        return field[0][0];
    if(field[2][0] == field[1][1] && field[2][0] == field[0][2] && field[2][0] != ' ')
        return field[2][0];

    return ' ';

}

bool tictactoeAgent::draw(char field[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(field[i][j] == ' ')
                return false;
    return true;
}

std::pair<int, int> tictactoeAgent::action(char field[3][3], char self, char opponent, bool debug)
{
    int temp;
    std::pair<int, std::pair<int, int>> choice = std::make_pair(-10, std::make_pair(0, 0));

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp = recursiveMoveMin(field, self, opponent, i, j);

            if(temp > choice.first)
                choice = std::make_pair(temp, std::make_pair(i, j));

            if(debug)
                std::cout << i << " " << j << ": " << temp << std::endl;
        }
    }
    return choice.second;
}

int tictactoeAgent::recursiveMoveMax(char field[3][3], char self, char opponent, int x, int y)
{
    char newfield[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            newfield[i][j] = field[i][j];

    if(newfield[x][y] != ' ')
        return -2;

    /**/
    newfield[x][y] = opponent;

    if(win(newfield) == opponent)
        return -1;

    if(draw(newfield))
        return 0;

    int temp;
    int best = -1;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp = recursiveMoveMin(newfield, self, opponent, i, j);
            if(temp > best)
                best = temp;
        }
    }
    return best;
}

int tictactoeAgent::recursiveMoveMin(char field[3][3], char self, char opponent, int x, int y)
{
    char newfield[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            newfield[i][j] = field[i][j];

    if(newfield[x][y] != ' ')
        return -2;

    /**/
    newfield[x][y] = self;

    if(win(newfield) == self)
        return 1;

    if(draw(newfield))
        return 0;

    int temp;
    int worst = 1.0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp = recursiveMoveMax(newfield, self, opponent, i, j);
            if(temp < worst && temp != -2)
                worst = temp;
        }
    }
    return worst;
}
