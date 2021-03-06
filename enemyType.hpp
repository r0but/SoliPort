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
    
	bool checkRight(int pX, int pY){
        
        // Direction specific
        if (pX - xCoord > 4 || pX - xCoord <= 0){
            cout << "pX - xCoord > 4 or <= 0\n";
            return false;
        }
        
        // debug stuff
        cout << "enemy X: " << xCoord << '\n';
        cout << "enemy Y: " << yCoord << '\n';
        cout << "pX: " << pX << '\n';
        cout << "pY: " << pY << '\n';
        
        // Direction specific
        if (levelArray[pX - 1][pY] != '.'){
            cout << "Player next to wall\n";
            return false;
        }
        
        // Can be generalized to left, but will give undefined values if used
        // for up and down. For that I just have to invert.
        float slope = (static_cast<float>(pY) -
                        static_cast<float>(yCoord)) /
                       (static_cast<float>(pX) -
                        static_cast<float>(xCoord));
        
        cout << "Slope: " << slope << '\n';
        
        // Can be generalized
        if (slope > 1.1 || slope < -1.1){
            return false;
        }
        
        // Direction specific
        for (int x = 1; x <= pX - xCoord; x++){
            int y = round(static_cast<float>(x) * slope);
            
            if (levelArray[xCoord + x][yCoord + y] != '.'){
                cout << "Sightline collision with wall at x = " << x << " and "
                     << "y = " << y << '\n';
                
                return false;
            }
        }
        return true;
    }
        
	bool checkUp(int pX, int pY) const{
        
        // Direction specific. Fixed for up
        if (pY - yCoord < -4 || pY - yCoord >= 0){
            cout << "Wrong direction\n";
            return false;
        }
        
        // debug stuff
        cout << "enemy X: " << xCoord << '\n';
        cout << "enemy Y: " << yCoord << '\n';
        cout << "pX: " << pX << '\n';
        cout << "pY: " << pY << '\n';
        
        // Direction specific - fixed for up
        if (levelArray[pX][pY + 1] != '.'){
            cout << "Player next to wall\n";
            return false;
        }
        
        // Can be generalized to left, but will give undefined values if used
        // for up and down. For that I will invert.
        float slope = (static_cast<float>(pX) -
                       static_cast<float>(xCoord)) /
                      (static_cast<float>(pY) -
                       static_cast<float>(yCoord));
        
        cout << "Slope: " << slope << '\n';
        
        // Generalized
        if (slope > 1.1 || slope < -1.1){
            return false;
        }
        
        // Direction specific - fixed for up
        for (int y = -1; y >= pY - yCoord; y--){
            int x = round(static_cast<float>(y) * slope);
            
            if (levelArray[xCoord + x][yCoord + y] != '.'){
                return false;
            }
        }
        return true;
	}

	bool checkLeft(int pX, int pY) const{
        
        // Direction specific. Fixed for left
        if (pX - xCoord < -4 || pX - xCoord >= 0){
            cout << "pX - xCoord > -4 or <= 0\n";
            return false;
        }
        
        // debug stuff
        cout << "enemy X: " << xCoord << '\n';
        cout << "enemy Y: " << yCoord << '\n';
        cout << "pX: " << pX << '\n';
        cout << "pY: " << pY << '\n';
        
        // Direction specific - fixed for left
        if (levelArray[pX + 1][pY] != '.'){
            cout << "Player next to wall\n";
            return false;
        }
        
        // Can be generalized to left, but will give undefined values if used
        // for up and down. For that I will invert.
        float slope = (static_cast<float>(pY) -
                       static_cast<float>(yCoord)) /
                      (static_cast<float>(pX) -
                       static_cast<float>(xCoord));
        
        cout << "Slope: " << slope << '\n';
        
        // Generalized
        if (slope > 1.1 || slope < -1.1){
            return false;
        }
        
        // Direction specific - fixed for left
        for (int x = -1; x >= pX - xCoord; x--){
            int y = round(static_cast<float>(x) * slope);
            
            if (levelArray[xCoord + x][yCoord + y] != '.'){
                return false;
            }
        }
        return true;

	}

	bool checkDown(int pX, int pY) const{
        // Direction specific - fixed for down
        if (pY - yCoord > 4 || pY - yCoord <= 0){
            cout << "Wrong direction\n";
            return false;
        }
        
        // debug stuff
        cout << "enemy X: " << xCoord << '\n';
        cout << "enemy Y: " << yCoord << '\n';
        cout << "pX: " << pX << '\n';
        cout << "pY: " << pY << '\n';
        
        // Direction specific - fixed for down
        if (levelArray[pX][pY - 1] != '.'){
            cout << "Player next to wall\n";
            return false;
        }
        
        // Can be generalized to left, but will give undefined values if used
        // for up and down. For that I will invert.
        float slope = (static_cast<float>(pX) -
                       static_cast<float>(xCoord)) /
                      (static_cast<float>(pY) -
                       static_cast<float>(yCoord));
        
        cout << "Slope: " << slope << '\n';
        
        // Generalized
        if (slope > 1.1 || slope < -1.1){
            return false;
        }
        
        // Direction specific - fixed for up
        for (int y = 1; y <= pY - yCoord; y++){
            int x = round(static_cast<float>(y) * slope);
            
            if (levelArray[xCoord + x][yCoord + y] != '.'){
                return false;
            }
        }
        return true;
	}

	bool checkForPlayer(int pX, int pY){
		if (xCoord == pX && yCoord == pY){
			return true;
		}
        
        
        if (xCoord - pX < 0){ // player to the right
            if (levelArray[pX - 1][pY] != '.'){
                return false;
            }
        }
        else if (xCoord - pX > 0){ // player to the left
            if (levelArray[pX + 1][pY] != '.'){
                return false;
            }
        }
        
        if (yCoord - pY < 0){ // player below
            if (levelArray[pX][pY - 1] != '.'){
                return false;
            }
        }
        else if (yCoord - pY > 0){ // player above
            if (levelArray[pX][pY + 1] != '.'){
                return false;
            }
        }
		
		// just need to have return(checkDirection()), will fix later.
		// All this sight code is hacky garbage. 
		// I'm sorry to whoever reads this.
		switch(heading){
			case 0:
				if (checkRight(pX, pY))
					return 1;
				else
					return 0;
				break;
			case 2:
				if (checkLeft(pX, pY))
					return 1;
				else
					return 0;
				break;
			case 3:
				if (checkDown(pX, pY))
					return 1;
				else
					return 0;
				break;
			case 1:
				if (checkUp(pX, pY))
					return 1;
				else
					return 0;
				break;
			default:
				return 0;
		}
		return 0;
	}
    
    bool loadNewLevel(char newLevelArray[80][25]){
        for (int x = 0; x < 80; x++){
            for (int y = 0; y < 25; y++){
                levelArray[x][y] = newLevelArray[x][y];
            }
        }
        
        return 1;
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
    
    char levelArray[80][25];
};

#endif
