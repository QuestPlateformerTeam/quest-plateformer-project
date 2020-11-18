#include <cstdlib>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "main.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Quest Plateformer");
    //Limite les fps à 60 images / seconde
    window.setFramerateLimit(60);

    //On active la synchro verticale
    window.setVerticalSyncEnabled(true);

    //Instanciation des classes
    Input input;
    Map map;
    Player player;

    sf::Music music;
    if (!music.openFromFile("ressources/songs/ansisys.wav"))
        return -1; // erreur
    music.play();
    music.setVolume(5.f);

    Menu menu(window.getSize().x, window.getSize().y);
    bool flagOut = false;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
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
                                    //On commence au premier niveau (vous pouvez aussi mettre 2 pour tester le 2ème niveau)
                                    map.setLevel(1);
                                    map.changeLevel();

                                    //On initialise le player
                                    player.initialize(map, true);
                                    player.setVies(3);
                                    player.setEtoiles(0);

                                    while (window.isOpen())
                                    {
                                        // GESTION DES INPUTS (CLAVIER, JOYSTICK)
                                        input.gestionInputs(window);
                                        // MISES A JOUR - UPDATES
                                        //On met à jour le player : Rabidja
                                        player.update(input, map);
                                        // DESSIN - DRAW
                                        //On dessine tout
                                        window.clear();
                                        //On affiche le background
                                        map.drawBackground(window);
                                        // Affiche la map de tiles : layer 2 (couche du fond)
                                        map.draw(2, window);
                                        // Affiche la map de tiles : layer 1 (couche active : sol, etc.)
                                        map.draw(1, window);
                                        // Affiche le joueur
                                        player.draw(map, window);
                                        // Affiche la map de tiles : layer 3 (couche en foreground / devant)
                                        map.draw(3, window);
                                        window.display();
                                    }
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

        window.clear();

        menu.draw(window);

        window.display();
    }
}
