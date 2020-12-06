#ifndef FIREBALL_H
#define FIREBALL_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Fireball
{
    public:
        Fireball();
        virtual ~Fireball();
        Fireball(const Fireball& f1);
        void draw(sf::RenderWindow& window);
        void setPositionY(int newY);
        sf::Sprite getSprite();
        void reset();
        int getPositionY(){return positionY;};

    protected:

    private:
        sf::Texture texture;
        sf::Sprite fireball;
        int positionX;
        int positionY;
        const int MOVESPEED =2;
};

#endif // FIREBALL_H
