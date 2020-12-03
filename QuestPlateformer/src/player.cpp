#include "player.h"
#include "math.h"


Player::Player(int x, int y)
{
    this->positionX = x;
    this->positionY = y;

    if (!texture.loadFromFile("ressources/graphics/deadpool.png"))
        std::cout << "Erreur durant le chargement du spritesheet du player." << std::endl;
    else
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT,PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT));
    }

}

Player::~Player()
{
    //dtor
}

void Player::setPlayerAtStart(Map map)
{

    this->positionX = map.getStartX();
    this->positionY = map.getStartY();
}

void Player::isDead(Map& map)
{
    sf::sleep(sf::milliseconds(750));

    if(life > 1)
    {
        life--;
        sprite.setTextureRect(sf::IntRect(1 * PLAYER_HEIGHT ,PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT));
        setPlayerAtStart(map);

    }else
    {
        flagGameOver = true;
        map.resetGame();
        setLife(3);
        setPlayerAtStart(map);
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

void Player::update(Map& map, bool& flagInGame, const int* level, FireballContainer& fireballContainer, CoinContainer& coinContainer)
{
    deplacement(flagInGame,map,level);


    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        if (level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == EXIT_TILE && coinContainer.isAllLooted() )
        {
            map.changeToNextLevel();
            setPlayerAtStart(map);
            fireballContainer.resetAll();
            coinContainer.loadConfig(map);
            coinContainer.resetAll();
            coinContainer.setLooted(false);
        }

        if ((level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)]) == TILE_KILL )
        {
            isDead(map);
            fireballContainer.resetAll();
        }

    }

    for(int i = 0; i<=fireballContainer.getNbFireball(); i++)
    {
        if (Collision::PixelPerfectTest(sprite,fireballContainer.getOneFireball(i).getSprite(),128))
        {
            isDead(map);
            fireballContainer.resetAll();
            hasJump = false;
        }
    }

    for(int i = 0; i<=coinContainer.getNbCoin(); i++)
    {
        if(Collision::PixelPerfectTest(sprite,coinContainer.getOneCoin(i),128) && coinContainer.getThisCoin(i).getDisplay())
            coinContainer.changeToNextCoin();
    }
}

void Player::deplacement(bool& flagInGame, Map& map,const int* level)
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        flagInGame = false;

    if(counterWalking == 3)
        counterWalking = 0;

    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {

        if (level[map.getTileNumber(positionX+20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE)
            {
            lockRight = true;
            //std::cout<<"Collision a droite"<<std::endl;
        }else
        {
            lockRight = false;
        }
        if (level[map.getTileNumber(positionX-20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE)
        {
            lockLeft = true;
            //std::cout<<"Collision a gauche"<<std::endl;
        }else
        {
            lockLeft = false;
        }
        if ((level[map.getTileNumber(positionX, positionY+25,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE))
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

