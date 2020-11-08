#include "player.h"
#include "map.h"
#include "input.h"

using namespace std;
using namespace sf;

//Constructeur

Player::Player()
{
//Chargement de la spritesheet de Rabidja
    if (!rabidjaTexture.loadFromFile("ressources/graphics/rabidja.png"))
    {
// Erreur
        cout << "Erreur durant le chargement du spritesheet de Rabidja." << endl;
    }
    else
        rabidja.setTexture(rabidjaTexture);

//Initialisation des variables :
    dirX = 0;
    dirY = 0;
    life = 3;
    invincibleTimer = 0;
    x = y = h = w = 0;
    checkpointActif = false;
    respawnX = respawnY = 0;
    frameNumber = frameTimer = frameMax = 0;
    etat = direction = 0;
    timerMort = 0;
    onGround = false;
    dirX = dirY = 0;
    saveX = saveY = 0;
    Playerjump = false;

}


//Accesseurs
int Player::getX(void) const
{
    return x;
}
int Player::getY(void) const
{
    return y;
}
int Player::getW(void) const
{
    return w;
}
int Player::getH(void) const
{
    return h;
}
float Player::getDirX(void) const
{
    return dirX;
}
float Player::getDirY(void) const
{
    return dirY;
}
int Player::getOnGround(void) const
{
    return onGround;
}
int Player::getLife(void) const
{
    return life;
}
int Player::getVies(void) const
{
    return vies;
}
int Player::getEtoiles(void) const
{
    return etoiles;
}
int Player::getDirection(void) const
{
    return direction;
}


//Mutateurs
void Player::setX(int valeur)
{
    x = valeur;
}
void Player::setY(int valeur)
{
    y = valeur;
}
void Player::setW(int valeur)
{
    w = valeur;
}
void Player::setH(int valeur)
{
    h = valeur;
}
void Player::setDirX(float valeur)
{
    dirX = valeur;
}
void Player::setDirY(float valeur)
{
    dirY = valeur;
}
void Player::setOnGround(bool valeur)
{
    onGround = valeur;
}
void Player::setTimerMort(int valeur)
{
    timerMort = valeur;
}
void Player::setVies(int valeur)
{
    vies = valeur;
}
void Player::setEtoiles(int valeur)
{
    etoiles = valeur;
}
void Player::setCheckpoint(bool valeur)
{
    checkpointActif = valeur;
}

void Player::initialize(Map &map, bool newLevel)
{
//PV � 3
    life = 3;

//Timer d'invincibilit� � 0
    invincibleTimer = 0;

//Indique l'�tat et la direction de notre h�ros
    direction = RIGHT;
    etat = IDLE;

//Indique le num�ro de la frame o� commencer
    frameNumber = 0;

//...la valeur de son chrono ou timer
    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//... et son nombre de frames max (8 pour l'anim' IDLE
// = ne fait rien)
    frameMax = 8;

    /* Coordonn�es de d�marrage/respawn de notre h�ros.
    Plus tard, quand on aura rajout� la gestion de nos
    checkpoints, le h�ros pourra y ressusciter directement
    sans recommencer le niveau. Mais pour l'instant, il restera
    � false, et on recommencera donc au d�but du niveau (beginX, beginY) */
    if (checkpointActif == true)
    {
        x = respawnX;
        y = respawnY;
    }
    else
    {
        x = map.getBeginX();
        y = map.getBeginY();
    }

    map.setStartX(0);
    map.setStartY(0);

    /* Hauteur et largeur de notre h�ros */
    w = PLAYER_WIDTH;
    h = PLAYER_HEIGTH;

//Variables n�cessaires au fonctionnement de la gestion des collisions
    timerMort = 0;
    onGround = false;
}

void Player::draw(Map &map, RenderWindow &window)
{
    /* Gestion du timer */
// Si notre timer (un compte � rebours en fait) arrive � z�ro
    if (frameTimer <= 0)
    {
//On le r�initialise
        frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//Et on incr�mente notre variable qui compte les frames de 1 pour passer � la suivante
        frameNumber++;

//Mais si on d�passe la frame max, il faut revenir � la premi�re :
        if (frameNumber >= frameMax)
            frameNumber = 0;
    }
//Sinon, on d�cr�mente notre timer
    else
        frameTimer--;


//Ensuite, on peut passer la main � notre fonction
    rabidja.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));

//Pour conna�tre le X de la bonne frame � dessiner, il suffit de multiplier
//la largeur du sprite par le num�ro de la frame � afficher -> 0 = 0; 1 = 40; 2 = 80...
//On calcule le Y de la bonne frame � dessiner, selon la valeur de l'�tat du h�ros :
//Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
//Tout cela en accord avec notre spritesheet, of course ;)

//Si on a �t� touch� et qu'on est invincible
    if (invincibleTimer > 0)
    {
//On fait clignoter le h�ros une frame sur deux
//Pour �a, on calcule si le num�ro de la frame en
//cours est un multiple de deux
        if (frameNumber % 2 == 0)
        {
//Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche)
            if (direction == LEFT)
            {
//On n'a plus de flip auto en SFML, il faut donc tout calculer
                rabidja.setTextureRect(sf::IntRect(
                                           (frameNumber + 1) * w,
                                           etat * h,
                                           -w, h));
                window.draw(rabidja);
            }
            else
            {
                rabidja.setTextureRect(sf::IntRect(
                                           frameNumber * w,
                                           etat * h,
                                           w, h));
                window.draw(rabidja);
            }
        }
//Sinon, on ne dessine rien, pour le faire clignoter
    }

//Sinon, on dessine normalement
    else
    {
//Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche)
        if (direction == LEFT)
        {
//On n'a plus de flip auto en SFML, il faut donc tout calculer
            rabidja.setTextureRect(sf::IntRect(
                                       (frameNumber + 1) * w,
                                       etat * h,
                                       -w, h));
            window.draw(rabidja);
        }
        else
        {
            rabidja.setTextureRect(sf::IntRect(
                                       frameNumber * w,
                                       etat * h,
                                       w, h));
            window.draw(rabidja);
        }
    }

}

void Player::centerScrolling(Map &map)
{
// Nouveau scrolling � sous-bo�te limite :
//Pour �viter les effets de saccades dus � une cam�ra qui se
//centre automatiquement et constamment sur le joueur (ce qui
//peut en rendre malade certains...), on cr�e une "bo�te" imaginaire
//autour du joueur. Quand on d�passe un de ses bords (en haut, en bas,
//� gauche ou � droite), on scrolle.
//Mais l� encore, au lieu de centrer sur le joueur, on d�place simplement
//la cam�ra jusqu'� arriver au joueur. On a chang� ici la valeur � 4 pixels
//pour que le jeu soit plus rapide.
    int cxperso = x + w / 2;
    int cyperso = y + h / 2;
    int xlimmin = map.getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = map.getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

//Effet de retour en arri�re quand on est mort :
//Si on est tr�s loin de la cam�ra, plus loin que le bord
//de la map, on acc�l�re le scrolling :
    if (cxperso < map.getStartX())
    {
        map.setStartX(map.getStartX() - 30);
    }

//Si on d�passe par la gauche, on recule la cam�ra
    else if (cxperso < xlimmin)
    {
        map.setStartX(map.getStartX() - 4);
    }

//Effet de retour en avant quand on est mort (au
//cas o� le joueur s'amuse � faire le niveau � rebours
//apr�s une checkpoint) :
//Si on est tr�s loin de la cam�ra, plus loin que le bord
//de la map, on acc�l�re le scrolling :
    if (cxperso > map.getStartX() + SCREEN_WIDTH)
    {
        map.setStartX(map.getStartX() + 30);
    }

//Si on d�passe par la droite, on avance la cam�ra
    else if (cxperso > xlimmax)
    {
        map.setStartX(map.getStartX() + 4);
    }

//Si on arrive au bout de la map � gauche, on stoppe le scrolling
    if (map.getStartX() < 0)
    {
        map.setStartX(0);
    }

//Si on arrive au bout de la map � droite, on stoppe le scrolling � la
//valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir).
    else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
    {
        map.setStartX(map.getMaxX() - SCREEN_WIDTH);
    }

//Si on d�passe par le haut, on remonte la cam�ra
    if (cyperso < ylimmin)
    {
        map.setStartY(map.getStartY() - 4);
    }

//Si on d�passe par le bas, on descend la cam�ra
    if (cyperso > ylimmax)
    {
//Sauf si on tombe tr�s vite, auquel cas, on acc�l�re la cam�ra :
        if (dirY >= MAX_FALL_SPEED - 2)
        {
            map.setStartY(map.getStartY() + MAX_FALL_SPEED + 1);
        }
        else
        {
            map.setStartY(map.getStartY() + 4);
        }
    }

//Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (map.getStartY() < 0)
    {
        map.setStartY(0);
    }

//Si on arrive au bout de la map en bas, on stoppe le scrolling � la
//valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir).
    else if (map.getStartY() + SCREEN_HEIGHT >= map.getMaxY())
    {
        map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
    }

}

void Player::mapCollision(Map &map)
{

    int i, x1, x2, y1, y2;

    /* D'abord, on consid�re le joueur en l'air jusqu'� temps
    d'�tre s�r qu'il touche le sol */
    onGround = 0;

    /* Ensuite, on va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va d�couper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
    teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas o� notre sprite serait inf�rieur � la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
    sera op�rationnel quelle que soit la taille de nos sprites ! */

    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;


//On lance alors une boucle for infinie car on l'interrompra selon
//les r�sultats de nos calculs
    for (;;)
    {
//On va calculer ici les coins de notre sprite � gauche et �
//droite pour voir quelle tile ils touchent.
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;

//M�me chose avec y, sauf qu'on va descendre au fur et � mesure
//pour tester toute la hauteur de notre sprite, gr�ce � notre
//fameuse variable i.
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;

//De l�, on va tester les mouvements initi�s dans updatePlayer
//gr�ce aux vecteurs dirX et dirY, tout en testant avant qu'on
//se situe bien dans les limites de l'�cran.
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
//Si on a un mouvement � droite
            if (dirX > 0)
            {
//On v�rifie si les tiles recouvertes sont solides
                if (map.getTile(y1, x2) > BLANK_TILE || map.getTile(y2, x2) > BLANK_TILE)
                {
// Si c'est le cas, on place le joueur aussi pr�s que possible
// de ces tiles, en mettant � jour ses coordonn�es. Enfin, on
//r�initialise son vecteur d�placement (dirX).

                    x = x2 * TILE_SIZE;
                    x -= w + 1;
                    dirX = 0;
                }
            }

//M�me chose � gauche
            else if (dirX < 0)
            {
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y2, x1) > BLANK_TILE)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }

        }

//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
        if (i == h)
        {
            break;
        }

//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
        i += TILE_SIZE;

        if (i > h)
        {
            i = h;
        }
    }


//On recommence la m�me chose avec le mouvement vertical (axe des Y)
    if (w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = w;


    for (;;)
    {
        x1 = (x) / TILE_SIZE;
        x2 = (x + i) / TILE_SIZE;

        y1 = (y + dirY) / TILE_SIZE;
        y2 = (y + dirY + h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirY > 0)
            {
// D�placement en bas
//Gestion des plateformes traversables : elles se situent juste avant
//les tiles bloquantes dans notre tileset (dont la valeur butoire est
//BLANK_TILE). Il suffit donc d'utiliser le num�ro de la premi�re tile
//traversable au lieu de BLANK_TILE pour bloquer le joueur,
//seulement quand il tombe dessus (sinon, il passe au-travers
//et le test n'est donc pas effectu� dans les autres directions
                if (map.getTile(y2, x1) > TILE_TRAVERSABLE || map.getTile(y2, x2) > TILE_TRAVERSABLE)
                {
//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
//on le d�clare sur le sol (onGround).
                    y = y2 * TILE_SIZE;
                    y -= h;
                    dirY = 0;
                    onGround = 1;
                }
            }

            else if (dirY < 0)
            {
// D�placement vers le haut
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y1, x2) > BLANK_TILE)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }

//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
        if (i == w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > w)
        {
            i = w;
        }
    }

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
    x += dirX;
    y += dirY;

//Et on contraint son d�placement aux limites de l'�cran.
    if (x < 0)
    {
        x = 0;
    }

    else if (x + w >= map.getMaxX())
    {
//Si on touche le bord droit de l'�cran, on passe au niveau sup
        map.setLevel(map.getLevel() + 1);

//Si on d�passe le niveau max, on annule et on limite le d�placement du joueur
        if (map.getLevel() > LEVEL_MAX)
        {
            map.setLevel(LEVEL_MAX);
            x = map.getMaxX() - w - 1;
        }

//Sinon, on passe au niveau sup, on charge la nouvelle map et on r�initialise le joueur
        else
        {
//On d�sactive le checkpoint
            checkpointActif = 0;

            map.changeLevel();
            initialize(map, true);
        }
    }

//Maintenant, s'il sort de l'�cran par le bas (chute dans un trou sans fond), on lance le timer
//qui g�re sa mort et sa r�initialisation (plus tard on g�rera aussi les vies).
    if (y > map.getMaxY())
    {
        timerMort = 60;
    }
}

void Player::update(Input &input, Map &map)
{
//On rajoute un timer au cas o� notre h�ros mourrait lamentablement en tombant dans un trou...
//Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
//on r�initialise.
//C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0.
    if (timerMort == 0)
    {
//On g�re le timer de l'invincibilit�
        if (invincibleTimer > 0)
            invincibleTimer--;

//On r�initialise notre vecteur de d�placement lat�ral (X), pour �viter que le perso
//ne fonce de plus en plus vite pour atteindre la vitesse de la lumi�re ! ;)
//Essayez de le d�sactiver pour voir !
        dirX = 0;

// La gravit� fait toujours tomber le perso : on incr�mente donc le vecteur Y
        dirY += GRAVITY_SPEED;

//Mais on le limite pour ne pas que le joueur se mette � tomber trop vite quand m�me
        if (dirY >= MAX_FALL_SPEED)
            dirY = MAX_FALL_SPEED;


//Voil�, au lieu de changer directement les coordonn�es du joueur, on passe par un vecteur
//qui sera utilis� par la fonction mapCollision(), qui regardera si on peut ou pas d�placer
//le joueur selon ce vecteur et changera les coordonn�es du player en fonction.
        if (input.getButton().left == true)
        {
            dirX -= PLAYER_SPEED;
//Et on indique qu'il va � gauche (pour le flip
//de l'affichage, rappelez-vous).
            direction = LEFT;

//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
//le sol (car l'anim' sera diff�rente s'il est en l'air)
            if (etat != WALK && onGround == true)
            {
//On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

//Si on d�tecte un appui sur la touche fl�ch�e droite
        else if (input.getButton().right == true)
        {
//On augmente les coordonn�es en x du joueur
            dirX += PLAYER_SPEED;
//Et on indique qu'il va � droite (pour le flip
//de l'affichage, rappelez-vous).
            direction = RIGHT;

//Si ce n'�tait pas son �tat auparavant et qu'il est bien sur
//le sol (car l'anim' sera diff�rente s'il est en l'air)
            if (etat != WALK && onGround == true)
            {
//On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivit� (Idle)
        else if (input.getButton().right == false && input.getButton().left == false && onGround == true)
        {
//On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
//� chaque tour de boucle
            if (etat != IDLE)
            {
//On enregistre l'anim' de l'inactivit� et on l'initialise � 0
                etat = IDLE;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }


//Et voici la fonction de saut tr�s simple :
//Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
//n�gative au vecteur Y
//parce que sauter veut dire se rapprocher du haut de l'�cran et donc de y=0.
        if (input.getButton().jump == true)
        {
            if (onGround == true)
            {
                dirY = -JUMP_HEIGHT;
                onGround = false;
                Playerjump = true;
            }
// Si on est en saut 1, on peut faire un deuxi�me bond et on remet jump1 � 0
            else if (Playerjump == true)
            {
                dirY = -JUMP_HEIGHT;
                Playerjump = false;
            }
            input.setButton(jump, false);
        }


        /* R�active la possibilit� de double saut si on tombe sans sauter */
        if (onGround == true)
            Playerjump = true;


//On g�re l'anim du saut
        if (onGround == false)
        {
//Si on est en saut 1, on met l'anim' du saut normal
            if (Playerjump == true)
            {
                if (etat != JUMP1)
                {
                    etat = JUMP1;
                    frameNumber = 0;
                    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                    frameMax = 2;
                }
            }
            else
            {
                if (etat != JUMP2)
                {
                    etat = JUMP2;
                    frameNumber = 0;
                    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                    frameMax = 4;
                }
            }
        }

//On rajoute notre fonction de d�tection des collisions qui va mettre �
//jour les coordonn�es de notre super lapin.
        mapCollision(map);

//On g�re le scrolling (fonction ci-dessous)
        centerScrolling(map);

    }

//Gestion de la mort quand le h�ros tombe dans un trou :
//Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
//On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
// timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
//le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (timerMort > 0)
    {
        timerMort--;

        if (timerMort == 0)
        {
//On perd une vie
            vies--;

// Si on est mort, on r�initialise le niveau
            map.changeLevel();
            initialize(map, false);
        }
    }
}
