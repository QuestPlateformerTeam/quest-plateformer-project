#include "fireball.h"

Fireball::Fireball()
{
    if(!texture.loadFromFile("ressources/graphics/flame.png"))
        std::cout<<"Erreur chargement flamme"<<std::endl;
    fireball.setTexture(texture);
    fireball.setScale(1.5,1.5);

    reset();
    fireball.setPosition(positionX, positionY);
}

Fireball::~Fireball()
{
}

void Fireball::draw(sf::RenderWindow& window)
{
    if(this->positionX<=-10)
        reset();

    this->positionX = this->positionX - MOVESPEED;
    fireball.setPosition(positionX,positionY);
    window.draw(fireball);
}

void Fireball::setPositionY(int newY)
{
    this->positionY = newY;
}


sf::FloatRect Fireball::getGlobalForIntersect()
{
    return fireball.getGlobalBounds();
}

void Fireball::reset()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);
    this->positionX= 800 + rand()%(1000-50 + 1) + 50; ;
    this->positionY= rand()%(430-0 + 1) + 0;
}
