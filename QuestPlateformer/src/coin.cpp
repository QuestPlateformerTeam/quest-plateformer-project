#include "coin.h"

Coin::Coin()
{
    if(!texture.loadFromFile("ressources/graphics/coin.png"))
        std::cout<<"Erreur chargement coin"<<std::endl;
    aCoin.setTexture(texture);
    aCoin.setTextureRect(sf::IntRect(counterAnimation*COIN_WIDTH+20,42,COIN_WIDTH,COIN_HEIGHT));
    aCoin.setScale(0.2,0.2);

}

Coin::Coin(int posX, int posY)
{
    if(!texture.loadFromFile("ressources/graphics/coin.png"))
        std::cout<<"Erreur chargement coin"<<std::endl;
    aCoin.setTexture(texture);
    aCoin.setTextureRect(sf::IntRect(counterAnimation*COIN_WIDTH+20,42,COIN_WIDTH,COIN_HEIGHT));
    aCoin.setScale(0.15,0.15);
    aCoin.setPosition(sf::Vector2f(posX,posY));
}

Coin::~Coin()
{

}

sf::Sprite Coin::getCoin()
{
    return aCoin;
}

void Coin::changeDisplay(bool b)
{
    isDisplayed = b;
}

bool Coin::getDisplay()
{
    return isDisplayed;
}

void Coin::draw(sf::RenderWindow& window)
{
    if(isDisplayed)
    {
        this->timee++;
        if(timee==7)
        {
            if(counterAnimation==5)
                counterAnimation=0;

            counterAnimation++;
            timee=0;
        }
        aCoin.setTextureRect(sf::IntRect(counterAnimation*COIN_WIDTH+20,42,COIN_WIDTH,COIN_HEIGHT));
        window.draw(aCoin);
    }
}

