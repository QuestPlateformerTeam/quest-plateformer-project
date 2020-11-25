#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Map
{
    public:
        Map();
        virtual ~Map();
        void drawBackground(sf::RenderWindow& window);
        int getBeginX(void) const;
        int getBeginY(void) const;
        int getStartX(void) const;
        int getStartY(void) const;
        int getMaxX(void) const;
        int getMaxY(void) const;

    protected:

    private:
        sf::Texture backgroundTexture;
        sf::Sprite background;

        // Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau
        int beginx, beginy;

        // Coordonn�es de d�but, lorsqu'on doit dessiner la map
        int startX, startY;

        // Coordonn�es max de fin de la map
        int maxX, maxY;

        // Taille de la fen�tre : 800x480 pixels
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 480;
};

#endif // MAP_H
