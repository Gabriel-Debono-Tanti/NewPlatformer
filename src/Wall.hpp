#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
    
public:
    RectangleShape Wallbox;
    bool isClimbable = true;
    sf::FloatRect getglobalbounds(){
        return Wallbox.getGlobalBounds();
    }
    int GetY(){
        return Wallbox.getPosition().y;
    }
    int GetX(){
        return Wallbox.getPosition().x;
    }
    Wall(sf::Vector2f size, sf::Color colour){
        Wallbox.setSize(size);
        Wallbox.setFillColor(colour);
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(Wallbox);
    }void setPos(sf::Vector2f pos){
        Wallbox.setPosition(pos);
    }

};


