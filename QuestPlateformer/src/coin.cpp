#include "coin.h"

Coin::Coin()
{
    if(!texture.loadFromFile("ressources/graphics/coin.png"))//Charger l'image de la pièce
        std::cout<<"Erreur chargement coin"<<std::endl;
    aCoin.setTexture(texture);
    aCoin.setTextureRect(sf::IntRect(counterAnimation*COIN_WIDTH+20,42,COIN_WIDTH,COIN_HEIGHT));
    aCoin.setScale(0.2,0.2);
}

Coin::Coin(int posX, int posY)
{
    if(!texture.loadFromFile("ressources/graphics/coin.png")) //Je charge la texture de ma pièce
        std::cout<<"Erreur chargement coin"<<std::endl;

    aCoin.setTexture(texture);
    aCoin.setTextureRect(sf::IntRect(counterAnimation*COIN_WIDTH+20,42,COIN_WIDTH,COIN_HEIGHT)); //Je règle osn format sur la spritesheet
    aCoin.setScale(0.15,0.15); //Je set une echelle
    aCoin.setPosition(sf::Vector2f(posX,posY)); //Et je set une position de départ
}

Coin::~Coin(){} //Destructeur

sf::Sprite Coin::getCoin(){return aCoin;}
void Coin::changeDisplay(bool b){isDisplayed = b;}
bool Coin::getDisplay(){return isDisplayed;}

void Coin::draw(sf::RenderWindow& window)
{
    if(isDisplayed)
    {
        this->timee++; //boucle pour allonger le temps avant une animation
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

