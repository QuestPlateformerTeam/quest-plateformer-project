#include "player.h"
#include "math.h"

//Constructeur de mon objet player
Player::Player(int x, int y)
{
    //J'affecte � mon joueur une position X et Y sur la fen�tre.
    this->positionX = x;
    this->positionY = y;

    //Je charge une texture et je mets la texture dans le sprite pour pouvoir l'utiliser � l'�cran
    if (!texture.loadFromFile("ressources/graphics/deadpool.png"))
        std::cout << "Erreur durant le chargement du spritesheet du player." << std::endl; //Retourne un message console en cas d'erreur
    else
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT,PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT)); //Je r�cup�re une image sp�cifique sur ma spritesheet
    }

    /*
        Ici je charge les deux fichiers audio que le joueur rencontrera sur la map
    */
    if (!soundDeath.openFromFile("ressources/songs/deathSound.ogg")) //Chargement du fichier audio son de mort du joueur
        std::cout<<"Erreur lors du chargement du son de mort"<<std::endl;//Retourne un message console en cas d'erreur
    soundDeath.setVolume(10.f);

    if (!soundCoin.openFromFile("ressources/songs/coin.ogg")) //Chargement du fichier audio son r�cup�ration d'une pi�ce
        std::cout<<"Erreur lors du chargement du son de mort"<<std::endl;//Retourne un message console en cas d'erreur
    soundCoin.setVolume(10.f);


}

Player::~Player()
{
    //destructeur
}

/*
    =================
    Getters & Setters
    =================
*/
void Player::setLife(int newLife){this->life = newLife;}
int Player::getLife(){return life;}
//Fonction pour renvoyer le joueur � son point de d�part
void Player::setPlayerAtStart(Map map){this->positionX = map.getStartX();this->positionY = map.getStartY();}


void Player::isDead(Map& map, bool& flagEndGame, bool& flagInGame) //Fonction qui g�re la mort d'un joueur
{
    sf::sleep(sf::milliseconds(750)); // Je fais une pause de 0,75s pour attirer le joueur sur sa mort et le pr�parer � la r�apparition

    if(life > 1) // Si il lui reste des vies
    {
        life--; // Je retire une vie
        sprite.setTextureRect(sf::IntRect(1 * PLAYER_HEIGHT ,PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT)); // Je recharge son sprite en position de d�part
        setPlayerAtStart(map); // Je renvoie le joueur au point de d�part
    }
    else //Si le joueur n'a plus de vie
    {
        flagEndGame = true; //J'active l'�tat GAME OVER
        flagInGame = false; //Je m'assure qu'il ne soit plus en partie

        map.resetGame(); //Je reset la partie
        setLife(3); // Je pr� rempli sa vie � 3 pour la prochaine partie
        setPlayerAtStart(map); // Je renvoie le joueur au d�part pour la prochaine partie
    }
}

// Fonction pour dessiner mon joueur sur la map
void Player::draw(sf::RenderWindow& window, Map map)
{
    window.draw(sprite);
}

//Fonction pour actualiser les infos du joueur
void Player::update(Map& map, bool& flagInGame, const int* level, FireballContainer& fireballContainer, CoinContainer& coinContainer, bool& flagEndGame, bool& flagGameOver, bool& flagPause)
{

    deplacement(flagInGame,map,level,flagPause);// Une fonction a �t� cr��e s�paremment pour s'y retrouver plus facilement dans le code

    sprite.setPosition(sf::Vector2f(this->positionX,this->positionY)); //J'actualise la position de mon joueur

    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds())) // je viens v�rifier si mon joueur entre en collision avec une tuile de la map VOIR MAP.H pour comprendre
    {
        //Si mon joueur marche sur la tile EXIT et qu'il a ramass� toutes les pi�ces alors le joueur valide la condition
        if (level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == EXIT_TILE && coinContainer.isAllLooted())
        {
            map.changeToNextLevel(flagEndGame, flagInGame); //Je passe au niveau suivant
            setPlayerAtStart(map); //J'envoie le joueur au d�part
            fireballContainer.resetAll(); //Je red�marre le boules de feu
            coinContainer.loadConfig(map); // Je recharge bien le bon map config pour les pi�ces
            coinContainer.resetAll(); //Je les replace toutes � leur position
            coinContainer.setLooted(false);//Je pr�cise que mon joueur n'a pas ramass� les pi�ces
            if(flagEndGame)// Et si le joueur finit la partie en marchant sur le dernier EXIT alors, je remets sa vie � 3 pour le pr�parer � une nouvelle partie
                life = 3;
        }

        if ((level[map.getTileNumber(positionX, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)]) == TILE_KILL )// Si le joueur marche sur la TILE lave
        {
            soundDeath.stop(); //Je m'assure que mon son est stopp�
            soundDeath.play();//Je lance le son de mort
            isDead(map, flagEndGame, flagInGame); // J'active la fonction mort
            fireballContainer.resetAll();// Je reset les boules de feu
            coinContainer.loadConfig(map); //Je recharge mon fichier de config
            coinContainer.resetAll(); //Je reset les pi�ces
        }

    }

    for(int i = 0; i<=fireballContainer.getNbFireball(); i++)//Je boucle sur toutes mes boules de feu
    {
        if (Collision::PixelPerfectTest(sprite,fireballContainer.getOneFireball(i).getSprite()))//J'utilise la fonction de perfect pixel collision avec une boule de feu
        {
            soundDeath.stop(); //Je m'assure que mon son est stopp�
            soundDeath.play(); //Je lance le son de mort
            isDead(map,flagEndGame, flagInGame); // J'active la fonction mort
            fireballContainer.resetAll(); // Je reset les boules de feu
            coinContainer.loadConfig(map); //Je recharge mon fichier de config
            coinContainer.resetAll(); //Je reset les pi�ces
            hasJump = false; //Je dis que mon joueur n'est pas en saut pour qu'au respawn il ne saute pas tout seul
        }
    }

    for(int i = 0; i<=coinContainer.getNbCoin(); i++)//Je boucle sur toutes mes pi�ces
    {
        if(Collision::PixelPerfectTest(sprite,coinContainer.getOneCoin(i)) && coinContainer.getThisCoin(i).getDisplay()) //J'utilise la fonction de perfect pixel collision avec les pi�ces
        {
            soundCoin.stop();//Je m'assure que mon son est stopp�
            soundCoin.play();//Je lance le son
            coinContainer.changeToNextCoin();// Si j'ai touch� une pi�ce je peux afficher la suivante
        }
    }
}

void Player::deplacement(bool& flagInGame, Map& map,const int* level, bool& flagPause) //D�placement
{
    if(hasJump && !lockUp) //Condition qui v�rifie que mon joueur � sauter et qu'il n'est pas bloqu� par un mur au dessus de lui
    {
        this->positionY-= velocityY*0.7; //Calcul pour faire monter le joueur
        if(fromHeight-this->positionY >= MAX_HEIGHT_JUMP) //Si le joueur atteint la hauteur max pr�vue pour le saut
            isTopOfJump = true;//je dis qu'il a atteint le haut de son saut pour pr�voir la redescente
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !lockLeft)//Si le joueur appuie sur la touche et que le boolean lui permet d'aller � gauche
    {
        positionX-= MOVESPEED; //Le joueur se d�place vers la gauche
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT ,PLAYER_WIDTH * 1.2,PLAYER_WIDTH,PLAYER_HEIGHT));//J'affiche le sprite qui correspond � un d�placement gauche
        if(!hasJump)//Si il n'est pas dans les airs
        {
            timee++;
            if(timee==5)
            {
                counterWalking++;//J'anime le joueur
                timee =0;
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !lockRight)//Si le joueur appuie sur la touche et que le boolean lui permet d'aller � droite
    {
        positionX+= MOVESPEED;
        sprite.setTextureRect(sf::IntRect(counterWalking * PLAYER_HEIGHT, PLAYER_WIDTH * 2.4,PLAYER_WIDTH,PLAYER_HEIGHT)); //J'affiche le sprite qui correspond � un d�placement � droite
        if(!hasJump)
        {
            timee++;
            if(timee==5)
            {
                counterWalking++; //J'anime le joueur
                timee =0;
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !lockUp && canJump) //Si le joueur appuie sur la touche et que le boolean lui permet de sauter
    {
        hasJump = true; //Je dis que mon joueur � sauter
        isTopOfJump = false; //Je dis qu'il n'a pas atteint la hauteur max de son saut
        fromHeight = this->positionY; // Je r�cup�re la position depuis laquelle il saute
        canJump = false; //Je pr�viens le double jump en bloquant le saut si il est en l'air
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si j'appuie sur escape mon joueur revient au menu pause
    {
        flagInGame = false;
        flagPause = true;
    }

    if(counterWalking == 3) //Si j'arrive � la fin de mon animation je la recommence
        counterWalking = 0;


    if (sprite.getGlobalBounds().intersects(map.getVertices().getBounds())) //Ici sont plac�es les conditions pour v�rifier les collisions du joueur avec son environnement
    {

        if ((level[map.getTileNumber(positionX+20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE)|| positionX>=780)
            lockRight = true; //Si je rencontre le bord de la map ou le bord d'un mur je bloque la droite
        else
            lockRight = false; //Sinon j'autorise

        if ((level[map.getTileNumber(positionX-20, positionY,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE)|| positionX<=-5)
            lockLeft = true; //Si je rencontre le bord de la map ou le bord d'un mur je bloque la gauche
        else
            lockLeft = false;

        if (level[map.getTileNumber(positionX, positionY+25,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE)
        {
            lockDown = true; //Si je rencontre le bord de la map ou le bord d'un mur je bloque le bas
            canJump = true; //Je m'assure que le joueur peut sauter
            isTopOfJump = false; // Mais donc je m'assure que s'il vient de sauter il ne peut pas directement �tre au sommet du saut
        }else if(isTopOfJump || !hasJump) //Sinon le il est en haut d'un saut et qu'il ne vient pas sauter comme si il quitte un bloc plus haut pour un bloc plus bas
        {
            lockDown = false; //J'autorise la chute
            this->positionY+= velocityY*0.5; //Calcul de la chute
            hasJump = false; //Je m'assure que le joueur ne vient pas de sauter
        }
        if ((level[map.getTileNumber(positionX, positionY-25,PLAYER_WIDTH,PLAYER_HEIGHT)] == WALL_TILE )|| positionY>=455)
        {
            lockUp = true; //Si je rencontre le bord de la map ou le bord d'un mur je bloque le haut
            isTopOfJump = true; //J'assure que je ne suis donc en phase descendante d'un saut

        }else
            lockUp = false; //Sinon je bloque le saut
    }
}

