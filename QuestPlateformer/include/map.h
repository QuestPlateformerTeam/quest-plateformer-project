#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "coin.h"


class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map();
        virtual ~Map();
        bool load(sf::Vector2u tileSize, unsigned int width, unsigned int height);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vertex* getVertex();
        sf::VertexArray getVertices();
        int getTileNumber(int x, int y, int PLAYER_WIDTH, int PLAYER_HEIGHT);
        int getScreenWidth() const;
        int getScreenHeight() const;
        int getTileSize() const;
        int getNbTileByLine() const;
        int getNbTileByColumn() const;
        int getStartX();
        int getStartY();
        int* getTiles();
        void setMap(std::string filename);
        int getLevel();
        void setLevel(int newLevel);
        void changeToNextLevel(bool& flagEndGame);
        void resetGame();



    protected:

    private:
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 480;
        static const int TILE_SIZE = 32;
        static const int NB_TILE_BY_LINE = SCREEN_WIDTH/TILE_SIZE;
        static const int NB_TILE_BY_COLUMN = SCREEN_HEIGHT/TILE_SIZE;
        static const int NB_TILE = (NB_TILE_BY_LINE*NB_TILE_BY_COLUMN);
        int level = 1;
        std::string levelToLoad = "ressources/maps/map1.txt";

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        sf::Vertex* quad;
        sf::Text affichageVie;
        sf::Font font;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        int tileNumber;
        int tiles[NB_TILE];
        int startX = 20;
        int startY = 400;

        std::vector<Coin*> coinList;

};

#endif // MAP_H
