#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "player.h"
#include "hud.h"
#include "fireballContainer.h"
#include "menu.h"
#include "endGame.h"
#include "coinContainer.h"

int main(int argc, char *argv[])
{
    //Initialisation des objets et des variables n�c�ssaires � la gestion du jeu
    Player player(20,400);
    Map map;
    HudLayer hud;
    FireballContainer fireballContainer;
    CoinContainer coinContainer(map);
    Menu menu(map.getScreenWidth(), map.getScreenHeight());

    bool flagPause = false;
    bool flagInGame = false;//Je r�gle l'�tat EN JEU sur faux
    bool flagEndGame = false;//Je r�gle l'�tat FIN sur faux
    EndGame endGame(map.getScreenWidth(),map.getScreenHeight());
    bool flagGameOver = false; //Je r�gle l'�tat GAME OVER sur faux
    //Vu que les �tats sont tous faux je me redirige automatiquement vers mon menu

    sf::Music music; //Je d�clare un variable musique globale qui affectera tout le jeu
    if (!music.openFromFile("../ressources/songs/ansisys.ogg"))
        std::cout<<"Erreur lors du chargement de la musique"<<std::endl; // Je renvoie un message console pour me pr�venir en cas d'erreur pour plus de facilit�
    music.setVolume(10.f);//R�glage du volume qui attend un float
    music.setLoop(true); // Je boucle ma musique
    music.play(); //Je lance la musique

    sf::RenderWindow window(sf::VideoMode(map.getScreenWidth(), map.getScreenHeight(), map.getTileSize()), "Quest Plateformer | Neven - Leveau - Lopez - Moins "); // Je param�tre ma fen�tre
    window.setFramerateLimit(60);//Je r�gles l'affichage sur 60 images secondes

    sf::err().rdbuf(NULL); //Supprime une boucle warning console sur pc Alex

    while(window.isOpen()) //Boucle tant que ma fen�tre de jeu est ouverte
    {
        sf::Event event;
        while (window.pollEvent(event)) //Boucle pour capturer un objet de type Event
        {
            switch(event.type)
            {
                case sf::Event::Closed: //Si clique sur la croix de la fen�tre elle se ferme
                    window.close();
                    break;
                case sf::Event::KeyReleased: //Je capture un �v�nement lors du relachement d'une touche
                    menu.update(event, flagInGame, window, hud, flagPause); //J'envoie l'�v�nement dans une m�thode qui met � jour mon menu principal.
                default:;
            }
        }
        window.clear(); // Je nettoie ma fen�tre avant de dessiner � nouveau
        //A partir d'ici je v�rifie l'�tat de mon jeu {EN MENU, EN JEU, EN GAME OVER, EN FIN DE JEU}
        //Je place le 1er IF dans le dessus de la boucle pour optimiser le temps de chargement vu que c'est la fen�tre la plus gourmande
        //Et qui apparaitra le plus souvent
        if(flagInGame && !flagEndGame) //Si je suis en jeu
        {
            window.draw(map); //Je dessine ma map
            hud.draw(window, map, player); //Je dessine le HUD ou Affichage t�te haute en fran�ais
            fireballContainer.draw(window); // J'initialise le conteneur de mes boules de feu
            coinContainer.draw(window); //J'initialise le contenur de mes pi�ces
            player.update(map, flagInGame, map.getTiles(), fireballContainer, coinContainer,flagEndGame, flagGameOver,flagPause); //Je mets � jour mon joueur et sa position sur la map
            player.draw(window,map); //Une fois la mise � jour du joueur faite, je le dessine
        }
        else if(flagEndGame || flagGameOver) //Si je suis en fin de partie ou en game over
        {
            flagInGame = false; //Je m'assure que je ne suis plus en jeu
            endGame.update(event,flagInGame,window,flagEndGame); //Je mets � jour mon menu de FIN de partie OU de GAME OVER
            endGame.draw(window,hud.getChrono()); // Je dessine le menu
        }
        else //Sinon je reviens sur le menu du jeu en cas de probl�me ou d'�v�nement inattendu
            menu.draw(window); // Je dessine mon menu
        window.display();//Une fois toutes les op�rations faites, j'affiche tout le contenu de window sur la fen�tre qui est affich�e � l'�cran
    }
}

