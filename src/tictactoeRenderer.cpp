#include "tictactoeRenderer.h"
#include "tictactoeAgent.h"

#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>


tictactoeRenderer::tictactoeRenderer()
{
    //ctor
}

tictactoeRenderer::~tictactoeRenderer()
{
    //dtor
}

void tictactoeRenderer::start()
{
    tictactoeAgent t;
    char field[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    TicTacToeField tttfield;
    srand(time(0));
    int c = rand()%2;
    std::vector<Figure*> figures;
    sf::RenderWindow window(sf::VideoMode({800, 500}), "TicTacToe");

    sf::Font font;
    if(!font.openFromFile("arial.ttf") && !font.openFromFile("bin/Release/arial.ttf")) {
        return;
    }

    sf::Text text(font, "", 200);
    text.setPosition(sf::Vector2f(500, 200));
    text.setCharacterSize(20);


    while (window.isOpen())
    {
        //player turn
        if(c % 2)
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
                {
                    auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                    int x = mouse->position.x;
                    int y = mouse->position.y;
                    if(x < 300 && y < 300)
                    {
                        if(field[x/100][y/100] == ' ')
                        {
                            field[x/100][y/100] = 'x';
                            figures.push_back(new xFigure((x/100) * 100 + 55, (y/100) * 100 + 55));
                            c++;
                        }
                    }
                }
            }
        }
        //computer turn
        else
        {
           while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            std::pair<int, int> bestMove = t.action(field, 'o', 'x');
            field[bestMove.first][bestMove.second] = 'o';
            figures.push_back(new oFigure(bestMove.first * 100 + 40, bestMove.second * 100 + 40));
            c++;

        }

        bool ended = false;
        if(t.win(field) != ' ')
        {
            sf::String s;
            s += t.win(field);
            text.setString(s + " won. \nClick anywhere to play again");
            ended = true;
        }
        else if(t.draw(field))
        {
            text.setString("Draw. \nClick anywhere to play again");
            ended = true;
        }
        if(ended)
        {
            window.clear();

            tttfield.draw(window);
            window.draw(text);
            for(Figure *figure : figures)
                figure->draw(window);

            window.display();
        }

        while(ended)
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if ((event->is<sf::Event::MouseButtonPressed>()) && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
                {
                    c = rand()%2;
                    for(int i = 0; i < 3; i++)
                        for(int j = 0; j < 3; j++)
                            field[i][j] = ' ';

                    for(Figure *f : figures)
                        delete f;
                    figures.clear();

                    text.setString("");
                    ended = false;
                }
            }
        }


        window.clear();

        tttfield.draw(window);
        window.draw(text);
        for(Figure *figure : figures)
            figure->draw(window);

        window.display();

        sf::sleep(sf::seconds(0.1f));
    }
}
