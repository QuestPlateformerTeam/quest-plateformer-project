#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"
#include "fireball.h"
#include "fireballContainer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "coinContainer.h"
#include "Collision.h"

class Player
{
    public:
        Player();
        Player(int x, int y);
        virtual ~Player();
        Player(const Player& player) { /* copy construction from rhs*/ }
        Player& operator=(const Player& player);
        void draw(sf::RenderWindow& window, Map map);
        void update(Map& map, bool& flagInGame, const int* level, FireballContainer& fireballContainer, CoinContainer& coinContainer);
        void deplacement(bool& flagInGame, Map& map,const int* level);
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
        int WALL_TILE = 90;
        /*int TILE_LEFT = 123;
        int TILE_RIGHT = 122;
        int TILE_HEIGHT = 113;*/
        int TILE_KILL = 188;

        //Spritesheet de Rabidja
        sf::Texture texture;
        sf::Sprite sprite;
        int timee = 0;

        //Constantes
        const int MOVESPEED = 3;
        const int MAX_HEIGHT_JUMP = 80;
        const int PLAYER_HEIGHT = 50;
        const int PLAYER_WIDTH = 40;

        const int EXIT_TILE = 186;



};

#endif // PLAYER_H
