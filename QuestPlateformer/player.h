#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

class Map;
class Input;


class Player
{

public:

    //Constructeur
    Player();

    //Accesseurs
    int getX(void) const;
    int getY(void) const;
    int getW(void) const;
    int getH(void) const;
    float getDirX(void) const;
    float getDirY(void) const;
    int getOnGround(void) const;
    int getLife(void) const;
    int getVies(void) const;
    int getEtoiles(void) const;
    int getDirection(void) const;

    //Mutateurs
    void setX(int valeur);
    void setY(int valeur);
    void setW(int valeur);
    void setH(int valeur);
    void setDirX(float valeur);
    void setDirY(float valeur);
    void setOnGround(bool valeur);
    void setTimerMort(int valeur);
    void setVies(int valeur);
    void setEtoiles(int valeur);
    void setCheckpoint(bool valeur);

    //Fonctions
    void initialize(Map &map, bool newLevel);
    void draw(Map &map, sf::RenderWindow &window);
    void update(Input &input, Map &map);
    void centerScrolling(Map &map);
    void mapCollision(Map &map);


private:

    //Variables de la classe en acc�s priv�
    sf::Text nbVieScreen;
    sf::Font font;
// Points de vie/sant� + chrono d'invicibilit�
    int life, invincibleTimer;

//Vies et �toiles (100 �toiles = 1 vie)
    int vies, etoiles;

// Coordonn�es du sprite
    int x, y;

// Largeur, hauteur du sprite
    int h, w;

// Checkpoint pour le h�ros (actif ou non)
    bool checkpointActif;
// + coordonn�es de respawn (r�apparition)
    int respawnX, respawnY;

// Variables utiles pour l'animation :
// Num�ro de la frame (= image) en cours + timer
    int frameNumber, frameTimer, frameMax;
// Nombre max de frames, �tat du sprite et direction
// dans laquelle il se d�place (gauche / droite)
    int etat, direction;

// Variables utiles pour la gestion des collisions :
//Est-il sur le sol, chrono une fois mort
    int timerMort;
    bool onGround;

//Vecteurs de d�placement temporaires avant d�tection
//des collisions avec la map
    float dirX, dirY;
//Sauvegarde des coordonn�es de d�part
    int saveX, saveY;

//Variable pour le double saut
    bool Playerjump;

//Gestion des pentes par Stephantasy
    float dirXmem, dirYmem;
    int posXmem, posYmem;
    int wasOnGround;
    int wasOnSlope;

//Spritesheet de Rabidja
    sf::Texture rabidjaTexture;
    sf::Sprite rabidja;



    /******************/
    /* Constantes */
    /******************/


//Nombre max de levels
    const int LEVEL_MAX = 2;

    /* Taille maxi de la map : 400 x 150 tiles */
    const int MAX_MAP_X = 400;
    const int MAX_MAP_Y = 150;

    /* Taille d'une tile (32 x 32 pixels) */
    const int TILE_SIZE = 32;

    /* Constante pour l'animation */
    const int TIME_BETWEEN_2_FRAMES_PLAYER = 4;

    /* Taille du sprite de notre h�ros (largeur = width et hauteur = heigth) */
    const int PLAYER_WIDTH = 40;
    const int PLAYER_HEIGTH = 50;

//Vitesse de d�placement en pixels du sprite
    const int PLAYER_SPEED = 4;

//Valeurs attribu�es aux �tats/directions
    const int IDLE = 0;
    const int WALK = 1;
    const int JUMP1 = 2;
    const int JUMP2 = 3;
    const int DEAD = 4;

    const int RIGHT = 1;
    const int LEFT = 2;

//Constantes d�finissant la gravit� et la vitesse max de chute
    const double GRAVITY_SPEED = 0.6;
    const int MAX_FALL_SPEED = 15;
    const int JUMP_HEIGHT = 10;

// Taille de la fen�tre : 800x480 pixels
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 480;

//Constantes pour les limites de la cam�ra avant scrolling
    const int LIMITE_X = 400;
    const int LIMITE_Y = 220;
    const int LIMITE_W = 100;
    const int LIMITE_H = 80;

//Enum pour les boutons
    enum { up, down, right, left, attack, jump, enter };



    /*************************/
    /* VALEURS DES TILES */
    /************************/

// Constante d�finissant le seuil entre les tiles traversables
// (blank) et les tiles solides
    const int BLANK_TILE = 99;

//Plateformes traversables
    const int TILE_TRAVERSABLE = 80;

//Tiles Power-ups
    const int TILE_POWER_UP_DEBUT = 77;
    const int TILE_POWER_UP_FIN = 79;
    const int TILE_POWER_UP_COEUR = 78;

//Autres Tiles sp�ciales
    const int TILE_RESSORT = 125;
    const int TILE_CHECKPOINT = 23;
    const int TILE_MONSTRE = 136;
    const int TILE_PIKES = 127;

//Tiles plateformes mobiles
    const int TILE_PLATEFORME_DEBUT = 130;
    const int TILE_PLATEFORME_FIN = 131;




};
#endif // PLAYER_H_INCLUDED
