#include "Map.h"

Map::Map()
{
    // on crée la tilemap avec le niveau précédemment défini
    if (!load("ressources/graphics/tileset1.png", sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn()))
        std::cout<<"Erreur lors du chargement du tilset"<<std::endl;
}

Map::~Map()
{
    //dtor
}

//Getters & Setters
sf::Vertex* Map::getVertex(){return quad;}
sf::VertexArray Map::getVertices(){return m_vertices;}
int Map::getScreenWidth() const{return SCREEN_WIDTH;}
int Map::getScreenHeight() const{return SCREEN_HEIGHT;}
int Map::getTileSize() const{return TILE_SIZE;}
int Map::getNbTileByLine() const{return NB_TILE_BY_LINE;}
int Map::getNbTileByColumn() const{return NB_TILE_BY_COLUMN;}
int* Map::getTiles(){return tiles;}
int Map::getStartX(){return startX;}
int Map::getStartY(){return startY;}
int Map::getTileNumber(int x, int y, int PLAYER_WIDTH, int PLAYER_HEIGHT)
{
    return ((((int)(x+PLAYER_WIDTH/2)/TILE_SIZE))) + (((int)(y+PLAYER_HEIGHT/2)/TILE_SIZE)*NB_TILE_BY_LINE);
}

//Ici je charge le niveau souhaité dans ma liste de map
void Map::setMap(std::string filename)
{
    std::fstream myFile(filename, std::ios_base::in);
    std::string Line;
    if(myFile.is_open())
    {
        std::cout<<"map chargee"<<std::endl;
        for (int i = 0; i < NB_TILE ; i++) //Récupère les valeurs pour chaque tuile
        {
            getline(myFile,Line,','); //Récupère les valeurs une par une séparée par le délimiteur ','
            std::stringstream iss;
            iss << Line; //Stocke les caractères dans un stream
            iss >> tiles[i]; //Renvoie le stream en un int dans l'array
        }
        myFile.close();
    }
    else
        std::cout<<"Erreur chargement map"<<std::endl;
}

//Cette fonction charge la map graphique sur la map de tuile vide
bool Map::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    //Je récupère la map sous forme de tuile vide de 32x32
    setMap("ressources/maps/map2.txt");

    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            quad = &m_vertices[(i + j * width) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();
    // on applique la texture du tileset
    states.texture = &m_tileset;
    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}


