/*
 The MIT License (MIT)

 Copyright (c) 2014 Joshua Trahan

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

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include "winResourcePath.hpp"
#elif __APPLE__
#include "ResourcePath.hpp"
#endif

#include "levelType.hpp"

using namespace std;

void drawWinScreen(){
    for (int i = 0; i < 25; i++){
        cout << endl;
    }

    cout << "Congratulate! You are winner!" << endl;
}

void drawLossScreen(){
    cout << endl << "You lose! Good day, sir." << endl;
}

// Exit codes:
// 0: Success
// 1: Error
// 2: Shut down everything
int gameLoop(levelType level){
    char userInput;
    while(true){

        // winOrLose - 0 means game isn't finished, 1 means win, 2 means loss
        int winOrLose = 0;

        level.drawMap();
        level.sfmlHandler->setTextures();
        level.sfmlHandler->drawScreen();

        userInput = level.sfmlHandler->getInput();

        if (userInput == 'q')
            break;
        else if (userInput == '!'){
            return 2;
        }
        else
            winOrLose = level.iterateMap(userInput);
        cout << endl << endl;

        if (winOrLose == 1){
            level.drawMap();
            level.sfmlHandler->setTextures();
            level.sfmlHandler->drawScreen();
            drawWinScreen();
            break;
        }
        else if (winOrLose == 2){
            level.drawMap();
            level.sfmlHandler->setTextures();
            level.sfmlHandler->drawScreen();
            drawLossScreen();
            break;
        }
    }
    return 0;
}

int main(){
    bool userCont = true;
    string levelName = "";
    bool  restart = false;
    int numOfLevels = 2;
    levelType* level = new levelType();
    for (int currentLevel = 1; currentLevel <= numOfLevels; currentLevel++){
        if (!restart){
            cout << "Enter the filename for the level you want to load: ";
            //cin >> levelName;
        }

        // temporary to string the levels together
        levelName = "level" + to_string(currentLevel) + ".slv";

        ifstream levelFile;
        string levelPath = resourcePath() + levelName;
        levelFile.open(levelPath.c_str());

        if (!levelFile.is_open()){
            cout << "Level not found. Make sure you typed it correctly, ";
            cout << "and that it is in the game's directory." << endl << endl;
            break;
        }

        level->buildLevel(levelFile);

        levelFile.close();

        if (currentLevel == numOfLevels){
            char userChoice = level->sfmlHandler->drawMainMenu();
            if (userChoice == '3'){
                break;
            }
        }
    }

    return 0;
}
