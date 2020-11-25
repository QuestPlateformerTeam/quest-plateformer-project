#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player
{
    public:
        Player();
        Player(int x, int y);
        virtual ~Player();
        void draw(sf::RenderWindow& window, Map map);
        void update(Map map, bool& flagInGame);
        int getPositionX();
        int getPositionY();
        void setPositionX(int x);
        void setPositionY(int y);

    protected:

    private:
        sf::RectangleShape rectangle;
        int positionX;
        int positionY;
        bool canJump = true;
        bool topJump = true;
        int currentHeightJump = 0;
        int distanceCalculated = 9;
        //Spritesheet de Rabidja
        sf::Texture texture;
        sf::Sprite sprite;

        const int MAX_HEIGHT_JUMP = 150;
        const int MOVESPEED = 5;
        const int PLAYER_HEIGHT = 25;
        const int PLAYER_WIDTH = 25;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 480;
};

#endif // PLAYER_H
