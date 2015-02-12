#ifndef DRAWTYPE_H
#define DRAWTYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class drawType{
public:
    drawType(int nVertLevelSize, int nHorizLevelSize, int nNumOfEnemies,
             char nLevelArray[80][25], enemyType nEnemyArray[25],
             playerType nPlayer)
    :window(sf::VideoMode(640, 480), "Soliton has TILES!!! Wait, actually it doesn't.",
            sf::Style::Default)
    {
        vertLevelSize = nVertLevelSize;
        horizLevelSize = nHorizLevelSize;
        player = nPlayer;
        numOfEnemies = nNumOfEnemies;
        
        for (int y = 0; y < 25; y++){
            for (int x = 0; x < 80; x++){
                levelArray[x][y] = nLevelArray[x][y];
            }

        }
        
        for (int i = 0; i < 25; i++){
            enemyArray[i] = nEnemyArray[i];
        }
        
        return;
    }
    
    char getInput(){
        sf::Event event;
        
        while (window.waitEvent(event)){
            
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    return 'q';
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::D)
                        return 'd';
                    else if (event.key.code == sf::Keyboard::S)
                        return 's';
                    else if (event.key.code == sf::Keyboard::A)
                        return 'a';
                    else if (event.key.code == sf::Keyboard::W)
                        return 'w';
                    else if (event.key.code == sf::Keyboard::Q)
                        return 'q';
                    break;
                
                default:
                    break;
            };
        }
    }
    
    int drawScreen(){
        if (window.isOpen()){
            window.clear();
            
            
            
            window.display();
            return;
        }
        return;
    }

private:
    int loadTextures(){
        return 0;
    }
    
    int vertLevelSize;
    int horizLevelSize;
    int numOfEnemies;
    char levelArray[80][25];
    enemyType enemyArray[25];
    playerType player;
    
    sf::RenderWindow window;
};

#endif
