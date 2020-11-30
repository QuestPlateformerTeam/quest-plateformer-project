#ifndef HOMEMENU_H
#define HOMEMENU_H
#define MAX_NUMBER_OF_ITEMS 3
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"


class HomeMenu
{
    public:
        HomeMenu();
        HomeMenu(float width, float height);
        virtual ~HomeMenu();
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int GetPressedItem(){ return selectedItemIndex;};
        float getWidth();
        float getHeight();

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

#endif // HOMEMENU_H
