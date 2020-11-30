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
        void update(Map map, bool& flagInGame, const int* level);
        void deplacement(bool& flagInGame);
        void wallDetection(Map map, const int* level);

    protected:

    private:
        int positionX;
        int positionY;
        bool canJump = false;
        float velocityY = 10;
        bool lockUp;
        bool lockDown;
        bool lockLeft;
        bool lockRight;
        int counterWalking = 0;
        bool hasJump =false;
        bool isTopOfJump = true;
        int fromHeight;

        //Spritesheet de Rabidja
        sf::Texture texture;
        sf::Sprite sprite;

        const int MOVESPEED = 3;
        const int MAX_HEIGHT_JUMP = 80;
        const int PLAYER_HEIGHT = 50;
        const int PLAYER_WIDTH = 40;

};

#endif // PLAYER_H
