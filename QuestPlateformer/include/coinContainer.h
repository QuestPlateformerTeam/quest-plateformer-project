#ifndef COINCONTAINER_H
#define COINCONTAINER_H
#include <vector>
#include "coin.h"
#include <SFML/Graphics.hpp>

class CoinContainer
{
    public:
        CoinContainer();
        virtual ~CoinContainer();
        void draw(sf::RenderWindow& window);
        void changeToNextCoin();
        int getNbCoin();
        sf::Sprite getOneCoin(int i);
        Coin& getThisCoin(int i);

    protected:

    private:
        std::vector<Coin*> coinList;
        const int NB_COIN = 3;
        int currentCoinToDisplay = 0;
};

#endif // COINCONTAINER_H
