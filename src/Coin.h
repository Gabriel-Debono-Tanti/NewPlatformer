#pragma once


#include <iostream>
#include "SFML/Graphics.hpp"

class Coin
{
private:
    sf::RectangleShape coin;
public:
    Coin(sf::Vector2f size, sf::Color colour){
        coin.setSize(size);
        coin.setFillColor(colour);
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(coin);
    }
    sf::FloatRect getglobalbounds(){
        return coin.getGlobalBounds();
    }
    void setPos(sf::Vector2f pos){
        coin.setPosition(pos);
    }
    
};



