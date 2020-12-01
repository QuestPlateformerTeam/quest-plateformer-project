#include "player.h"
#include "math.h"

Player::Player()
{
    this->life = 3;
}

Player::~Player()
{
    //dtor
}

Player::Player(int x, int y)
{
    this->positionX = x;
    this->positionY = y;
    this->life = 3;

    //Chargement de la spritesheet de Rabidja
    if (!texture.loadFromFile("ressources/graphics/deadpool.png"))
    {
        // Erreur
        std::cout << "Erreur durant le chargement du spritesheet du player." << std::endl;
    }
    else
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT,PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT));
    }
}

void Player::setLife(int newLife)
{
    this->life = newLife;
}
int Player::getLife()
{
    return life;
}

void Player::draw(sf::RenderWindow& window, Map map)
{
    sprite.setPosition(sf::Vector2f(this->positionX,this->positionY));
    window.draw(sprite);
}

void Player::update(Map& map, bool& flagInGame, const int* level)
{
    deplacement(flagInGame);
    wallDetection(map, level);
    stepOn(map, level, EXIT_TILE);
}

void Player::deplacement(bool& flagInGame)
{
     if(hasJump && !lockUp)
    {
        this->positionY-= velocityY*0.7;
        if(fromHeight-this->positionY >= MAX_HEIGHT_JUMP)
            isTopOfJump = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !lockLeft)
    {
        positionX-= MOVESPEED;
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT ,PLAYER_WIDTH * 1.2,PLAYER_WIDTH,PLAYER_HEIGHT));
        if(!hasJump)
            timee++;
            if(timee==5)
            {
                counterWalking++;
                timee =0;
            }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !lockRight)
    {
        positionX+= MOVESPEED;
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT, PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT));
        if(!hasJump)
            timee++;
            if(timee==5)
            {
                counterWalking++;
                timee =0;
            }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !lockUp && canJump)
    {
        hasJump = true;
        isTopOfJump = false;
        fromHeight = this->positionY;
        canJump = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !lockDown)
    {
        positionY+= MOVESPEED;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        flagInGame = false;

    if(counterWalking == 3)
        counterWalking = 0;
}

void Player::wallDetection(Map& map, const int* level)
{
    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        if (level[map.getTileNumber(positionX+20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE )
        {
            lockRight = true;
            //std::cout<<"Collision a droite"<<std::endl;
        }else
        {
            lockRight = false;
        }
        if (level[map.getTileNumber(positionX-20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE )
        {
            lockLeft = true;
            //std::cout<<"Collision a gauche"<<std::endl;
        }else
        {
            lockLeft = false;
        }
        if (level[map.getTileNumber(positionX, positionY+25,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE )
        {
            lockDown = true;
            //std::cout<<"Collision en bas"<<std::endl;
            canJump = true;
            isTopOfJump = false;
        }else if(isTopOfJump || !hasJump)
        {
            lockDown = false;
            this->positionY+= velocityY*0.5;
            hasJump = false;
        }
        if (level[map.getTileNumber(positionX, positionY-25,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE )
        {
            lockUp = true;
            //std::cout<<"Collision en haut"<<std::endl;
            isTopOfJump = true;

        }else
        {
            lockUp = false;
        }
    }
}

void Player::stepOn(Map& map, const int* level, const int itemToDetect)
{
    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        if (level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == itemToDetect )
        {
            map.load("ressources/maps/map2.txt","ressources/graphics/tileset1.png", sf::Vector2u(map.getTileSize(), map.getTileSize()), map.getNbTileByLine(), map.getNbTileByColumn());
            this->positionX = map.getStartX();
            this->positionY = map.getStartY();
        }

        if (level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == 128 )
        {
            this->positionX = map.getStartX();
            this->positionY = map.getStartY();
        }
    }
}

