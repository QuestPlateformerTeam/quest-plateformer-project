#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define MAX_NUMBER_OF_ITEMS 3
#include "SFML/Graphics.hpp"

class Menu
{
    public:
        Menu(float width, float height);
        ~Menu();

        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int GetPressedItem(){ return selectedItemIndex;};
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

#endif // MENU_H_INCLUDED
