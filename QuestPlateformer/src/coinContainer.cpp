#include "coinContainer.h"

CoinContainer::CoinContainer(Map& map)
{
    loadConfig(map);
}

CoinContainer::~CoinContainer()
{
    //dtor
}

void CoinContainer::loadConfig(Map& map)
{
    coinList.clear();
    int pos[8];
    std::fstream myFile("ressources/maps/map"+std::to_string(map.getLevel())+"Config.txt", std::ios_base::in);
    std::string Line;

    if(myFile.is_open())
    {
        for (int i = 0; i <= NB_COIN *2 -1 ; i++) //Récupère les valeurs pour chaque tuile
        {
            getline(myFile,Line,','); //Récupère les valeurs une par une séparée par le délimiteur ','
            std::stringstream iss;
            iss << Line; //Stocke les caractères dans un stream
            iss >> pos[i]; //Renvoie le stream en un int dans l'array
        }
        myFile.close();
    }
    else
        std::cout<<"Erreur chargement mapConfig"<<std::endl;

    for (int i = 0; i<=NB_COIN*2; i+=2)
    {
            coinList.push_back(new Coin(pos[i],pos[i+1]));
    }
}

void CoinContainer::draw(sf::RenderWindow& window)
{
    if(currentCoinToDisplay < NB_COIN)
    {
        for(int i =0; i<=NB_COIN; i++)
        {
            if(i == currentCoinToDisplay)
                coinList.at(i)->changeDisplay(true);
            else
                coinList.at(i)->changeDisplay(false);

            if(coinList.at(i)->getDisplay())
                coinList.at(i)->draw(window);
        }
    }
    else
        flagAllCoinLoot = true;
}

void CoinContainer::changeToNextCoin()
{
    currentCoinToDisplay = currentCoinToDisplay +1;
}

int CoinContainer::getNbCoin()
{
    return NB_COIN;
}

sf::Sprite CoinContainer::getOneCoin(int i)
{
    return coinList.at(i)->getCoin();
}

Coin& CoinContainer::getThisCoin(int i)
{
    return *coinList.at(i);
}

void CoinContainer::resetAll()
{
    currentCoinToDisplay=0;
}

bool CoinContainer::isAllLooted()
{
    return flagAllCoinLoot;
}

void CoinContainer::setLooted(bool b)
{
    flagAllCoinLoot = false;
}

