#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Map
{
    public:
        //Constructeur
        Map();
        //Fonctions
        void drawBackground(sf::RenderWindow &window);

    private:
    //Variables de la classe en accès privé
    //Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

};


#endif // MAP_H_INCLUDED
