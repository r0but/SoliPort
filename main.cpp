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

#include <ResourcePath.hpp>

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

void gameLoop(levelType& level){
    char userInput;
    while(true){
        
        // winOrLose - 0 means game isn't finished, 1 means win, 2 means loss
        int winOrLose = 0;
        
        level.drawMap();
        
        userInput = level.sfmlHandler.getInput();
        
        if (userInput == 'q')
            break;
        else
            winOrLose = level.iterateMap(userInput);
        cout << endl << endl;
        
        if (winOrLose == 1){
            level.drawMap();
            drawWinScreen();
            break;
        }
        else if (winOrLose == 2){
            level.drawMap();
            drawLossScreen();
            break;
        }
    }
}

int main(){
    bool userCont = true;
    string levelName = "";
    bool  restart = false;
    while (userCont){
        if (!restart){
            cout << "Enter the filename for the level you want to load: ";
            cin >> levelName;
        }
        
        ifstream levelFile;
        string levelPath = resourcePath() + levelName;
        levelFile.open(levelPath.c_str());
        
        if (!levelFile.is_open()){
            cout << "Level not found. Make sure you typed it correctly, ";
            cout << "and that it is in the game's directory." << endl << endl;
            continue;
        }
        
        levelType level(levelFile);
        
        levelFile.close();
        
        gameLoop(level);
        
        char cUserCont;
        cout << endl << "Would you like to continue, quit, or restart? "
        << "(c/q/r): ";
        cin >> cUserCont;
        
        if (cUserCont == 'c' || cUserCont == 'C')
            userCont = true;
        else if (cUserCont == 'r' || cUserCont == 'R'){
            restart = true;
            userCont = true;
        }
        else
            userCont = false;
    }
    
    return 0;
}