#ifndef COIN_H
#define COIN_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Coin
{
    public:
        Coin();
        Coin(int posX, int posY);
        virtual ~Coin();
        void draw(sf::RenderWindow& window);
        sf::Sprite getCoin();
        void changeDisplay(bool b);
        bool getDisplay();

    protected:

    private:
        sf::Texture texture;
        sf::Sprite aCoin;
        const int COIN_HEIGHT = 200;
        const int COIN_WIDTH = 200;
        int counterAnimation = 0;
        int timee=0;

        int posX;
        int posY;

        bool isDisplayed = false;
};


#endif // COIN_H
