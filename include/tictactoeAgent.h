#ifndef TICTACTOEAGENT_H
#define TICTACTOEAGENT_H

#include <utility>


class tictactoeAgent
{
public:
    tictactoeAgent();
    virtual ~tictactoeAgent();
    std::pair<int,int> action(char[3][3], char, char, bool=false);
    char win(char[3][3]);
    bool draw(char[3][3]);
protected:

private:
    int recursiveMoveMax(char[3][3], char, char, int, int);
    int recursiveMoveMin(char[3][3], char, char, int, int);

};

#endif // TICTACTOEAGENT_H
