#include "player.h"
#include "math.h"

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
        sprite.setTextureRect(sf::IntRect(0,0,PLAYER_WIDTH,PLAYER_HEIGHT));
    }
}

void Player::draw(sf::RenderWindow& window, Map map)
{
    sprite.setPosition(sf::Vector2f(this->positionX,this->positionY));
    window.draw(sprite);
}

void Player::update(Map map, bool& flagInGame, const int* level)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !lockLeft)
    {
        positionX-= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !lockRight)
    {
        positionX+= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !lockUp && canJump)
    {
        positionY-=speed+100;
        canJump = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !lockDown)
    {
        positionY+= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        flagInGame = false;
    }


    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        std::cout<<std::to_string(map.getTileNumber(positionX, positionY))<<std::endl;

        if (level[map.getTileNumber(positionX+20, positionY)] == 60 )
        {
            std::cout<<"Collision a droite"<<std::endl;
            lockRight = true;
        }else
        {
            lockRight = false;
        }
        if (level[map.getTileNumber(positionX-20, positionY)] == 60 )
        {
            std::cout<<"Collision a gauche"<<std::endl;
            lockLeft = true;
        }else
        {
            lockLeft = false;
        }
        if (level[map.getTileNumber(positionX, positionY+25)] == 60 )
        {
            std::cout<<"Collision en bas"<<std::endl;
            lockDown = true;
            canJump = true;
        }else
        {
            this->positionY+= velocityY*1.05;
            lockDown = false;
        }
        if (level[map.getTileNumber(positionX, positionY-25)] == 60 )
        {
            std::cout<<"Collision en haut"<<std::endl;
            lockUp = true;
        }else
        {
            lockUp = false;
        }
    }
}
