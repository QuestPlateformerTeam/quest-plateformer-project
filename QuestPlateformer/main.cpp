#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "player.h"
#include "homeMenu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Quest Plateformer | Neven - Leveau - Lopez - Moins ");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Map map;
    HomeMenu menu(window.getSize().x, window.getSize().y);
    Player player(100,100);
    //Supprime une boucle erreur
    sf::err().rdbuf(NULL);
    bool flagInGame = false;

    while(window.isOpen())
    {
        // Création d'un évènement pour fermer la fenêtre
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
                                menu.MoveUp();
                                break;
                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;
                            case sf::Keyboard::Return:
                                switch(menu.GetPressedItem())
                                {
                                    case 0:
                                        std::cout << "Play button has been pressed" <<std::endl;
                                        flagInGame = true;
                                        break;
                                    case 1:
                                        std::cout << "Options button has been pressed" <<std::endl;
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

            map.drawBackground(window);
            player.update(map, flagInGame);
            player.draw(window,map);
        }
        else
            menu.draw(window);

        window.display();
    }




}

