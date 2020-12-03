#include "fireballContainer.h"
FireballContainer::FireballContainer()
{
    for(int i =0; i<=NB_FIREBALL; i++)
    {
        fireballList.push_back(new Fireball());
    }
}

FireballContainer::~FireballContainer()
{
    //dtor
}

void FireballContainer::draw(sf::RenderWindow& window)
{
    for(int i =0; i<=NB_FIREBALL; i++)
    {
        fireballList.at(i)->draw(window);
    }
}

Fireball& FireballContainer::getOneFireball(int i)
{
    return *fireballList.at(i);
}

void FireballContainer::resetAll()
{
    for(int i =0; i<=NB_FIREBALL; i++)
    {
        fireballList.at(i)->reset();
    }
}

int FireballContainer::getNbFireball()
{
    return NB_FIREBALL;
}
