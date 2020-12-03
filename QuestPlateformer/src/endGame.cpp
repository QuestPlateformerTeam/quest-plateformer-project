#include "endGame.h"

EndGame::EndGame()
{
    if(!font.loadFromFile("ressources/police/arial.ttf"))
        std::cout<<"Erreur chargement font HUD"<<std::endl;

    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setString("END GAME");
    text.setPosition(sf::Vector2f(350,210));
}

EndGame::~EndGame()
{

}

void EndGame::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
