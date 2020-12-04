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
        void restartChrono();
        sf::Text getChrono(){return timeDisplayed;};

    protected:

    private:
    sf::Font font;
    sf::Text lifeDisplayed;
    sf::Text timeDisplayed;
    std::string fullStringLife;
    std::string fullStringTime;
    sf::Clock clock;
};

#endif // HUDLAYER_H
