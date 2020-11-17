#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Map
{
    public:

    //Constructeur
    Map();

    //Accesseurs
    int getBeginX(void) const;
    int getBeginY(void) const;
    int getStartX(void) const;
    int getStartY(void) const;
    int getMaxX(void) const;
    int getMaxY(void) const;
    int getTile(int y, int x) const;
    int getLevel(void) const;

    //Mutateurs
    void setLevel(int valeur);
    void setStartX(int valeur);
    void setStartY(int valeur);
    void setTile(int y, int x, int valeur);

    //Fonctions
    void drawBackground(sf::RenderWindow &window);
    void loadMap(std::string filename);
    void draw(int layer, sf::RenderWindow &window);
    void changeLevel(void);
    void testDefilement(void);


    private:
    //Variables de la classe en accès privé

    //Numéro du tileset à utiliser
    int tilesetAffiche;

    /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
    int beginx, beginy;

    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonnées max de fin de la map */
    int maxX, maxY;

    /* Tableau à double dimension représentant la map de tiles */
    int tile[150][400];

    //Deuxième couche de tiles
    int tile2[150][400];

    //Troisième couche de tiles
    int tile3[150][400];

    /* Timer et numéro du tileset à afficher pour animer la map */
    int mapTimer, tileSetNumber;

    //Numéro du niveau en cours
    int level;

    //Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    //Tilesets
    sf::Texture tileSet1Texture;
    sf::Sprite tileSet1;
    sf::Texture tileSet1BTexture;
    sf::Sprite tileSet1B;


    /*******************/
    /* Constantes */
    /******************/

    // Taille de la fenêtre : 800x480 pixels
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 480;

    /* Taille maxi de la map : 400 x 150 tiles */
    const int MAX_MAP_X = 400;
    const int MAX_MAP_Y = 150;

    /* Taille d'une tile (32 x 32 pixels) */
    const int TILE_SIZE = 32;

    /* Constante pour l'animation */
    const int TIME_BETWEEN_2_FRAMES = 20;


    /*************************/
    /* VALEURS DES TILES */
    /************************/

    // Constante définissant le seuil entre les tiles traversables
    // (blank) et les tiles solides
    const int BLANK_TILE = 99;

    //Plateformes traversables
    const int TILE_TRAVERSABLE = 80;

    //Tiles Power-ups
    const int TILE_POWER_UP_DEBUT = 77;
    const int TILE_POWER_UP_FIN = 79;
    const int TILE_POWER_UP_COEUR = 78;

    //Autres Tiles spéciales
    const int TILE_RESSORT = 125;
    const int TILE_CHECKPOINT = 23;
    const int TILE_MONSTRE = 136;
    const int TILE_PIKES = 127;

    //Tiles plateformes mobiles
    const int TILE_PLATEFORME_DEBUT = 130;
    const int TILE_PLATEFORME_FIN = 131;

    // Tiles pentes à 26.5° ; BenH = de BAS en HAUT ; HenB = De HAUT en BAS
    const int TILE_PENTE_26_BenH_1 = 69;
    const int TILE_PENTE_26_BenH_2 = 70;
    const int TILE_PENTE_26_HenB_1 = 71;
    const int TILE_PENTE_26_HenB_2 = 72;

};
#endif
