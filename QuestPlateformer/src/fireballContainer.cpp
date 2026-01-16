#include "fireballContainer.h"

FireballContainer::FireballContainer() //Je cr�e un container qui stocke toutes mes boules de feu
{
    for(int i =0; i<=NB_FIREBALL; i++)
        fireballList.push_back(new Fireball()); //Je push une nouvelle boule de feu en fonctione de la difficult� demand�e
}

FireballContainer::~FireballContainer(){}//destructeur

void FireballContainer::draw(sf::RenderWindow& window) //Je dessine mes boules de feu
{
    for(int i =0; i<=NB_FIREBALL; i++)
        fireballList.at(i)->draw(window);
}

Fireball& FireballContainer::getOneFireball(int i) //Je r�cup�re une boule de feu depuis mon vecteur
{
    return *fireballList.at(i);
}

void FireballContainer::resetAll() //Je reset la position des boules de feu
{
    for(int i =0; i<=NB_FIREBALL; i++)
        fireballList.at(i)->reset();
}

int FireballContainer::getNbFireball() //Je r�cup�re le nombre de boule de feu max possible sur ma map
{
    return NB_FIREBALL;
}
