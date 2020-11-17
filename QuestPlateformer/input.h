#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <SFML/Graphics.hpp>

class Input
{
    //Structures
    struct Button { bool left, right, up, down, jump, attack, enter; };

    public:
        //Constructeur
        Input();
        //Accesseur
        Button getButton() const;
        //Mutateur
        void setButton(int bouton, bool etat);
        //Fonctions
        void gestionInputs(sf::RenderWindow &window);
        void getInput(sf::RenderWindow &window);


    private:
        //Variables de la classe en acc�s priv�
        sf::Event event;
        Button button;
        //Enum pour les boutons
        enum{ up, down, right, left, attack, jump, enter };

};
#endif
