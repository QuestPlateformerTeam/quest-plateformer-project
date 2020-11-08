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
//PV à 3
    life = 3;

//Timer d'invincibilité à 0
    invincibleTimer = 0;

//Indique l'état et la direction de notre héros
    direction = RIGHT;
    etat = IDLE;

//Indique le numéro de la frame où commencer
    frameNumber = 0;

//...la valeur de son chrono ou timer
    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//... et son nombre de frames max (8 pour l'anim' IDLE
// = ne fait rien)
    frameMax = 8;

    /* Coordonnées de démarrage/respawn de notre héros.
    Plus tard, quand on aura rajouté la gestion de nos
    checkpoints, le héros pourra y ressusciter directement
    sans recommencer le niveau. Mais pour l'instant, il restera
    à false, et on recommencera donc au début du niveau (beginX, beginY) */
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

    /* Hauteur et largeur de notre héros */
    w = PLAYER_WIDTH;
    h = PLAYER_HEIGTH;

//Variables nécessaires au fonctionnement de la gestion des collisions
    timerMort = 0;
    onGround = false;
}

void Player::draw(Map &map, RenderWindow &window)
{
    /* Gestion du timer */
// Si notre timer (un compte à rebours en fait) arrive à zéro
    if (frameTimer <= 0)
    {
//On le réinitialise
        frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

//Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
        frameNumber++;

//Mais si on dépasse la frame max, il faut revenir à la première :
        if (frameNumber >= frameMax)
            frameNumber = 0;
    }
//Sinon, on décrémente notre timer
    else
        frameTimer--;


//Ensuite, on peut passer la main à notre fonction
    rabidja.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));

//Pour connaître le X de la bonne frame à dessiner, il suffit de multiplier
//la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
//On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros :
//Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
//Tout cela en accord avec notre spritesheet, of course ;)

//Si on a été touché et qu'on est invincible
    if (invincibleTimer > 0)
    {
//On fait clignoter le héros une frame sur deux
//Pour ça, on calcule si le numéro de la frame en
//cours est un multiple de deux
        if (frameNumber % 2 == 0)
        {
//Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche)
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
//Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche)
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
// Nouveau scrolling à sous-boîte limite :
//Pour éviter les effets de saccades dus à une caméra qui se
//centre automatiquement et constamment sur le joueur (ce qui
//peut en rendre malade certains...), on crée une "boîte" imaginaire
//autour du joueur. Quand on dépasse un de ses bords (en haut, en bas,
//à gauche ou à droite), on scrolle.
//Mais là encore, au lieu de centrer sur le joueur, on déplace simplement
//la caméra jusqu'à arriver au joueur. On a changé ici la valeur à 4 pixels
//pour que le jeu soit plus rapide.
    int cxperso = x + w / 2;
    int cyperso = y + h / 2;
    int xlimmin = map.getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = map.getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

//Effet de retour en arrière quand on est mort :
//Si on est très loin de la caméra, plus loin que le bord
//de la map, on accélère le scrolling :
    if (cxperso < map.getStartX())
    {
        map.setStartX(map.getStartX() - 30);
    }

//Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        map.setStartX(map.getStartX() - 4);
    }

//Effet de retour en avant quand on est mort (au
//cas où le joueur s'amuse à faire le niveau à rebours
//après une checkpoint) :
//Si on est très loin de la caméra, plus loin que le bord
//de la map, on accélère le scrolling :
    if (cxperso > map.getStartX() + SCREEN_WIDTH)
    {
        map.setStartX(map.getStartX() + 30);
    }

//Si on dépasse par la droite, on avance la caméra
    else if (cxperso > xlimmax)
    {
        map.setStartX(map.getStartX() + 4);
    }

//Si on arrive au bout de la map à gauche, on stoppe le scrolling
    if (map.getStartX() < 0)
    {
        map.setStartX(0);
    }

//Si on arrive au bout de la map à droite, on stoppe le scrolling à la
//valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
    {
        map.setStartX(map.getMaxX() - SCREEN_WIDTH);
    }

//Si on dépasse par le haut, on remonte la caméra
    if (cyperso < ylimmin)
    {
        map.setStartY(map.getStartY() - 4);
    }

//Si on dépasse par le bas, on descend la caméra
    if (cyperso > ylimmax)
    {
//Sauf si on tombe très vite, auquel cas, on accélère la caméra :
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

//Si on arrive au bout de la map en bas, on stoppe le scrolling à la
//valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (map.getStartY() + SCREEN_HEIGHT >= map.getMaxY())
    {
        map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
    }

}

void Player::mapCollision(Map &map)
{

    int i, x1, x2, y1, y2;

    /* D'abord, on considère le joueur en l'air jusqu'à temps
    d'être sûr qu'il touche le sol */
    onGround = 0;

    /* Ensuite, on va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va découper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il
    teste la tile où se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas où notre sprite serait inférieur à la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la même tile. Mais comme ça notre code
    sera opérationnel quelle que soit la taille de nos sprites ! */

    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;


//On lance alors une boucle for infinie car on l'interrompra selon
//les résultats de nos calculs
    for (;;)
    {
//On va calculer ici les coins de notre sprite à gauche et à
//droite pour voir quelle tile ils touchent.
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;

//Même chose avec y, sauf qu'on va descendre au fur et à mesure
//pour tester toute la hauteur de notre sprite, grâce à notre
//fameuse variable i.
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;

//De là, on va tester les mouvements initiés dans updatePlayer
//grâce aux vecteurs dirX et dirY, tout en testant avant qu'on
//se situe bien dans les limites de l'écran.
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
//Si on a un mouvement à droite
            if (dirX > 0)
            {
//On vérifie si les tiles recouvertes sont solides
                if (map.getTile(y1, x2) > BLANK_TILE || map.getTile(y2, x2) > BLANK_TILE)
                {
// Si c'est le cas, on place le joueur aussi près que possible
// de ces tiles, en mettant à jour ses coordonnées. Enfin, on
//réinitialise son vecteur déplacement (dirX).

                    x = x2 * TILE_SIZE;
                    x -= w + 1;
                    dirX = 0;
                }
            }

//Même chose à gauche
            else if (dirX < 0)
            {
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y2, x1) > BLANK_TILE)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }

        }

//On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == h)
        {
            break;
        }

//Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;

        if (i > h)
        {
            i = h;
        }
    }


//On recommence la même chose avec le mouvement vertical (axe des Y)
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
// Déplacement en bas
//Gestion des plateformes traversables : elles se situent juste avant
//les tiles bloquantes dans notre tileset (dont la valeur butoire est
//BLANK_TILE). Il suffit donc d'utiliser le numéro de la première tile
//traversable au lieu de BLANK_TILE pour bloquer le joueur,
//seulement quand il tombe dessus (sinon, il passe au-travers
//et le test n'est donc pas effectué dans les autres directions
                if (map.getTile(y2, x1) > TILE_TRAVERSABLE || map.getTile(y2, x2) > TILE_TRAVERSABLE)
                {
//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
//on le déclare sur le sol (onGround).
                    y = y2 * TILE_SIZE;
                    y -= h;
                    dirY = 0;
                    onGround = 1;
                }
            }

            else if (dirY < 0)
            {
// Déplacement vers le haut
                if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y1, x2) > BLANK_TILE)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }

//On teste la largeur du sprite (même technique que pour la hauteur précédemment)
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

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    x += dirX;
    y += dirY;

//Et on contraint son déplacement aux limites de l'écran.
    if (x < 0)
    {
        x = 0;
    }

    else if (x + w >= map.getMaxX())
    {
//Si on touche le bord droit de l'écran, on passe au niveau sup
        map.setLevel(map.getLevel() + 1);

//Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
        if (map.getLevel() > LEVEL_MAX)
        {
            map.setLevel(LEVEL_MAX);
            x = map.getMaxX() - w - 1;
        }

//Sinon, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
        else
        {
//On désactive le checkpoint
            checkpointActif = 0;

            map.changeLevel();
            initialize(map, true);
        }
    }

//Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
//qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
    if (y > map.getMaxY())
    {
        timerMort = 60;
    }
}

void Player::update(Input &input, Map &map)
{
//On rajoute un timer au cas où notre héros mourrait lamentablement en tombant dans un trou...
//Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
//on réinitialise.
//C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
    if (timerMort == 0)
    {
//On gère le timer de l'invincibilité
        if (invincibleTimer > 0)
            invincibleTimer--;

//On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
//ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
//Essayez de le désactiver pour voir !
        dirX = 0;

// La gravité fait toujours tomber le perso : on incrémente donc le vecteur Y
        dirY += GRAVITY_SPEED;

//Mais on le limite pour ne pas que le joueur se mette à tomber trop vite quand même
        if (dirY >= MAX_FALL_SPEED)
            dirY = MAX_FALL_SPEED;


//Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
//qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
//le joueur selon ce vecteur et changera les coordonnées du player en fonction.
        if (input.getButton().left == true)
        {
            dirX -= PLAYER_SPEED;
//Et on indique qu'il va à gauche (pour le flip
//de l'affichage, rappelez-vous).
            direction = LEFT;

//Si ce n'était pas son état auparavant et qu'il est bien sur
//le sol (car l'anim' sera différente s'il est en l'air)
            if (etat != WALK && onGround == true)
            {
//On enregistre l'anim' de la marche et on l'initialise à 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

//Si on détecte un appui sur la touche fléchée droite
        else if (input.getButton().right == true)
        {
//On augmente les coordonnées en x du joueur
            dirX += PLAYER_SPEED;
//Et on indique qu'il va à droite (pour le flip
//de l'affichage, rappelez-vous).
            direction = RIGHT;

//Si ce n'était pas son état auparavant et qu'il est bien sur
//le sol (car l'anim' sera différente s'il est en l'air)
            if (etat != WALK && onGround == true)
            {
//On enregistre l'anim' de la marche et on l'initialise à 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Idle)
        else if (input.getButton().right == false && input.getButton().left == false && onGround == true)
        {
//On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
//à chaque tour de boucle
            if (etat != IDLE)
            {
//On enregistre l'anim' de l'inactivité et on l'initialise à 0
                etat = IDLE;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }


//Et voici la fonction de saut très simple :
//Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
//négative au vecteur Y
//parce que sauter veut dire se rapprocher du haut de l'écran et donc de y=0.
        if (input.getButton().jump == true)
        {
            if (onGround == true)
            {
                dirY = -JUMP_HEIGHT;
                onGround = false;
                Playerjump = true;
            }
// Si on est en saut 1, on peut faire un deuxième bond et on remet jump1 à 0
            else if (Playerjump == true)
            {
                dirY = -JUMP_HEIGHT;
                Playerjump = false;
            }
            input.setButton(jump, false);
        }


        /* Réactive la possibilité de double saut si on tombe sans sauter */
        if (onGround == true)
            Playerjump = true;


//On gère l'anim du saut
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

//On rajoute notre fonction de détection des collisions qui va mettre à
//jour les coordonnées de notre super lapin.
        mapCollision(map);

//On gère le scrolling (fonction ci-dessous)
        centerScrolling(map);

    }

//Gestion de la mort quand le héros tombe dans un trou :
//Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
//On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
// timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
//le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (timerMort > 0)
    {
        timerMort--;

        if (timerMort == 0)
        {
//On perd une vie
            vies--;

// Si on est mort, on réinitialise le niveau
            map.changeLevel();
            initialize(map, false);
        }
    }
}
