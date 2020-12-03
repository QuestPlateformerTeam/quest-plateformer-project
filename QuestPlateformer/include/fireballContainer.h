#ifndef FIREBALLCONTAINER_H
#define FIREBALLCONTAINER_H
#include <iostream>
#include <vector>
#include "fireball.h"
#include <SFML/Graphics.hpp>

using namespace std;


class FireballContainer
{
    public:
        FireballContainer();
        virtual ~FireballContainer();
        void draw(sf::RenderWindow& window);
        Fireball& getOneFireball(int i);
        void resetAll();
        int getNbFireball();

    protected:

    private:
        vector<Fireball*> fireballList;
        sf::Clock clock; // démarre le chrono
        const int NB_FIREBALL = 5;
};

#endif // FIREBALLCONTAINER_H
