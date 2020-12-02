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
        Player(const Player& player) { /* copy construction from rhs*/ }
        Player& operator=(const Player& player);
        void draw(sf::RenderWindow& window, Map map);
        void update(Map& map, bool& flagInGame, const int* level);
        void deplacement(bool& flagInGame, Map& map,const int* level);
        void wallDetection(Map& map, const int* level);
        void stepOn(Map& map, const int* level, const int itemToDetect);
        void setLife(int newLife);
        int getLife();
        void setPlayerAtStart(Map map);
        void isDead(Map& map);

    protected:

    private:
        int positionX;
        int positionY;
        int life = 3;
        bool flagGameOver = false;

        //Permet de savoir si le personnage peut sauter
        bool canJump = false;

        //Pour le déplacement dans le jeu
        float velocityY = 10;

        //boolean pour vérifier si il y a collision
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
        int timee = 0;

        //Constantes
        const int MOVESPEED = 3;
        const int MAX_HEIGHT_JUMP = 80;
        const int PLAYER_HEIGHT = 50;
        const int PLAYER_WIDTH = 40;
        const int WALL_TILE = 126;
        const int TILE_LEFT = 123;
        const int TILE_RIGHT = 122;
        const int TILE_HEIGHT = 113;
        const int EXIT_TILE = 126;

};

#endif // PLAYER_H
