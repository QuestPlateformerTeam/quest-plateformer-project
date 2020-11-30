#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "player.h"
#include "homeMenu.h"

int main(int argc, char *argv[])
{
    Map map;
    Player player(map.getStartX()+50,map.getStartY());
    Player player2(map.getStartX(),map.getStartY());
    HomeMenu homeMenu(map.getScreenWidth(), map.getScreenHeight());

    sf::RenderWindow window(sf::VideoMode(map.getScreenWidth(), map.getScreenHeight(), map.getTileSize()), "Quest Plateformer | Neven - Leveau - Lopez - Moins ");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    bool flagInGame = false;

    // on crée la tilemap avec le niveau précédemment défini
    if (!map.load("ressources/graphics/tileset1.png", sf::Vector2u(map.getTileSize(), map.getTileSize()), map.getNbTileByLine(), map.getNbTileByColumn(), window))
        return -1;

    //Supprime une boucle warning console sur pc Alex
    sf::err().rdbuf(NULL);


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
                    if(!flagInGame)
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Up:
                                homeMenu.MoveUp();
                                break;
                            case sf::Keyboard::Down:
                                homeMenu.MoveDown();
                                break;
                            case sf::Keyboard::Return:
                                switch(homeMenu.GetPressedItem())
                                {
                                    case 0:
                                        std::cout << "Play button has been pressed" <<std::endl;
                                        flagInGame = true;
                                        break;
                                    case 1:
                                        std::cout << "Options button has been pressed" <<std::endl;
                                        flagInGame = false;
                                        break;
                                    case 2:
                                        window.close();
                                        break;
                                }
                        }
                    }
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
            homeMenu.draw(window);


        window.display();
    }




}

