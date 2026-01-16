#include "player.h"
#include "Collision.h"

// Constructeur de l'objet Player
Player::Player(int x, int y)
{
    // J'affecte à mon joueur une position X et Y sur la fenêtre.
    this->positionX = x;
    this->positionY = y;

    // Je charge une texture et je mets la texture dans le sprite pour pouvoir l'utiliser à l'écran
    if (!texture.loadFromFile("../ressources/graphics/deadpool.png"))
        std::cout << "Erreur durant le chargement du spritesheet du player." << std::endl;
    else
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT, PLAYER_WIDTH * 2.4, PLAYER_WIDTH, PLAYER_HEIGHT));
    }

    // Chargement des fichiers audio
    if (!soundDeath.openFromFile("../ressources/songs/deathSound.ogg"))
        std::cout << "Erreur lors du chargement du son de mort" << std::endl;
    soundDeath.setVolume(10.f);

    if (!soundCoin.openFromFile("../ressources/songs/coin.ogg"))
        std::cout << "Erreur lors du chargement du son de pièce" << std::endl;
    soundCoin.setVolume(10.f);
}

Player::~Player()
{
    // destructeur
}

/*
    =================
    Getters & Setters
    =================
*/
void Player::setLife(int newLife) { this->life = newLife; }
int Player::getLife() { return life; }

void Player::setPlayerAtStart(Map map)
{
    this->positionX = map.getStartX();
    this->positionY = map.getStartY();
}

void Player::isDead(Map& map, bool& flagEndGame, bool& flagInGame)
{
    sf::sleep(sf::milliseconds(750));

    if(life > 1)
    {
        life--;
        sprite.setTextureRect(sf::IntRect(1 * PLAYER_HEIGHT, PLAYER_WIDTH * 2.4, PLAYER_WIDTH, PLAYER_HEIGHT));
        setPlayerAtStart(map);
    }
    else
    {
        flagEndGame = true;
        flagInGame = false;

        map.resetGame();
        setLife(3);
        setPlayerAtStart(map);
    }
}

void Player::draw(sf::RenderWindow& window, Map map)
{
    window.draw(sprite);
}

void Player::update(Map& map, bool& flagInGame, const int* level, FireballContainer& fireballContainer, CoinContainer& coinContainer, bool& flagEndGame, bool& flagGameOver, bool& flagPause)
{
    deplacement(flagInGame, map, level, flagPause);
    sprite.setPosition(sf::Vector2f(this->positionX, this->positionY));

    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        if (level[map.getTileNumber(positionX, positionY, PLAYER_WIDTH, PLAYER_HEIGHT)] == EXIT_TILE && coinContainer.isAllLooted())
        {
            map.changeToNextLevel(flagEndGame, flagInGame);
            setPlayerAtStart(map);
            fireballContainer.resetAll();
            coinContainer.loadConfig(map);
            coinContainer.resetAll();
            coinContainer.setLooted(false);
            if(flagEndGame)
                life = 3;
        }

        if ((level[map.getTileNumber(positionX, positionY, PLAYER_WIDTH, PLAYER_HEIGHT)]) == TILE_KILL)
        {
            soundDeath.stop();
            soundDeath.play();
            isDead(map, flagEndGame, flagInGame);
            fireballContainer.resetAll();
            coinContainer.loadConfig(map);
            coinContainer.resetAll();
        }
    }

    for(int i = 0; i <= fireballContainer.getNbFireball(); i++)
    {
        if (Collision::PixelPerfectTest(sprite, fireballContainer.getOneFireball(i).getSprite()))
        {
            soundDeath.stop();
            soundDeath.play();
            isDead(map, flagEndGame, flagInGame);
            fireballContainer.resetAll();
            coinContainer.loadConfig(map);
            coinContainer.resetAll();
            hasJump = false;
        }
    }

    for(int i = 0; i <= coinContainer.getNbCoin(); i++)
    {
        if(Collision::PixelPerfectTest(sprite, coinContainer.getOneCoin(i)) && coinContainer.getThisCoin(i).getDisplay())
        {
            soundCoin.stop();
            soundCoin.play();
            coinContainer.changeToNextCoin();
        }
    }
}

void Player::deplacement(bool& flagInGame, Map& map, const int* level, bool& flagPause)
{
    if(hasJump && !lockUp)
    {
        this->positionY -= velocityY * 0.7;
        if(fromHeight - this->positionY >= MAX_HEIGHT_JUMP)
            isTopOfJump = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !lockLeft)
    {
        positionX -= MOVESPEED;
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT, PLAYER_WIDTH * 1.2, PLAYER_WIDTH, PLAYER_HEIGHT));
        if(!hasJump)
        {
            timee++;
            if(timee == 5)
            {
                counterWalking++;
                timee = 0;
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !lockRight)
    {
        positionX += MOVESPEED;
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT, PLAYER_WIDTH * 2.4, PLAYER_WIDTH, PLAYER_HEIGHT));
        if(!hasJump)
        {
            timee++;
            if(timee == 5)
            {
                counterWalking++;
                timee = 0;
            }
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
    {
        flagInGame = false;
        flagPause = true;
    }

    if(counterWalking == 3)
        counterWalking = 0;

    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds()))
    {
        if ((level[map.getTileNumber(positionX + 20, positionY, PLAYER_WIDTH, PLAYER_HEIGHT)] == WALL_TILE) || positionX >= 780)
            lockRight = true;
        else
            lockRight = false;

        if ((level[map.getTileNumber(positionX - 20, positionY, PLAYER_WIDTH, PLAYER_HEIGHT)] == WALL_TILE) || positionX <= -5)
            lockLeft = true;
        else
            lockLeft = false;

        if (level[map.getTileNumber(positionX, positionY + 25, PLAYER_WIDTH, PLAYER_HEIGHT)] == WALL_TILE)
        {
            lockDown = true;
            canJump = true;
            isTopOfJump = false;
        }
        else if(isTopOfJump || !hasJump)
        {
            lockDown = false;
            this->positionY += velocityY * 0.5;
            hasJump = false;
        }

        if ((level[map.getTileNumber(positionX, positionY - 25, PLAYER_WIDTH, PLAYER_HEIGHT)] == WALL_TILE) || positionY >= 455)
        {
            lockUp = true;
            isTopOfJump = true;
        }
        else
            lockUp = false;
    }
}
