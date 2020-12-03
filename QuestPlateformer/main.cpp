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
#include "coinContainer.h"

int main(int argc, char *argv[])
{
    Player player(20,400);
    Map map;
    HudLayer hud;
    FireballContainer fireballContainer;
    CoinContainer coinContainer;
    Menu menu(map.getScreenWidth(), map.getScreenHeight());
    bool flagInGame = false;

    sf::Music music;
    if (!music.openFromFile("ressources/songs/ansisys.wav"))
        std::cout<<"Erreur lors du chargement de la musique"<<std::endl;
    music.setVolume(10.f);
    music.play();

    sf::RenderWindow window(sf::VideoMode(map.getScreenWidth(), map.getScreenHeight(), map.getTileSize()), "Quest Plateformer | Neven - Leveau - Lopez - Moins ");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::err().rdbuf(NULL); //Supprime une boucle warning console sur pc Alex

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event) )
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    menu.update(event, flagInGame, window);
            }
        }
        window.clear();
        if(flagInGame)
        {
            window.draw(map);
            hud.draw(window, map, player);
            fireballContainer.draw(window);
            coinContainer.draw(window);
            player.update(map, flagInGame, map.getTiles(), fireballContainer, coinContainer);
            player.draw(window,map);
        }
        else
            menu.draw(window);
        window.display();
    }
}

