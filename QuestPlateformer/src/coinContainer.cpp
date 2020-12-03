#include "coinContainer.h"

CoinContainer::CoinContainer()
{
    for(int i =0; i<=NB_COIN; i++)
    {
        coinList.push_back(new Coin(100,100+i*100));
    }
}

CoinContainer::~CoinContainer()
{
    //dtor
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

