#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define MAX_NUMBER_OF_ITEMS 3
#include "SFML/Graphics.hpp"

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

    protected:

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Font fontTitle;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        float width;
        float height;
};

#endif // MENU_H


