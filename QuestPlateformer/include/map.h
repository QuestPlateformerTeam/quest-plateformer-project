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

        // Coordonnées de départ du héros, lorsqu'il commence le niveau
        int beginx, beginy;

        // Coordonnées de début, lorsqu'on doit dessiner la map
        int startX, startY;

        // Coordonnées max de fin de la map
        int maxX, maxY;

        // Taille de la fenêtre : 800x480 pixels
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 480;
};

#endif // MAP_H
