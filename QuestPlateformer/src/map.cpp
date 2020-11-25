#include "map.h"

Map::Map()
{

}

Map::~Map()
{

}

//Accesseurs
int Map::getBeginX(void) const
{
    return beginx;
}

int Map::getBeginY(void) const
{
    return beginy;
}

int Map::getStartX(void) const
{
    return startX;
}

int Map::getStartY(void) const
{
    return startY;
}

int Map::getMaxX(void) const
{
    return maxX;
}

int Map::getMaxY(void) const
{
    return maxY;
}

void Map::drawBackground(sf::RenderWindow& window)
{
    if (!backgroundTexture.loadFromFile("ressources/graphics/background.png"))
    {
        std::cout << "Erreur durant le chargement de l'image de background." << std::endl;
    }else
    {
        sf::Sprite background;
    }

    background.setTexture(backgroundTexture);

    window.draw(background);
}
