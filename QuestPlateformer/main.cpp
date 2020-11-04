#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "input.h"

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
    // Cr�ation d'une fen�tre en SFML
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
    "Rabidja 3.0 - Chapitre 3 - Big Tuto SFML2 - www.meruvia.fr");

    //Limite les fps � 60 images / seconde
    window.setFramerateLimit(60);


    //On active la synchro verticale
    window.setVerticalSyncEnabled(true);

    //Instanciation des classes
    Input input;

    // Boucle infinie, principale, du jeu
    while (window.isOpen())
    {
        /** GESTION DES INPUTS (CLAVIER, JOYSTICK) **/
        input.gestionInputs(window);

        /** DESSIN - DRAW **/
        //On efface l'�cran et on l'affiche
        window.clear();
        window.display();
    }

    // On quitte
    return 0;
}
