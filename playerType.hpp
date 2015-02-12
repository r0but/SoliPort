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

#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

using namespace std;

class playerType{
public:
	void moveUp(){
		yCoord -= 1;
	}
	void moveDown(){
		yCoord += 1;
	}
	void moveLeft(){
		xCoord -= 1;
	}
	void moveRight(){
		xCoord += 1;
	}
	
	void move(char input, char levelArray[80][25]){
		if (input == 'w' && (levelArray[xCoord][yCoord - 1] == '.' ||
						     levelArray[xCoord][yCoord - 1] == 'E'))
			moveUp();
		else if (input == 's' && (levelArray[xCoord][yCoord + 1] == '.' || 
								  levelArray[xCoord][yCoord + 1] == 'E'))
			moveDown();
		else if (input == 'a' && (levelArray[xCoord - 1][yCoord] == '.' || 
								  levelArray[xCoord - 1][yCoord] == 'E'))
			moveLeft();
		else if (input == 'd' && (levelArray[xCoord + 1][yCoord] == '.' ||
								  levelArray[xCoord + 1][yCoord] == 'E'))
			moveRight();
	}
	int getXCoord(){
		return xCoord;
	}
	int getYCoord(){
		return yCoord;
	}
	void setPosition(int xSet, int ySet){
		xCoord = xSet;
		yCoord = ySet;
	}
	char getIcon(){
		return icon;
	}
	void setAmmoCount(int ammoSet){
		if (ammoSet >= 0)
			ammoLeft = ammoSet;
		else
			ammoLeft = 0;
		return;
	}
	void addToAmmoCount(int ammoAdd){
		if (ammoAdd >= 0)
			ammoLeft += ammoAdd;
		return;
	}
	void decrementAmmoCount(){
		if (ammoLeft > 0){
			ammoLeft--;
		}
        return;
	}
	
	int getAmmoCount(){
		return ammoLeft;
	}
	
	playerType(int xSet = 10, int ySet = 10, int ammo = 0){
		xCoord = xSet;
		yCoord = ySet;
		ammoLeft = ammo;
		icon = '@';
	}	
private:
	int xCoord;
	int yCoord;
	char icon;
	int ammoLeft;
};

#endif
