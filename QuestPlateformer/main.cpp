#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "player.h"
#include "menu.h"
#include "pickup.h"

int main(int argc, char *argv[])
{
    Player player(50,600);
    Map map("ressources/maps/map1.txt");
    Menu menu(map.getScreenWidth(), map.getScreenHeight());
    bool flagInGame = false;
    sf::Texture texturePiece;


   /* //Charger une piece
    if(texturePiece.loadFromFile("ressources/graphics/piece.png"))
        std::cout<<"Erreur lors du chargement de la piece"<<std::endl;

    vector<pickup>::const_iterator iter1;
    vector<picup> pickupArray;

    class pickup pickup1;*/


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
            player.update(map, flagInGame, map.getTiles());
            player.draw(window,map);
        }
        else
            menu.draw(window);
        window.display();
    }
}

