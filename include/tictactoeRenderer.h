#ifndef TICTACTOERENDERER_H
#define TICTACTOERENDERER_H

class tictactoeRenderer
{
    public:
        tictactoeRenderer();
        virtual ~tictactoeRenderer();
        static void start();

    protected:

    private:
};

/* render helper classes */
#include <SFML/Graphics.hpp>
#include <iostream>
class TicTacToeField
{
    sf::RectangleShape r[4];
public:
    TicTacToeField()
    {
        r[0] = sf::RectangleShape(sf::Vector2f(10, 290));
        r[1] = sf::RectangleShape(sf::Vector2f(10, 290));
        r[2] = sf::RectangleShape(sf::Vector2f(290, 10));
        r[3] = sf::RectangleShape(sf::Vector2f(290, 10));

        r[0].setPosition(sf::Vector2f(100, 10));
        r[1].setPosition(sf::Vector2f(200, 10));
        r[2].setPosition(sf::Vector2f(10, 100));
        r[3].setPosition(sf::Vector2f(10, 200));
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(r[0]);
        window.draw(r[1]);
        window.draw(r[2]);
        window.draw(r[3]);
    }
};

class Figure
{
public:
    virtual void draw(sf::RenderWindow &window){}
    virtual ~Figure(){}
};

class xFigure : public Figure
{
private:
    sf::RectangleShape r[2];
public:
    xFigure(int x, int y)
    {
        r[0] = sf::RectangleShape(sf::Vector2f(10, 90));
        r[1] = sf::RectangleShape(sf::Vector2f(10, 90));

        r[0].setOrigin(sf::Vector2f(5, 45));
        r[1].setOrigin(sf::Vector2f(5, 45));

        r[0].setPosition(sf::Vector2f(x, y));
        r[1].setPosition(sf::Vector2f(x, y));

        r[0].setRotation(sf::degrees(45));
        r[1].setRotation(sf::degrees(-45));
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(r[0]);
        window.draw(r[1]);
    }
};

class oFigure : public Figure
{
private:
    sf::CircleShape r[2];
public:
    oFigure(int x, int y)
    {
        r[0] = sf::CircleShape(40);
        r[1] = sf::CircleShape(30);

        r[0].setOrigin(sf::Vector2f(28, 28));
        r[1].setOrigin(sf::Vector2f(21, 21));

        r[0].setPosition(sf::Vector2f(x, y));
        r[1].setPosition(sf::Vector2f(x+3.5, y+3.5));

        r[0].setFillColor(sf::Color::White);
        r[1].setFillColor(sf::Color::Black);
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(r[0]);
        window.draw(r[1]);
    }
};

#endif // TICTACTOERENDERER_H
