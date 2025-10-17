#include "endGame.h"
#include <iostream>

EndGame::EndGame(float width, float height)
{
    this->width = width;  // largeur de la fenêtre
    this->height = height; // hauteur de la fenêtre

    if (!font.loadFromFile("../ressources/police/arial.ttf"))
        std::cout << "Impossible de charger la police d'ecriture" << std::endl;

    // Préparation des textes du menu
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play again");

    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Back to menu");

    selectedItemIndex = 0; // item actuellement sélectionné

    title.setString("END GAME");
    title.setFillColor(sf::Color::White);
    title.setFont(font);
    title.setCharacterSize(60);
    title.setPosition((this->width / 2) - (title.getGlobalBounds().width / 2), 10);

    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);
}

EndGame::~EndGame() {}

void EndGame::draw(sf::RenderWindow& window, sf::Text chrono)
{
    window.draw(title);

    chrono.setPosition(sf::Vector2f(this->width / 2 - 60, 100));
    chrono.setFont(font);
    chrono.setFillColor(sf::Color::White);
    chrono.setCharacterSize(30);
    window.draw(chrono);

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS_ENDGAME; i++) {
        float calculatedWidthRect = (this->width / 2) - 150;
        float calculatedWidthText = (this->width / 2) - (menu[i].getGlobalBounds().width / 2);
        float calculatedHeight = this->height / (MAX_NUMBER_OF_ITEMS_ENDGAME + 1) * (i + 1);

        rectangle.setPosition(calculatedWidthRect, calculatedHeight - 5);
        menu[i].setPosition(sf::Vector2f(calculatedWidthText, calculatedHeight));
        menu[i].setFont(font);

        window.draw(rectangle);
        window.draw(menu[i]);
    }
}

void EndGame::update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window, bool& flagEndGame)
{
    if (!flagInGame) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            MoveUp();
            break;
        case sf::Keyboard::Down:
            MoveDown();
            break;
        case sf::Keyboard::Return:
            switch (selectedItemIndex) {
            case 0: // relancer le jeu
                std::cout << "Play button has been pressed" << std::endl;
                flagInGame = true;
                flagEndGame = false;
                break;
            case 1: // retour au menu
                flagInGame = false;
                flagEndGame = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void EndGame::MoveUp()
{
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void EndGame::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS_ENDGAME) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
