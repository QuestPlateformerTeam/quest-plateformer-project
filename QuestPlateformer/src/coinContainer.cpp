#include "coinContainer.h"

CoinContainer::CoinContainer(Map& map)
{
    loadConfig(map);
}

CoinContainer::~CoinContainer()
{
    //dtor
}
/*
    =================
    Getters & Setters
    =================
*/
void CoinContainer::setLooted(bool b){flagAllCoinLoot = false;}
Coin& CoinContainer::getThisCoin(int i){return *coinList.at(i);}
int CoinContainer::getNbCoin(){return NB_COIN;}

void CoinContainer::changeToNextCoin(){currentCoinToDisplay = currentCoinToDisplay +1;}
sf::Sprite CoinContainer::getOneCoin(int i){return coinList.at(i)->getCoin();}
void CoinContainer::resetAll(){currentCoinToDisplay=0;}
bool CoinContainer::isAllLooted(){return flagAllCoinLoot;}

void CoinContainer::loadConfig(Map& map)
{
    coinList.clear();
    int pos[8];
    std::fstream myFile("ressources/maps/map"+std::to_string(map.getLevel())+"Config.txt", std::ios_base::in); //Je charge mon fichier config en rapport avec la map
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
        coinList.push_back(new Coin(pos[i],pos[i+1])); //Je push les valeurs dans
}

void CoinContainer::draw(sf::RenderWindow& window)//va dessiner les pièces uniquement si elles affichables
{
    if(currentCoinToDisplay < NB_COIN)//Je vérifie en fonction des pièces à afficher
    {
        for(int i =0; i<NB_COIN; i++) //Je boucle sur mes pièces
        {
            if(i == currentCoinToDisplay) //Si la pièce du vecteur est la pièce à afficher
                coinList.at(i)->changeDisplay(true); //Alors je set en true
            else//Sinon
                coinList.at(i)->changeDisplay(false);//Je set en false

            if(coinList.at(i)->getDisplay())//Je vérifie si je dois afficher la pièce
                coinList.at(i)->draw(window);//Si oui, je l'affiche
        }
    }
    else
        flagAllCoinLoot = true;
}


