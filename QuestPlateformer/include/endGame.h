#ifndef ENDGAME_H
#define ENDGAME_H
#include <SFML/Graphics.hpp>
#include <iostream>

class EndGame
{
    public:
        EndGame();
        virtual ~EndGame();
        void draw(sf::RenderWindow& window);

    protected:

    private:
        sf::Text text;
        sf::Font font;
};

#endif // ENDGAME_H
