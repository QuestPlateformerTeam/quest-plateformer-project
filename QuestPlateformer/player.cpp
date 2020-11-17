#include "player.h"
#include "map.h"
#include "input.h"

using namespace std;
using namespace sf;

//Constructeur

Player::Player()
{
//Chargement de la spritesheet de Rabidja
    if (!rabidjaTexture.loadFromFile("ressources/graphics/rabidja.png"))
    {
// Erreur
        cout << "Erreur durant le chargement du spritesheet de Rabidja." << endl;
    }
    else
        rabidja.setTexture(rabidjaTexture);

//Initialisation des variables :
    dirX = 0;
    dirY = 0;
    life = 3;
    invincibleTimer = 0;
    x = y = h = w = 0;
    checkpointActif = false;
    respawnX = respawnY = 0;
    frameNumber = frameTimer = frameMax = 0;
    etat = direction = 0;
    timerMort = 0;
    onGround = false;
    dirX = dirY = 0;
    saveX = saveY = 0;
    Playerjump = false;

}


//Accesseurs
int Player::getX(void) const
{
    return x;
}
int Player::getY(void) const
{
    return y;
}
int Player::getW(void) const
{
    return w;
}
int Player::getH(void) const
{
    return h;
}
float Player::getDirX(void) const
{
    return dirX;
}
float Player::getDirY(void) const
{
    return dirY;
}
int Player::getOnGround(void) const
{
    return onGround;
}
int Player::getLife(void) const
{
    return life;
}
int Player::getVies(void) const
{
    return vies;
}
int Player::getEtoiles(void) const
{
    return etoiles;
}
int Player::getDirection(void) const
{
    return direction;
}


//Mutateurs
void Player::setX(int valeur)
{
    x = valeur;
}
void Player::setY(int valeur)
{
    y = valeur;
}
void Player::setW(int valeur)
{
    w = valeur;
}
void Player::setH(int valeur)
{
    h = valeur;
}
void Player::setDirX(float valeur)
{
    dirX = valeur;
}
void Player::setDirY(float valeur)
{
    dirY = valeur;
}
void Player::setOnGround(bool valeur)
{
    onGround = valeur;
}
void Player::setTimerMort(int valeur)
{
    timerMort = valeur;
}
void Player::setVies(int valeur)
{
    vies = valeur;
}
void Player::setEtoiles(int valeur)
{
    etoiles = valeur;
}
void Player::setCheckpoint(bool valeur)
{
    checkpointActif = valeur;
}

void Player::initialize(Map &map, bool newLevel)
{
    life = 3;
    invincibleTimer = 0;
    direction = RIGHT;
    etat = IDLE;
    frameNumber = 0;
    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
    frameMax = 8;


    if (checkpointActif == true)
    {
        x = respawnX;
        y = respawnY;
    }
    else
    {
        x = map.getBeginX();
        y = map.getBeginY();
    }

    map.setStartX(0);
    map.setStartY(0);


    w = PLAYER_WIDTH;
    h = PLAYER_HEIGTH;

    timerMort = 0;
    onGround = false;
}

void Player::draw(Map &map, RenderWindow &window)
{
    if (frameTimer <= 0)
    {
//On le réinitialise
        frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        frameNumber++;
        if (frameNumber >= frameMax)
            frameNumber = 0;
    }
    else
        frameTimer--;


    rabidja.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));

    if (invincibleTimer > 0)
    {

        if (frameNumber % 2 == 0)
        {
            if (direction == LEFT)
            {
                rabidja.setTextureRect(sf::IntRect(
                                           (frameNumber + 1) * w,
                                           etat * h,
                                           -w, h));
                window.draw(rabidja);
            }
            else
            {
                rabidja.setTextureRect(sf::IntRect(
                                           frameNumber * w,
                                           etat * h,
                                           w, h));
                window.draw(rabidja);
            }
        }
    }
    else
    {
        if (direction == LEFT)
        {
            rabidja.setTextureRect(sf::IntRect(
                                       (frameNumber + 1) * w,
                                       etat * h,
                                       -w, h));
            window.draw(rabidja);
        }
        else
        {
            rabidja.setTextureRect(sf::IntRect(
                                       frameNumber * w,
                                       etat * h,
                                       w, h));
            window.draw(rabidja);
        }
    }

}

void Player::centerScrolling(Map &map)
{
    int cxperso = x + w / 2;
    int cyperso = y + h / 2;
    int xlimmin = map.getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = map.getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    if (cxperso < map.getStartX())
    {
        map.setStartX(map.getStartX() - 30);
    }
    else if (cxperso < xlimmin)
    {
        map.setStartX(map.getStartX() - 4);
    }
    if (cxperso > map.getStartX() + SCREEN_WIDTH)
    {
        map.setStartX(map.getStartX() + 30);
    }
    else if (cxperso > xlimmax)
    {
        map.setStartX(map.getStartX() + 4);
    }

    if (map.getStartX() < 0)
    {
        map.setStartX(0);
    }

    else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
    {
        map.setStartX(map.getMaxX() - SCREEN_WIDTH);
    }

    if (cyperso < ylimmin)
    {
        map.setStartY(map.getStartY() - 4);
    }

    if (cyperso > ylimmax)
    {
        if (dirY >= MAX_FALL_SPEED - 2)
        {
            map.setStartY(map.getStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            map.setStartY(map.getStartY() + 4);
        }
    }

    if (map.getStartY() < 0)
    {
        map.setStartY(0);
    }

    else if (map.getStartY() + SCREEN_HEIGHT >= map.getMaxY())
    {
        map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
    }

}

void Player::mapCollision(Map &map)
{

    int i, x1, x2, y1, y2;
    onGround = 0;

    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;

    for (;;)
    {
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirX > 0)
            {
                if (map.getTile(y1, x2) > BLANK_TILE || map.getTile(y2, x2) > BLANK_TILE)
                {

                    x = x2 * TILE_SIZE;
                    x -= w + 1;
                    dirX = 0;
                }
            }

            else if (dirX < 0)
            {
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y2, x1) > BLANK_TILE)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }

        }
        if (i == h)
        {
            break;
        }
        i += TILE_SIZE;

        if (i > h)
        {
            i = h;
        }
    }
    if (w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = w;


    for (;;)
    {
        x1 = (x) / TILE_SIZE;
        x2 = (x + i) / TILE_SIZE;

        y1 = (y + dirY) / TILE_SIZE;
        y2 = (y + dirY + h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirY > 0)
            {
                if (map.getTile(y2, x1) > TILE_TRAVERSABLE || map.getTile(y2, x2) > TILE_TRAVERSABLE)
                {
                    y = y2 * TILE_SIZE;
                    y -= h;
                    dirY = 0;
                    onGround = 1;
                }
            }

            else if (dirY < 0)
            {
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y1, x2) > BLANK_TILE)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }
        if (i == w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > w)
        {
            i = w;
        }
    }

    x += dirX;
    y += dirY;

    if (x < 0)
    {
        x = 0;
    }

    else if (x + w >= map.getMaxX())
    {
        map.setLevel(map.getLevel() + 1);
        if (map.getLevel() > LEVEL_MAX)
        {
            map.setLevel(LEVEL_MAX);
            x = map.getMaxX() - w - 1;
        }
        else
        {
            checkpointActif = 0;

            map.changeLevel();
            initialize(map, true);
        }
    }
    if (y > map.getMaxY())
    {
        timerMort = 60;
    }
}

void Player::update(Input &input, Map &map)
{
    if (timerMort == 0)
    {
        if (invincibleTimer > 0)
            invincibleTimer--;
        dirX = 0;
        dirY += GRAVITY_SPEED;

        if (dirY >= MAX_FALL_SPEED)
            dirY = MAX_FALL_SPEED;

        if (input.getButton().left == true)
        {
            dirX -= PLAYER_SPEED;
            direction = LEFT;
            if (etat != WALK && onGround == true)
            {
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

        else if (input.getButton().right == true)
        {
            dirX += PLAYER_SPEED;
            direction = RIGHT;
            if (etat != WALK && onGround == true)
            {
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }
        else if (input.getButton().right == false && input.getButton().left == false && onGround == true)
        {
            if (etat != IDLE)
            {
                etat = IDLE;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }
        if (input.getButton().jump == true)
        {
            if (onGround == true)
            {
                dirY = -JUMP_HEIGHT;
                onGround = false;
                Playerjump = true;
            }
            else if (Playerjump == true)
            {
                dirY = -JUMP_HEIGHT;
                Playerjump = false;
            }
            input.setButton(jump, false);
        }
        if (onGround == true)
            Playerjump = true;
        if (onGround == false)
        {
            if (Playerjump == true)
            {
                if (etat != JUMP1)
                {
                    etat = JUMP1;
                    frameNumber = 0;
                    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                    frameMax = 2;
                }
            }
            else
            {
                if (etat != JUMP2)
                {
                    etat = JUMP2;
                    frameNumber = 0;
                    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                    frameMax = 4;
                }
            }
        }
        mapCollision(map);
        centerScrolling(map);

    }
    if (timerMort > 0)
    {
        timerMort--;

        if (timerMort == 0)
        {
            vies--;
            map.changeLevel();
            initialize(map, false);
        }
    }
}
