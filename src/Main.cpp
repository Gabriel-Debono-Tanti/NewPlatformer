#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Entity.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;
using namespace sf;


vector<Entity> entities;
vector<int> tilemap1= {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 100,
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
    1, 100, 
     1, 100, 
    
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 100,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Player p(Vector2f(10, 10), Color::White);
    Wall floor(Vector2f(200, 200), Color::White);
    Wall ceiling(Vector2f(200, 100), Color::White);
    vector<Wall> walls;
    
    int posy = 0;
    int posx = 0;
    for(int i = 0; i < tilemap1.size(); i++){
        
       
        
        if(tilemap1[i] == 100){
                posx = 0;
                posy += 32;
                
            }
        
        
        if(tilemap1[i] == 1){
             Wall tile(Vector2f(32,32), Color::White);
            
            
            tile.setPos(Vector2f(posx, posy));
            
            walls.push_back(tile);
             posx += 32;  
        }
           
            

        
         
            
    }
    p.setPos(Vector2f(40, 50));
    cout << walls.size();
    while (window.isOpen())
    {
        p.input();
        floor.setPos(Vector2f(20, 300));
        ceiling.setPos(Vector2f(20, 100));
       
       walls.push_back(ceiling);
       walls.push_back(floor);
        
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
    for (const Wall& wall : walls) {
    sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
    sf::FloatRect playerBounds = p.player.getGlobalBounds();
    
    if (playerBounds.intersects(wallBounds)) {
        sf::FloatRect overlap;
        playerBounds.intersects(wallBounds, overlap);

        if (overlap.width < overlap.height) {
            if (playerBounds.left < wallBounds.left) {
                p.player.setPosition(p.player.getPosition().x - overlap.width, p.player.getPosition().y);
            } else {
                p.player.setPosition(p.player.getPosition().x + overlap.width, p.player.getPosition().y);
            }
        } else {
            if (playerBounds.top < wallBounds.top) {
                p.player.setPosition(p.player.getPosition().x, p.player.getPosition().y - overlap.height);
                 p.canjump = true;
                p.jumptime= 2;
            } else {
                p.player.setPosition(p.player.getPosition().x, p.player.getPosition().y + overlap.height);
               
            }
        }
    }
}
        window.setVerticalSyncEnabled(true); 
        window.setFramerateLimit(60);
        window.clear(Color::Black);
        p.drawTo(window);
        
        for(auto wall : walls){
            wall.drawTo(window);
        }
        window.display();
        
    }

    return 0;
}
