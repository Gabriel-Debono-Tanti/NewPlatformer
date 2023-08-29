#pragma once


#include <iostream>
#include "SFML/Graphics.hpp"
#include "Coin.h"
#include "Entity.hpp"
#include "Wall.hpp"
using namespace sf;
class Player
{
private:

public:
sf::RectangleShape player;
int gravityspeed = 4;
float jumptime = 3;
bool canjump = false;
    


    Player(sf::Vector2f size, sf::Color colour){
        player.setSize(size);
        player.setFillColor(colour);
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(player);
    }
    void move(sf::Vector2f distance){
        player.move(distance);
    }
    void setPos(sf::Vector2f pos){
        player.setPosition(pos);
    }
    int GetY(){
        return player.getPosition().y;
    }
    bool iscollidingwithcoin(Coin *coin){
        if(player.getGlobalBounds().intersects(coin->getglobalbounds())){
            return true;
        }
        return false;
    }
    void input(){
        move(Vector2f(0, gravityspeed));
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            move(Vector2f(2,0));
            
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            
            move(Vector2f(-2,0));
            
        }
        if(Keyboard::isKeyPressed(Keyboard::Space)){
            if(canjump == true || jumptime > 0){
                move(Vector2f(0,-10));
                jumptime -= 0.1f;
                canjump = false;
                
            }
            
            
        }
      
    }
    
   
};


