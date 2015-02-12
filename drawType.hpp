#ifndef DRAWTYPE_H
#define DRAWTYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class drawType{
public:
    drawType(int nVertLevelSize, int nHorizLevelSize, int nNumOfEnemies,
             char &nLevelArray)
    :window(sf::VideoMode(320, 240), "Soliton has TILES!!!",
            sf::Style::Default)
    {
        
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
        }
    }

private:
    int loadTextures(){
        return 0;
    }
    
    sf::RenderWindow window;
};

#endif