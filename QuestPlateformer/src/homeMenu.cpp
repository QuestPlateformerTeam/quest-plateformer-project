#include "homeMenu.h"

HomeMenu::HomeMenu()
{
    //ctor
}

HomeMenu::~HomeMenu()
{
    //dtor
}

HomeMenu::HomeMenu(float width, float height)
{
    this->width = width;
    this->height = height;

    if(!font.loadFromFile("ressources/police/arial.ttf"))
    {
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl;;
    }
    if(!fontTitle.loadFromFile("ressources/police/castlevania.ttf"))
    {
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl;;
    }

    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Play");

    menu[1].setColor(sf::Color::White);
    menu[1].setString("Options");

    menu[2].setColor(sf::Color::White);
    menu[2].setString("Exit");

    selectedItemIndex = 0;
}

void HomeMenu::draw(sf::RenderWindow & window){

    sf::Text title;
    title.setString("Quest Plateformer");
    title.setColor(sf::Color::White);
    title.setFont(fontTitle);
    title.setCharacterSize(60);
    title.setPosition((this->getWidth()/2)-(title.getGlobalBounds().width/2),10);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);
    window.draw(title);


    for(int i = 0; i< MAX_NUMBER_OF_ITEMS; i++){
        float calculatedWidthRect = (this->getWidth()/2) - 150;
        float calculatedWidthText = (this->getWidth()/2) - (menu[i].getGlobalBounds().width/2);
        float calculatedHeight = this->getHeight()/(MAX_NUMBER_OF_ITEMS+1)*(i+1);

        rectangle.setPosition(calculatedWidthRect,calculatedHeight - 5 );
        menu[i].setPosition(sf::Vector2f(calculatedWidthText,calculatedHeight));
        menu[i].setFont(font);

        window.draw(rectangle);
        window.draw(menu[i]);
    }
}

void HomeMenu::MoveUp(){
    if(selectedItemIndex - 1 >=0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void HomeMenu::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

float HomeMenu::getWidth()
{
    return this->width;
}

float HomeMenu::getHeight()
{
    return this->height;
}

