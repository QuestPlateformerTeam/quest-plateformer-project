#include "Map.h"

Map::Map()
{
    // on cr�e la tilemap avec le niveau pr�c�demment d�fini
    if (!load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn()))
        std::cout<<"Erreur lors du chargement du tilset"<<std::endl; //Message d'erreur en console au cas ou
}

Map::~Map(){}

/*
    =================
    Getters & Setters
    =================
*/

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
int Map::getLevel(){return this->level;}
void Map::setLevel(int newLevel){this->level = newLevel;}


void Map::changeToNextLevel(bool& flagEndGame, bool& flagInGame) //Fonction pour aller au niveau suivant
{
    setLevel(getLevel()+1); //J'incr�mente ma variable level pour aller au suivant
    if(this->level<=2) //Si inf�rieur � 2 pour limiter les niveaux
    {
        levelToLoad = "ressources/maps/map"+std::to_string(this->level)+".txt"; //Je pr�pare mon string pour le niveau
        load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn()); //Je charge le nouveau fichier map
    }
    else //Sinon
    {
        flagEndGame = true; //Je ne suis en fin de game car j'ai fini les niveaux
        flagInGame = false; // Je m'assure de ne plus �tre en jeu
        resetGame(); //Je reset la partie pour �tre certain de bien red�marrer
    }
}

void Map::resetGame() //Ma fonction de reset permet de recharger le jeu depuis le d�but
{
    setLevel(1);
    levelToLoad = "ressources/maps/map"+std::to_string(this->level)+".txt";
    load(sf::Vector2u(getTileSize(), getTileSize()), getNbTileByLine(), getNbTileByColumn());
}

//Cette fonction charge la map graphique sur la map de tuile vide
bool Map::load(sf::Vector2u tileSize, unsigned int width, unsigned int height)
{

    backgroundTexture.loadFromFile("ressources/graphics/background.png"); //Je charge mon fond de fen�tre
    backgroundSprite.setScale(1.8,1.8); //Je r�gle l'echelle de mon fond
    backgroundSprite.setTexture(backgroundTexture); //Je set la texture dans mon sprite

    std::fstream myFile(this->levelToLoad, std::ios_base::in); //Je pr�pare le fichier map � lire
    std::string Line; //Je cr�e un string qui va r�cup�rer les caract�res entre chaque delimiter

    if(myFile.is_open())//Si mon fichier est ouvert
    {
        for (int i = 0; i < NB_TILE ; i++) //R�cup�re les valeurs pour chaque tuile soit 400 dans notre jeu
        {
            getline(myFile,Line,','); //R�cup�re les valeurs une par une s�par�e par le d�limiteur ','
            std::stringstream iss;
            iss << Line; //Stocke les caract�res dans un stream
            iss >> tiles[i]; //Renvoie le stream en un int dans l'array
        }
        myFile.close(); //Je ferme mes ressources
    }
    else
        std::cout<<"Erreur chargement map"<<std::endl; //En cas d'erreur, un message console pour en �tre inform�

    // on charge la texture du tileset
    if (!m_tileset.loadFromFile("ressources/graphics/tileset3.png"))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on r�cup�re le num�ro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en d�duit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on r�cup�re un pointeur vers le quad � d�finir dans le tableau de vertex
            quad = &m_vertices[(i + j * width) * 4];

            // on d�finit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on d�finit ses quatre coordonn�es de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const //M�thode h�rit�e directement de Drawable
{
        // on applique la transformation
        states.transform *= getTransform();
        // on applique la texture du tileset
        states.texture = &m_tileset;
        // et on dessine enfin le tableau de vertex
        target.draw(backgroundSprite);
        target.draw(m_vertices, states);
}

int Map::getTileNumber(int x, int y, int PLAYER_WIDTH, int PLAYER_HEIGHT) //Fonction qui me permet de savoir sur quelle tuile je suis en fonction de la position de mon player
{
    return ((((int)(x+PLAYER_WIDTH/2)/TILE_SIZE))) + (((int)(y+PLAYER_HEIGHT/2)/TILE_SIZE)*NB_TILE_BY_LINE);
}




