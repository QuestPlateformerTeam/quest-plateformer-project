#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "player.h"
#include "hud.h"
#include "fireball.h"
#include "fireballContainer.h"
#include "menu.h"
#include "coin.h"
#include "endGame.h"
#include "coinContainer.h"

int main(int argc, char *argv[])
{
    //Initialisation des objets et des variables nécéssaires à la gestion du jeu
    Player player(20,400);
    Map map;
    HudLayer hud;
    FireballContainer fireballContainer;
    CoinContainer coinContainer(map);
    Menu menu(map.getScreenWidth(), map.getScreenHeight());

    bool flagPause = false;
    bool flagInGame = false;//Je règle l'état EN JEU sur faux
    bool flagEndGame = false;//Je règle l'état FIN sur faux
    EndGame endGame(map.getScreenWidth(),map.getScreenHeight());
    bool flagGameOver = false; //Je règle l'état GAME OVER sur faux
    //Vu que les états sont tous faux je me redirige automatiquement vers mon menu

    sf::Music music; //Je déclare un variable musique globale qui affectera tout le jeu
    if (!music.openFromFile("ressources/songs/ansisys.ogg"))
        std::cout<<"Erreur lors du chargement de la musique"<<std::endl; // Je renvoie un message console pour me prévenir en cas d'erreur pour plus de facilité
    music.setVolume(10.f);//Réglage du volume qui attend un float
    music.setLoop(true); // Je boucle ma musique
    music.play(); //Je lance la musique

    sf::RenderWindow window(sf::VideoMode(map.getScreenWidth(), map.getScreenHeight(), map.getTileSize()), "Quest Plateformer | Neven - Leveau - Lopez - Moins "); // Je paramètre ma fenêtre
    window.setFramerateLimit(60);//Je règles l'affichage sur 60 images secondes
    window.setVerticalSyncEnabled(true);//j'active la synchronisation verticale pour éviter les grésillements

    sf::err().rdbuf(NULL); //Supprime une boucle warning console sur pc Alex

    while(window.isOpen()) //Boucle tant que ma fenêtre de jeu est ouverte
    {
        sf::Event event;
        while (window.pollEvent(event)) //Boucle pour capturer un objet de type Event
        {
            switch(event.type)
            {
                case sf::Event::Closed: //Si clique sur la croix de la fenêtre elle se ferme
                    window.close();
                    break;
                case sf::Event::KeyReleased: //Je capture un évènement lors du relachement d'une touche
                    menu.update(event, flagInGame, window, hud, flagPause); //J'envoie l'évènement dans une méthode qui met à jour mon menu principal.
                default:;
            }
        }
        window.clear(); // Je nettoie ma fenêtre avant de dessiner à nouveau
        //A partir d'ici je vérifie l'état de mon jeu {EN MENU, EN JEU, EN GAME OVER, EN FIN DE JEU}
        //Je place le 1er IF dans le dessus de la boucle pour optimiser le temps de chargement vu que c'est la fenêtre la plus gourmande
        //Et qui apparaitra le plus souvent
        if(flagInGame && !flagEndGame) //Si je suis en jeu
        {
            window.draw(map); //Je dessine ma map
            hud.draw(window, map, player); //Je dessine le HUD ou Affichage tête haute en français
            fireballContainer.draw(window); // J'initialise le conteneur de mes boules de feu
            coinContainer.draw(window); //J'initialise le contenur de mes pièces
            player.update(map, flagInGame, map.getTiles(), fireballContainer, coinContainer,flagEndGame, flagGameOver,flagPause); //Je mets à jour mon joueur et sa position sur la map
            player.draw(window,map); //Une fois la mise à jour du joueur faite, je le dessine
        }
        else if(flagEndGame || flagGameOver) //Si je suis en fin de partie ou en game over
        {
            flagInGame = false; //Je m'assure que je ne suis plus en jeu
            endGame.update(event,flagInGame,window,flagEndGame); //Je mets à jour mon menu de FIN de partie OU de GAME OVER
            endGame.draw(window,hud.getChrono()); // Je dessine le menu
        }
        else //Sinon je reviens sur le menu du jeu en cas de problème ou d'évènement inattendu
            menu.draw(window); // Je dessine mon menu
        window.display();//Une fois toutes les opérations faites, j'affiche tout le contenu de window sur la fenêtre qui est affichée à l'écran
    }
}

