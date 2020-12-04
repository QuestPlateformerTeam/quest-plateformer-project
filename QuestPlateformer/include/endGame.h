#ifndef ENDGAME_H
#define ENDGAME_H
#define MAX_NUMBER_OF_ITEMS 2
#include <SFML/Graphics.hpp>
#include <iostream>

class EndGame
{
    public:
        EndGame(float width, float height);
        virtual ~EndGame();
        void draw(sf::RenderWindow& window, sf::Text chrono);
        void MoveUp();
        void MoveDown();
        void update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window,bool& flagEndGame);

    protected:

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text title;
        sf::RectangleShape rectangle;
        float width;
        float height;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

};

#endif // ENDGAME_H
