#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include "hud.h"
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3


class Menu
{
    public:
        Menu();
        Menu(float width, float height);
        virtual ~Menu();
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        void update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window, HudLayer& hud);

    protected:

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Font fontTitle;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text title;
        sf::RectangleShape rectangle;
        float width;
        float height;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
};

#endif // MENU_H
