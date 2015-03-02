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

#ifndef ENEMYTYPE_H
#define ENEMYTYPE_H

using namespace std;

struct actionType{
	char action;
	char direction;
};

class enemyType{
public:
	void moveUp(){
		yCoord--;
		heading = 1;
	}
	void moveDown(){
		yCoord++;
		heading = 3;
	}
	void moveLeft(){
		xCoord--;
		heading = 2;
	}
	void moveRight(){
		xCoord++;
		heading = 0;
	}
	int getXCoord(){
		return xCoord;
	}
	int getYCoord(){
		return yCoord;
	}
	char toDisplay(){
		if (!checkIfAlive()){
			return 'x';
		}
		if (heading == 2)
			return '>';
		else if (heading == 0)
			return '<';
		else if (heading == 1)
			return 'v';
		else if (heading == 3)
			return '^';
		else
			return 'O';
	}
	
	void setPosition(int x, int y, int headingSet){
		xCoord = x;
		yCoord = y;
		heading = headingSet;
	}
	
	bool checkRight(char levelArray[80][25], int pX, int pY) const{
		// Return false if player is behind enemy
		if (pX < xCoord){
			return false;
		}
		
		int xOffset = pX - xCoord;
		int yOffset = pY - yCoord;
		
		if (xOffset == 0){
			return false;
		}
		if (abs(xOffset) > 4 || abs(yOffset) > 4){
			return false;
		}
		if (abs(xOffset) == 1 && abs(yOffset) != 0){
			return false;
		}
		
		double slope = (double)yOffset / (double)xOffset;
		cout << "Right Slope: " << slope << endl;
		
		// Quick hack to make hiding behind walls more forgiving
		if (levelArray[pX - 1][pY] != '.'){
			return false;
		}
		
		// Drawing line toward player to see if the enemy should see them.
		// Returns false if line hits a wall.
		// 
		// Note to self: instead of hacky shit 15 or so lines up, possibly
		// 	put (y += (x * slope)) before (x++)
		for (int y = 0, x = 0; x <= 4; x++, y += (x * slope)){
			if (levelArray[xCoord + x][yCoord + y] != '.'){
				return false;
			}
			if (xCoord + x == pX && yCoord + y == pY){
				return true;
			}
		}
		return false;
	}

	bool checkLeft(char levelArray[80][25], int pX, int pY) const{
		// Return false if player is behind enemy
		if (pX > xCoord){
			return false;
		}
		
		int xOffset = pX - xCoord;
		int yOffset = pY - yCoord;
		
		if (xOffset == 0){
			return false;
		}
		if (xOffset > 4 || yOffset > 4){
			return false;
		}
		if (abs(xOffset) == 1 && abs(yOffset) != 0){
			return false;
		}
		
		double slope = (double)yOffset / (double)xOffset;
		
		// Quick hack to make hiding behind walls more forgiving
		if (levelArray[pX + 1][pY] != '.'){
			return false;
		}
		
		// Drawing line toward player to see if the enemy should see them.
		// Returns false if line hits a wall.
		for (int y = 0, x = 0; x >= -4; x--, y += (x * slope)){
			if (levelArray[xCoord + x][yCoord + y] != '.'){
				return false;
			}
			if (xCoord + x == pX && yCoord + y == pY){
				return true;
			}
		}
		return false;
	}

	bool checkUp(char levelArray[80][25], int pX, int pY) const{
		// Return false if player is behind enemy
		if (pY > yCoord){
			return false;
		}
		
		int xOffset = pX - xCoord;
		int yOffset = pY - yCoord;
		
		if (yOffset == 0){
			return false;
		}
		if (xOffset > 4 || yOffset > 4){
			return false;
		}
		if (abs(yOffset) == 1 && abs(xOffset) != 0){
			return false;
		}
		
		double slope = (double)xOffset / (double)yOffset;
		
		// Quick hack to make hiding behind walls more forgiving
		if (levelArray[pX][pY - 1] != '.'){
			return false;
		}
		
		// Drawing line toward player to see if the enemy should see them.
		// Returns false if line hits a wall.
		for (int y = 0, x = 0; y >= -4; y--, x += (y * slope)){
			if (levelArray[xCoord + x][yCoord + y] != '.'){
				return false;
			}
			if (xCoord + x == pX && yCoord + y == pY){
				return true;
			}
		}
		return false;
	}

	bool checkDown(char levelArray[80][25], int pX, int pY) const{
		// Return false if player is behind enemy
		if (pY < yCoord){
			return false;
		}
		
		int xOffset = pX - xCoord;
		int yOffset = pY - yCoord;
		
		if (yOffset == 0){
			return false;
		}
		if (xOffset > 4 || yOffset > 4){
			return false;
		}
		if (abs(yOffset) == 1 && abs(xOffset) != 0){
			return false;
		}
		
		double slope = (double)xOffset / (double)yOffset;
		
		// Quick hack to make hiding behind walls more forgiving
		if (levelArray[pX][pY + 1] != '.'){
			return false;
		}
		
		// Drawing line toward player to see if the enemy should see them.
		// Returns false if line hits a wall.
		for (int y = 0, x = 0; y <= 4; y++, x += (y * slope)){
			if (levelArray[xCoord + x][yCoord + y] != '.'){
				return false;
			}
			if (xCoord + x == pX && yCoord + y == pY){
				return true;
			}
		}
		return false;
	}

	bool checkForPlayer(char levelArray[80][25], int pX, int pY){
		if (xCoord == pX && yCoord == pY){
			return 1;
		}
		
		// just need to have return(checkDirection()), will fix later.
		// All this sight code is hacky garbage. 
		// I'm sorry to whoever reads this.
		switch(heading){
			case 0:
				if (checkRight(levelArray, pX, pY))
					return 1;
				else
					return 0;
				break;
			case 2:
				if (checkLeft(levelArray, pX, pY))
					return 1;
				else
					return 0;
				break;
			case 3:
				if (checkDown(levelArray, pX, pY))
					return 1;
				else
					return 0;
				break;
			case 1:
				if (checkUp(levelArray, pX, pY))
					return 1;
				else
					return 0;
				break;
			default:
				return 0;
		}
		return 0;
	}
	
	void moveAlongPath(){
		char direction = patrolPath[pathLoc].direction;
		char action = patrolPath[pathLoc].action;
		
		if (action == 'm'){
			switch (direction){
				case 'l':
					moveLeft();
					break;
				case 'r':
					moveRight();
					break;
				case 'u':
					moveUp();
					break;
				case 'd':
					moveDown();
					break;
				default:
					cout << "OH GOD";
			}
		}
		if (action == 'l'){
			switch (direction){
				case 'l':
					heading = 2;
					break;
				case 'r':
					heading = 0;
					break;
				case 'u':
					heading = 1;
					break;
				case 'd':
					heading = 3;
					break;
				default:
					cout << "OH GOD";
                    heading = 0;
			}
		}	
		if (patrolPath[pathLoc + 1].action == '$')
			pathLoc = 0;
		else
			pathLoc++;
	}

	void loadPatrolPath(ifstream &levelFile){
        for (int i = 0; i < 100; i++){
            patrolPath[i].action = '$';
            patrolPath[i].direction = '$';
        }
        
		char currentChar = levelFile.get();
        int i = 0;
        
        cout << currentChar << '\n';
        
        do{
            if (currentChar == ' ' || currentChar == '\n' || currentChar == '$'
                || currentChar == '#'){
                cout << currentChar << '\n';
                currentChar = levelFile.get();
                continue;
            }
            
            cout << currentChar << '\n';
            patrolPath[i].action = currentChar;
            currentChar = levelFile.get();
            
            cout << currentChar << '\n';
            patrolPath[i].direction = currentChar;
            currentChar = levelFile.get();
            
            i++;
        } while (currentChar != '\n' && !levelFile.eof());
	}
	
	bool checkIfAlive(){
		return isAlive;
	}
	
	void killEnemy(){
		isAlive = 0;
		return;
	}
    
    int getHeading(){
        return heading;
    }
    
    string getIcon(){
        switch(heading){
            case 0:
                return "eright.png";
                break;
            
            case 1:
                return "eup.png";
                break;
                
            case 2:
                return "eleft.png";
                break;
                
            case 3:
                return "edown.png";
                break;
                
            default:
                return "eright.png";
        };
    }
	
    enemyType(int xSet = 3, int ySet = 3, int heading = 0){
		xCoord = xSet;
		yCoord = ySet;
		pathLoc = 0;
		isAlive = 1;
		for (int i = 0; i < 100; i++){
			patrolPath[i].action = '$';
			patrolPath[i].direction = '$';
		}
	}
	
private:
	int xCoord;
	int yCoord;
	actionType patrolPath[100];
	int pathLoc;
	int heading;
	bool isAlive;
};

#endif
