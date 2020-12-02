#ifndef HUDLAYER_H
#define HUDLAYER_H
#include <iostream>
#include <string>
#include "map.h"
#include "player.h"
#include <SFML/Graphics.hpp>

class HudLayer
{
    public:
        HudLayer();
        virtual ~HudLayer();
        void draw(sf::RenderWindow& window, Map map, Player& player);

    protected:

    private:
    sf::Font font;
    sf::Text lifeDisplayed;
    std::string fullString;
};

#endif // HUDLAYER_H
