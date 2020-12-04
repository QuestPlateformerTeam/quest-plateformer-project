#include "fireball.h"

Fireball::Fireball()
{
    if(!texture.loadFromFile("ressources/graphics/flame.png")) //Je charge la texture de ma boule de feu
        std::cout<<"Erreur chargement flamme"<<std::endl; //Message d'erreur en cas de problème
    fireball.setTexture(texture); // Je set la texture de ma boule de feu
    fireball.setScale(1.5,1.5); //J'adapte son echelle
    reset(); //J'utilise ma fonction reset pour lui attribuer une position random et la renvoyer au départ
    fireball.setPosition(positionX, positionY);
}

Fireball::~Fireball(){}

/*
    =================
    Getters & Setters
    =================
*/
void Fireball::setPositionY(int newY){this->positionY = newY;}
sf::Sprite Fireball::getSprite(){return fireball;}


void Fireball::draw(sf::RenderWindow& window) //Je draw ma boule de feu
{
    if(this->positionX<=-10) //Si elle atteint le bord
        reset();//Je reset ma boule de feu à une nouvelle position

    this->positionX = this->positionX - MOVESPEED; //Je fais avancer ma boule de feu
    fireball.setPosition(positionX,positionY); //J'actualise sa position
    window.draw(fireball); //Je dessine ma boule de feu à sa position actualisée
}

void Fireball::reset()
{
    struct timespec ts; //Structure pour utiliser timespec
    clock_gettime(CLOCK_MONOTONIC, &ts); //Je crée un see en utilisant sur ts
    srand((time_t)ts.tv_nsec); //Je crée un random avec un seed et calculer en nano second pour avoir un random hétérogène

    this->positionX= 800 + rand()%(1000-50 + 1) + 50; ; //Calcul du random sur l'axe des X pour permettre un spawn en différé sans utiliser le temps
    this->positionY= rand()%(430-0 + 1) + 0; // Calcul d'un random sur l'axe des Y
}
