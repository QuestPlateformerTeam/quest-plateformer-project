#ifndef FIREBALL_H
#define FIREBALL_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Fireball
{
    public:
        Fireball();
        virtual ~Fireball();
        Fireball(const Fireball& f1){}
        void draw(sf::RenderWindow& window);
        void setPositionY(int newY);
        sf::FloatRect getGlobalForIntersect();
        void reset();
        int getPositionY(){return positionY;};

    protected:

    private:
        //sf::RectangleShape fireball;
        sf::Texture texture;
        sf::Sprite fireball;
        int positionX;
        int positionY;
        const int MOVESPEED =2;
};

#endif // FIREBALL_H
