#include "fireball.h"

Fireball::Fireball()
{
    fireball.setSize(sf::Vector2f(10, 10));
    fireball.setFillColor(sf::Color::Green);
    std::srand(time(NULL));
    int random = rand() %480;
    this->positionX= 790;
    this->positionY= 430;
    fireball.setPosition(positionX, positionY);
}

Fireball::~Fireball()
{
    //dtor
}

void Fireball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        target.draw(fireball, states);
}
