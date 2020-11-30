#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
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
        int GetPressedItem(){ return selectedItemIndex;};
        float getWidth();
        float getHeight();
        void update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window);

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
};

#endif // MENU_H
