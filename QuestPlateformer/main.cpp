#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "main.h"

int main(int argc, char *argv[])
{
// Création d'une fenêtre en SFML
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Ninjaaaa");

//Limite les fps à 60 images / seconde
    window.setFramerateLimit(60);

//On active la synchro verticale
    window.setVerticalSyncEnabled(true);

//Instanciation des classes
    Input input;
    Map map;
    Player player;

//On commence au premier niveau (vous pouvez aussi mettre 2 pour tester le 2ème niveau)
    map.setLevel(1);
    map.changeLevel();

//On initialise le player
    player.initialize(map, true);
    player.setVies(3);
    player.setEtoiles(0);

    /*sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("ressources/songs/ansisys.wav"))
        return -1;*/
    sf::Music music;
    if (!music.openFromFile("ressources/songs/ansisys.wav"))
        return -1; // erreur
    music.play();
    music.setVolume(50.f);

// Boucle infinie, principale, du jeu
    while (window.isOpen())
    {
        /** GESTION DES INPUTS (CLAVIER, JOYSTICK) **/
        input.gestionInputs(window);

        /** MISES A JOUR - UPDATES **/
        //On met à jour le player : Rabidja
        player.update(input, map);

        /** DESSIN - DRAW **/
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

// On quitte
    return 0;

}
