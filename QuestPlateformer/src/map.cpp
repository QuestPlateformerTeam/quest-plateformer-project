#include "map.h"
#include <sstream>
#include <fstream>
#include <iostream>

Map::Map()
{
    // on crée la tilemap avec le niveau précédemment défini
    if (!load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn()))
        std::cout << "Erreur lors du chargement du tileset" << std::endl;
}

Map::~Map() {}

sf::Vertex* Map::getVertex() { return quad; }
sf::VertexArray Map::getVertices() { return m_vertices; }
int Map::getScreenWidth() const { return SCREEN_WIDTH; }
int Map::getScreenHeight() const { return SCREEN_HEIGHT; }
int Map::getTileSize() const { return TILE_SIZE; }
int Map::getNbTileByLine() const { return NB_TILE_BY_LINE; }
int Map::getNbTileByColumn() const { return NB_TILE_BY_COLUMN; }
int* Map::getTiles() { return tiles; }
int Map::getStartX() { return startX; }
int Map::getStartY() { return startY; }
int Map::getLevel() { return this->level; }
void Map::setLevel(int newLevel) { this->level = newLevel; }

void Map::changeToNextLevel(bool& flagEndGame, bool& flagInGame)
{
    setLevel(getLevel() + 1);

    if (this->level <= 2)
    {
        levelToLoad = "../ressources/maps/map" + std::to_string(this->level) + ".txt";
        load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn());
    }
    else
    {
        flagEndGame = true;
        flagInGame = false;
        resetGame();
    }
}

void Map::resetGame()
{
    setLevel(1);
    levelToLoad = "../ressources/maps/map" + std::to_string(this->level) + ".txt";
    load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn());
}

bool Map::load(sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    backgroundTexture.loadFromFile("../ressources/graphics/background.png");
    backgroundSprite.setScale(1.8, 1.8);
    backgroundSprite.setTexture(backgroundTexture);

    std::fstream myFile(this->levelToLoad, std::ios_base::in);
    std::string Line;

    if (myFile.is_open())
    {
        for (int i = 0; i < NB_TILE; i++)
        {
            getline(myFile, Line, ',');
            std::stringstream iss;
            iss << Line;
            iss >> tiles[i];
        }
        myFile.close();
    }
    else
        std::cout << "Erreur chargement map" << std::endl;

    if (!m_tileset.loadFromFile("../ressources/graphics/tileset3.png"))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(backgroundSprite);
    target.draw(m_vertices, states);
}

int Map::getTileNumber(int x, int y, int PLAYER_WIDTH, int PLAYER_HEIGHT)
{
    return ((x + PLAYER_WIDTH / 2) / TILE_SIZE) + (((y + PLAYER_HEIGHT / 2) / TILE_SIZE) * NB_TILE_BY_LINE);
}
