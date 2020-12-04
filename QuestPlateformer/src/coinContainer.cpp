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
        for (int i = 0; i <= NB_COIN *2 -1 ; i++) //R�cup�re les valeurs pour chaque tuile
        {
            getline(myFile,Line,','); //R�cup�re les valeurs une par une s�par�e par le d�limiteur ','
            std::stringstream iss;
            iss << Line; //Stocke les caract�res dans un stream
            iss >> pos[i]; //Renvoie le stream en un int dans l'array
        }
        myFile.close();
    }
    else
        std::cout<<"Erreur chargement mapConfig"<<std::endl;

    for (int i = 0; i<=NB_COIN*2; i+=2)
        coinList.push_back(new Coin(pos[i],pos[i+1])); //Je push les valeurs dans
}

void CoinContainer::draw(sf::RenderWindow& window)//va dessiner les pi�ces uniquement si elles affichables
{
    if(currentCoinToDisplay < NB_COIN)//Je v�rifie en fonction des pi�ces � afficher
    {
        for(int i =0; i<NB_COIN; i++) //Je boucle sur mes pi�ces
        {
            if(i == currentCoinToDisplay) //Si la pi�ce du vecteur est la pi�ce � afficher
                coinList.at(i)->changeDisplay(true); //Alors je set en true
            else//Sinon
                coinList.at(i)->changeDisplay(false);//Je set en false

            if(coinList.at(i)->getDisplay())//Je v�rifie si je dois afficher la pi�ce
                coinList.at(i)->draw(window);//Si oui, je l'affiche
        }
    }
    else
        flagAllCoinLoot = true;
}


