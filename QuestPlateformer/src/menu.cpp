#include "menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

Menu::Menu(float width, float height)
{
    this->width = width; //Je r�cup�re la largeur de ma window
    this->height = height; //Je r�cup�re la hauteur de ma window

    if(!font.loadFromFile("ressources/police/arial.ttf")) //Je charge ma police d'�criture
    {
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl;;//Msg d'erreur console
    }
    if(!fontTitle.loadFromFile("ressources/police/castlevania.ttf"))//Je charge ma police d'�criture
    {
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl;;//Msg d'erreur console
    }
    if(!backgroundTexture.loadFromFile("ressources/graphics/background.png"))//Je charge mon fond de fen�tre
    {
        std::cout<<"Impossible de charger le background menu"<<std::endl;;//Msg d'erreur console
    }

    /*
        Je pr�pare les textes pour mon menu
    */

    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");

    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");

    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");

    selectedItemIndex = 0; //Item du menu qui est actuellement selectionn�

    title.setString("Quest Plateformer");
    title.setFillColor(sf::Color::White);
    title.setFont(fontTitle);
    title.setCharacterSize(60);
    title.setPosition((this->width/2)-(title.getGlobalBounds().width/2),10);

    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(sf::Vector2f(1.8,1.8));
}

void Menu::update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window, HudLayer& hud)
{
    if(!flagInGame)//Si je ne suis pas en jeu
    {
        switch (event.key.code)//Je fais un switch sur l'event
        {
            case sf::Keyboard::Up: //Si j'appuie sur la fl�che du haut
                MoveUp();//Je bouge sur la case au dessus
                break;
            case sf::Keyboard::Down: //Si j'appuie sur la fl�che du bas
                MoveDown(); //Je descends dans mon menu
                break;
            case sf::Keyboard::Return: //Si j'appuie sur Enter
                switch(selectedItemIndex) //En fonction de l'�l�ment selectionn�
                {
                    case 0:
                        //Je lance jeu
                        flagInGame = true;
                        hud.restartChrono(); //Je red�marre le chrono
                        break;
                    case 1:
                        std::cout << "Options button has been pressed" <<std::endl;
                        flagInGame = false; //Je m'assure que je ne suis pas en jeu avant d'aller dans mon menu option
                        break;
                    case 2:
                        window.close();
                        break;
                    default:break;
                }
            default:break;
        }
    }
}

void Menu::draw(sf::RenderWindow & window){

    window.draw(backgroundSprite); //Je dessine mon fond de fen�tre
    window.draw(title); //Je dessine mon titre

    //Je boucle sur tous mes items menu
    for(int i = 0; i< MAX_NUMBER_OF_ITEMS; i++){
        float calculatedWidthRect = (this->width/2) - 150; //Je calcule le milieu pour mon rectangle
        float calculatedWidthText = (this->width/2) - (menu[i].getGlobalBounds().width/2); //Je calcule le milieu pour mon text
        float calculatedHeight = this->height/(MAX_NUMBER_OF_ITEMS+1)*(i+1); //Je calcule la hauteur pour mes boxs

        rectangle.setPosition(calculatedWidthRect,calculatedHeight - 5 ); //Je set la position de mon rectangle
        menu[i].setPosition(sf::Vector2f(calculatedWidthText,calculatedHeight)); //Je set la position du texte des menus
        menu[i].setFont(font); //Je set le font

        window.draw(rectangle); //Je dessine d'abord le rectangle
        window.draw(menu[i]); //Je dessine ensuite le texte du menu au dessus
    }
}

/*
    Globalement les mouvements permette d'attribuer
    � la variable selectedItemIndex la box sur laquelle elle se trouve
    et de mettre en rouge le menu text sur lequel elle se trouve
*/
void Menu::MoveUp(){
    if(selectedItemIndex - 1 >=0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


