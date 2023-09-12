#pragma once


#include <iostream>
#include "SFML/Graphics.hpp"
#include "Coin.h"
#include "Entity.hpp"
#include "Wall.hpp"
using namespace sf;
class Player {
private:
   
    int gravitySpeed = 6;
    float jumpTime = 3.f; 
    bool canJump = true;
    bool isClimbing = false;
    float climbSpeed = 2.0f;
    bool canWallJump = true; 
    float wallJumpCooldown = 1.0f;

public:
 sf::RectangleShape player;
    Player(sf::Vector2f size, sf::Color colour) {
        player.setSize(size);
        player.setFillColor(colour);
        player.setOrigin(player.getSize().x / 2, player.getSize().y / 2);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(player);
    }

    void move(sf::Vector2f distance) {
        player.move(distance);
    }

    void setPosition(sf::Vector2f pos) {
        player.setPosition(pos);
    }

    bool isCollidingWithCoin(Coin *coin) {
        if (player.getGlobalBounds().intersects(coin->getglobalbounds())) {
            return true;
        }
        return false;
    }

    void handleWallCollisions(const std::vector<Wall>& walls) {
        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
            sf::FloatRect playerBounds = player.getGlobalBounds();

            if (playerBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                playerBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (playerBounds.left < wallBounds.left) {
                        player.setPosition(player.getPosition().x - overlap.width + 0.1f, player.getPosition().y);
                      
                        
                        
                        
                    } else {
                        player.setPosition(player.getPosition().x + overlap.width -0.1f, player.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (playerBounds.top < wallBounds.top) {
                        player.setPosition(player.getPosition().x, player.getPosition().y - overlap.height);
                        canJump = true;
                        jumpTime = 3.f; 
                    } else {
                        player.setPosition(player.getPosition().x, player.getPosition().y + overlap.height);
                    }
                }
            }
        }
    }
     
       

    void handleInput() {
        if (!isClimbing) {
            move(sf::Vector2f(0, gravitySpeed));
            move(sf::Vector2f((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) * 2, 0));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (canJump || jumpTime > 0) {
                    move(sf::Vector2f(0, -35));
                    canJump = false;
                    jumpTime--;
                }
            }
        } else {
            
                move(sf::Vector2f(0, (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) * climbSpeed));
        }
    }
    void handleClimbing(const std::vector<Wall>& walls) {
        if (!isClimbing) {
            
            for (const Wall& wall : walls) {
                sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
                sf::FloatRect playerBounds = player.getGlobalBounds();

                if (playerBounds.intersects(wallBounds) && wall.isClimbable && Keyboard::isKeyPressed(Keyboard::LShift)) {
                    isClimbing = true;
                    break; }
            }
        } else {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                
                move(sf::Vector2f(0, -climbSpeed));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
               
                move(sf::Vector2f(0, climbSpeed));
            } else {
                
                isClimbing = false;
            }
            for (const Wall& wall : walls) {
                sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
                sf::FloatRect playerBounds = player.getGlobalBounds();

                if (playerBounds.intersects(wallBounds) && wall.isClimbable && Keyboard::isKeyPressed(Keyboard::LShift)) {
                    isClimbing = true;
                    break; 
                }else if(!playerBounds.intersects(wallBounds) && wall.isClimbable && Keyboard::isKeyPressed(Keyboard::LShift)){
                     
                    isClimbing =false;
                }
            }
        }
    }
    
};


