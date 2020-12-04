#include "endGame.h"

EndGame::EndGame(float width, float height)
{
    this->width = width;
    this->height = height;

    if(!font.loadFromFile("ressources/police/arial.ttf"))
    {
        std::cout<<"Impossible de charger la police d'ecriture"<<std::endl;;
    }


    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Play again");

    menu[1].setColor(sf::Color::White);
    menu[1].setString("Back to menu");

    selectedItemIndex = 0;

    title.setString("END GAME");
    title.setColor(sf::Color::White);
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
    window.draw(title);
    chrono.setPosition(sf::Vector2f(this->width/2 - 60, 100 ));
    chrono.setFont(font);
    chrono.setColor(sf::Color::White);
    chrono.setCharacterSize(30);
    window.draw(chrono);
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

void EndGame::update(sf::Event& event, bool& flagInGame, sf::RenderWindow& window,bool& flagEndGame)
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
                switch(selectedItemIndex)
                {
                    case 0:
                        std::cout << "Play button has been pressed" <<std::endl;
                        flagInGame = true;
                        flagEndGame = false;

                        break;
                    case 1:
                        std::cout << "Options button has been pressed" <<std::endl;
                        flagInGame = false;
                        flagEndGame = false;
                        break;
                }
        }
    }
}

void EndGame::MoveUp(){
    if(selectedItemIndex - 1 >=0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void EndGame::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
