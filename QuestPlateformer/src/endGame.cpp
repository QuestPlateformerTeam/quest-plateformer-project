#include "endGame.h"

EndGame::EndGame(float width, float height)
{
    this->width = width;//Je récupère la largeur de ma window
    this->height = height;//Je récupère la hauteur de ma window

    if(!font.loadFromFile("ressources/police/arial.ttf"))//Je charge ma police d'écriture
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl; //Msg d'erreur console

    /*
        Je prépare les textes pour mon menu
    */

    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play again");

    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Back to menu");

    selectedItemIndex = 0; //Item du menu qui est actuellement selectionné

    title.setString("END GAME");
    title.setFillColor(sf::Color::White);
    title.setFont(font);
    title.setCharacterSize(60);
    title.setPosition((this->width/2)-(title.getGlobalBounds().width/2),10);

    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);
}

EndGame::~EndGame()
{

}

void EndGame::draw(sf::RenderWindow& window, sf::Text chrono)
{
    window.draw(title);//Je dessine mon titre

    chrono.setPosition(sf::Vector2f(this->width/2 - 60, 100 ));
    chrono.setFont(font);
    chrono.setFillColor(sf::Color::White);
    chrono.setCharacterSize(30);
    window.draw(chrono); //Je draw mon la valeur stoppée de mon chrono qui vient de HUD

    for(int i = 0; i< MAX_NUMBER_OF_ITEMS_ENDGAME; i++){
        float calculatedWidthRect = (this->width/2) - 150;
        float calculatedWidthText = (this->width/2) - (menu[i].getGlobalBounds().width/2);
        float calculatedHeight = this->height/(MAX_NUMBER_OF_ITEMS_ENDGAME+1)*(i+1);

        rectangle.setPosition(calculatedWidthRect,calculatedHeight - 5 );
        menu[i].setPosition(sf::Vector2f(calculatedWidthText,calculatedHeight));
        menu[i].setFont(font);

        window.draw(rectangle);
        window.draw(menu[i]);
    }
}

void EndGame::update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window,bool& flagEndGame)
{
    if(!flagInGame) //Si je ne suis pas en jeu
    {
        switch (event.key.code) //Je fais un switch sur l'event
        {
            case sf::Keyboard::Up: //Si j'appuie sur la flèche du haut
                MoveUp(); //Je bouge sur la case au dessus
                break;
            case sf::Keyboard::Down: //Si j'appuie sur la flèche du bas
                MoveDown(); //Je descends dans mon menu
                break;
            case sf::Keyboard::Return: //Si j'appuie sur Enter
                switch(selectedItemIndex) //En fonction de l'élément selectionné
                {
                    case 0: //Je relance le jeu
                        std::cout << "Play button has been pressed" <<std::endl;
                        flagInGame = true;
                        flagEndGame = false;
                        break;

                    case 1: //je reviens au menu
                        flagInGame = false;
                        flagEndGame = false;
                        break;
                    default:break;
                }
            default:break;
        }
    }
}

/*
    Globalement les mouvements permette d'attribuer
    à la variable selectedItemIndex la box sur laquelle elle se trouve
    et de mettre en rouge le menu text sur lequel elle se trouve
*/

void EndGame::MoveUp(){
    if(selectedItemIndex - 1 >=0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void EndGame::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS_ENDGAME){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
