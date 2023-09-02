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
#include <json.hpp>
using json = nlohmann::json;
using namespace std;
using namespace sf;


vector<Entity> entities;
ifstream f("./level.json");
json level = json::parse(f);


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Player p(Vector2f(10, 10), Color::White);
    Wall floor(Vector2f(200, 200), Color::White);
    Wall ceiling(Vector2f(200, 100), Color::White);
    vector<Wall> walls;
    vector<Sprite> tilemap;
    View view;
    view.setCenter(p.player.getOrigin().x, p.player.getOrigin().y);

   



    int posy = 0;
    int posx = 0;
    
     Texture t7;
    t7.loadFromFile("Textures/7.png");
    Texture t1;
    t1.loadFromFile("Textures/1.png");
    Texture t2;
    t2.loadFromFile("Textures/2.png");
    Texture t3;
    t3.loadFromFile("Textures/3.png");
    Texture t4;
    t4.loadFromFile("Textures/4.png");
    Texture t5;
    t5.loadFromFile("Textures/5.png");
    Texture t6;
     t6.loadFromFile("Textures/6.png");
    Texture t8;
    t8.loadFromFile("Textures/8.png");
    for(const auto& element : level["layers"][0]["data"]){
        int value = element.get<int>();
        
        
        if(posx == 2048){
                posx = 0;
                posy += 32;
                
            }
        
        if(value == 0){
            posx += 32;
        }
        if(value == 7){
             Sprite tile;
           
            tile.setTexture(t7);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }
         if(value == 1){
             Sprite tile;
             
            tile.setTexture(t1);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }  
         if(value == 2){
             Sprite tile;
             
            tile.setTexture(t2);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }      

         if(value == 3){
             Sprite tile;
             
            tile.setTexture(t3);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }  
          if(value == 4){
             Sprite tile;
             
            tile.setTexture(t4);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }  
         if(value == 5){
             Sprite tile;
           
            tile.setTexture(t5);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        } 
         if(value == 6){
            
             Sprite tile;
           
            tile.setTexture(t6);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }
         if(value == 8){
             Sprite tile;
           
            tile.setTexture(t8);
            
            tile.setPosition(Vector2f(posx, posy));
            
            tilemap.push_back(tile);
             posx += 32;  
        }       
    }
    for(const auto& element : level["layers"][1]["objects"]){

        Wall wall(Vector2f(element["width"], element["height"]), Color::Transparent);
        wall.setPos(Vector2f(element["x"], element["y"]));
        walls.push_back(wall);
    }
    p.setPos(Vector2f(40, 50));
    
    while (window.isOpen())
    {
        
        p.input();
        floor.setPos(Vector2f(20, 300));
        ceiling.setPos(Vector2f(20, 100));
       
       walls.push_back(ceiling);
       walls.push_back(floor);
       view.setCenter(p.player.getOrigin().x, p.player.getOrigin().y);
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
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
        p.jumptime = 2;
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
         for(auto tile : tilemap){
            window.draw(tile);
        }
        window.display();
        
    }

    return 0;
}
