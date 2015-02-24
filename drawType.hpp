/*
 The MIT License (MIT)

 Copyright (c) 2015 Joshua Trahan

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifndef DRAWTYPE_H
#define DRAWTYPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

/*
 0. Player Right
 1. Player Up
 2. Player Left
 3. Player Down
 4. Enemy Right
 5. Enemy Up
 6. Enemy Left
 7. Enemy Down
 8. Floor
 9. Wall
*/

class drawType{
public:
    drawType(int const nVertLevelSize, int const nHorizLevelSize,
             int const nNumOfEnemies, char nLevelArray[80][25],
             enemyType *nEnemyArray[25], playerType *nPlayer)
    :window(sf::VideoMode(1280, 720), "Soliton has TILES!!! At least, technically, it does.",
            sf::Style::Default)
    {
        pixelSize = 32;

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

        for (int i = 0; i < 4; i++){
            if (!texPlayer[i].loadFromFile( resourcePath() + std::to_string(i) + ".png")){
                cout << to_string(i) << " player texture failed to load\n";
            }
        }

        for (int i = 4; i < 8; i++){

            if (!texEnemy[i - 4].loadFromFile( resourcePath() + std::to_string(i) + ".png")){
                cout << to_string(i) << " enemy texture failed to load\n";
            }
        }

        for (int i = 8; i < 10; i++){
            if (!texLevel[i - 8].loadFromFile( resourcePath() + std::to_string(i) + ".png")){
                cout << to_string(i) << " level texture failed to load\n";
            }
        }

        // Setting tile textures
        for (int y = 0; y < 25; y++){
            for (int x = 0; x < 80; x++){
                if (levelArray[x][y] == '.'){
                    spriteLevel[x][y].setTexture(texLevel[0]);
                }
                else{
                    spriteLevel[x][y].setTexture(texLevel[1]);
                }
                spriteLevel[x][y].setPosition((float)(x * pixelSize),
                                              (float)(y * pixelSize));
            }
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
                    return '=';
                    break;
            };
        }
        return '=';
    }

    void setTextures(){
        int pX = player->getXCoord();
        int pY = player->getYCoord();

        int enemyXCoords[numOfEnemies];
        int enemyYCoords[numOfEnemies];

        for (int i = 0; i < numOfEnemies; i++){
            enemyXCoords[i] = enemyArray[i]->getXCoord();
            enemyYCoords[i] = enemyArray[i]->getYCoord();
        }

        int textureNumber;

        int playerHeading = player->getHeading();

        cout << "playerHeading: " << playerHeading << endl;

        switch (playerHeading){
            case 0:
                textureNumber = 0;
                break;
            case 1:
                textureNumber = 1;
                break;
            case 2:
                textureNumber = 2;
                break;
            case 3:
                textureNumber = 3;
                break;
            default:
                textureNumber = 0;
                cout << "Error setting correct player texture\n";
                break;
        };

        spritePlayer.setTexture(texPlayer[textureNumber]);
        spritePlayer.setPosition((float)(pX * pixelSize),
                                 (float)(pY * pixelSize));

        for (int i = 0; i < numOfEnemies; i++){
            int enemyHeading = enemyArray[i]->getHeading();

            cout << "enemyHeading: " << enemyHeading << endl;

            switch (enemyHeading){
                case 0:
                    textureNumber = 0;
                    break;
                case 1:
                    textureNumber = 1;
                    break;
                case 2:
                    textureNumber = 2;
                    break;
                case 3:
                    textureNumber = 3;
                    break;
                default:
                    textureNumber = 0;
                    cout << i << " Error setting correct enemy texture\n";
                    break;
            }

            spriteEnemy[i].setTexture(texEnemy[textureNumber]);
            spriteEnemy[i].setPosition((float)(enemyXCoords[i] * pixelSize),
                                       (float)(enemyYCoords[i] * pixelSize));

        }

        // Drawing the level - make sure to only redraw a sprite or re-set a
        // texture when it needs to change, players and enemies excluded.
    }

    int drawScreen(){
        if (window.isOpen()){
            window.clear();

            for (int y = 0; y < 25; y++){
                for (int x = 0; x < 80; x++){
                    window.draw(spriteLevel[x][y]);
                }
            }

            window.draw(spritePlayer);

            for (int i = 0; i < numOfEnemies; i++){
                window.draw(spriteEnemy[i]);
            }

            window.display();
            return 0;
        }
        return 0;
    }


private:

    int pixelSize;
    int vertLevelSize;
    int horizLevelSize;
    int numOfEnemies;
    char levelArray[80][25];
    playerType *player;

    sf::Sprite spriteArray;

    enemyType *enemyArray[25];

    // left right up down
    sf::Texture texEnemy[4];
    sf::Texture texPlayer[4];

    // floor wall
    sf::Texture texLevel[2];

    sf::Sprite spriteEnemy[25];
    sf::Sprite spritePlayer;
    sf::Sprite spriteLevel[80][25];

    sf::RenderWindow window;
};

#endif
