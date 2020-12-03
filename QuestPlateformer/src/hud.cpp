#include "hud.h"


HudLayer::HudLayer()
{
    if(!font.loadFromFile("ressources/police/arial.ttf"))
        std::cout<<"Erreur chargement font HUD"<<std::endl;

    lifeDisplayed.setFont(font);
    lifeDisplayed.setColor(sf::Color::White);
    lifeDisplayed.setPosition(sf::Vector2f(20,10));
    lifeDisplayed.setCharacterSize(25);

    timeDisplayed.setFont(font);
    timeDisplayed.setColor(sf::Color::White);
    timeDisplayed.setPosition(sf::Vector2f(650,10));
    timeDisplayed.setCharacterSize(25);
}

HudLayer::~HudLayer()
{
    //dtor
}

void HudLayer::draw(sf::RenderWindow& window, Map map , Player& player)
{
    fullStringLife = "Life: " + std::to_string(player.getLife()) +"  Level: "+std::to_string(map.getLevel());
    fullStringTime = "Timer: "+std::to_string((int)clock.getElapsedTime().asSeconds())+"s";

    lifeDisplayed.setString(fullStringLife);
    timeDisplayed.setString(fullStringTime);
    window.draw(lifeDisplayed);
    window.draw(timeDisplayed);
}
