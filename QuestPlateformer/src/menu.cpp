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

    title.setString("Quest Plateformer");
    title.setColor(sf::Color::White);
    title.setFont(fontTitle);
    title.setCharacterSize(60);
    title.setPosition((this->width/2)-(title.getGlobalBounds().width/2),10);

    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);
}

void Menu::update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window)
{
    if(!flagInGame)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Up:
                MoveUp();
                break;
            case sf::Keyboard::Down:
                MoveDown();
                break;
            case sf::Keyboard::Return:
                switch(GetPressedItem())
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

void Menu::draw(sf::RenderWindow & window){

    window.draw(title);
    for(int i = 0; i< MAX_NUMBER_OF_ITEMS; i++){
        float calculatedWidthRect = (this->width/2) - 150;
        float calculatedWidthText = (this->width/2) - (menu[i].getGlobalBounds().width/2);
        float calculatedHeight = this->height/(MAX_NUMBER_OF_ITEMS+1)*(i+1);

        rectangle.setPosition(calculatedWidthRect,calculatedHeight - 5 );
        menu[i].setPosition(sf::Vector2f(calculatedWidthText,calculatedHeight));
        menu[i].setFont(font);

        window.draw(rectangle);
        window.draw(menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >=0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}


