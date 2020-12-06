#include "hud.h"

HudLayer::HudLayer()
{
    if(!font.loadFromFile("ressources/police/arial.ttf"))
        std::cout<<"Erreur chargement font HUD"<<std::endl;

    lifeDisplayed.setFont(font);
    lifeDisplayed.setFillColor(sf::Color::White);
    lifeDisplayed.setPosition(sf::Vector2f(20,10));
    lifeDisplayed.setCharacterSize(25);

    timeDisplayed.setFont(font);
    timeDisplayed.setFillColor(sf::Color::White);
    timeDisplayed.setPosition(sf::Vector2f(650,10));
    timeDisplayed.setCharacterSize(25);

}

HudLayer::~HudLayer(){}//Destructeur

void HudLayer::restartChrono(){clock.restart();}//Permet de restart le chrono pour chaque game

void HudLayer::draw(sf::RenderWindow& window, Map map , Player& player) //Dessine mon affichage tete haute au dessus de ma map pour obtenir les informations joueurs
{
    fullStringLife = "Life: " + std::to_string(player.getLife()) +"  Level: "+std::to_string(map.getLevel());
    fullStringTime = "Timer: "+std::to_string((int)clock.getElapsedTime().asSeconds())+"s";

    lifeDisplayed.setString(fullStringLife);
    timeDisplayed.setString(fullStringTime);
    window.draw(lifeDisplayed);
    window.draw(timeDisplayed);
}
