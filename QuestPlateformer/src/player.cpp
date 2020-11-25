#include "player.h"

Player::Player()
{

}

Player::~Player()
{
    //dtor
}

Player::Player(int x, int y)
{
    this->positionX = x;
    this->positionY = y;
    //Chargement de la spritesheet de Rabidja
    if (!texture.loadFromFile("ressources/graphics/rabidja.png"))
    {
        // Erreur
        std::cout << "Erreur durant le chargement du spritesheet de Rabidja." << std::endl;
    }
    else
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0,0,40,50));
    }
}

void Player::draw(sf::RenderWindow& window, Map map)
{
    sprite.setPosition(sf::Vector2f(this->positionX,this->positionY));
    window.draw(sprite);
}

void Player::update(Map map, bool& flagInGame)
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(this->positionX>0)
            this->positionX-=MOVESPEED;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(this->positionX < SCREEN_WIDTH - sprite.getGlobalBounds().width)
            this->positionX+=MOVESPEED;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(this->positionY>0)
        {
            this->positionY-=MOVESPEED;
            topJump = true;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(this->positionY < SCREEN_HEIGHT - sprite.getGlobalBounds().height)
            this->positionY+=MOVESPEED;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        flagInGame = false;
    }

    if(this->positionY < (SCREEN_HEIGHT - rectangle.getGlobalBounds().height))
    {
        //this->positionY+= MOVESPEED;
    }

}
