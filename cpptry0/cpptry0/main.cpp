#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Turtle {
	private:
		int xPos;
		int yPos;	
		int lifes;
	public:
		Turtle(int x, int y );
		int getXPos();
		int getYPos();
		int getLifes();
		void setXPos(int x);
		void setYPos(int y);
		void setLifes(int n);
};

Turtle::Turtle(int x, int y) {
	lifes = 3;
	xPos = x;
	yPos = y;
}
int Turtle::getXPos(void) {
	return xPos;
}
int Turtle::getYPos(void) {
	return yPos;
}
int Turtle::getLifes(void) {
	return lifes;
}
void Turtle::setXPos(int x) {
	xPos = x;
}
void Turtle::setYPos(int y) {
	yPos = y;
}
void Turtle::setLifes(int n) {
	lifes = n;
}

class Straw {
private:
	int xPos;
	int yPos;
public:
	Straw(int x, int y);
	int getXPos();
	int getYPos();
	void setXPos(int x);
	void setYPos(int y);
};

Straw::Straw(int x, int y) {
	xPos = x;
	yPos = y;
}
int Straw::getXPos(void) {
	return xPos;
}
int Straw::getYPos(void) {
	return yPos;
}
void Straw::setXPos(int x) {
	xPos = x;
}
void Straw::setYPos(int y) {
	yPos = y;
}

vector <string> turtleInString;
vector <string> strawInString;
vector <string> frameInString;
vector <Turtle> turtles;
vector <Straw> straws;

Turtle player1(4, 10);

Turtle player2(22, 29);

int height = 40;
int width = 120;

int turtleWidth = 15;
int turtleHeight = 10;

int strawWidth = 4;
int strawHeight = 10;

clock_t start;
//int turtleX = 5;
//int turtleY = 9;

void loadTurtle() {
	turtleInString.push_back("      ___      ");
	turtleInString.push_back("__   |   |   __");
	turtleInString.push_back("\\ \\  |___|  / /");
	turtleInString.push_back(" \\ \\ /   \\ / / ");
	turtleInString.push_back("  \\ /\\___/\\ /  ");
	turtleInString.push_back("   |_/   \\_|   ");
	turtleInString.push_back("   | \\___/ |   ");
	turtleInString.push_back("  / \\/   \\/ \\  ");
	turtleInString.push_back(" / / \\___/ \\ \\ ");
	turtleInString.push_back("/_/    v    \\_\\");
}

void loadStraw() {
	strawInString.push_back(" __ ");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|  |");
	strawInString.push_back("|__|");
}

void loadFrame() {

	frameInString.clear();

	string topbottom;
	for (int i = 0; i < width; i++)
		topbottom.append("#");

	string middle;
	middle.append("#");
	for (int i = 0; i < width - 2; i++)
		middle.append(" ");
	middle.append("#");

	frameInString.push_back(topbottom);
	for (int i = 0; i < height - 2; i++)
	{
		frameInString.push_back(middle);
	}
	frameInString.push_back(topbottom);
}

void elementsToFrame() {
	
	loadFrame();
	

	/* zajebiste debugowanie			

	cout << turtles.size()<<" size of turtles"<<endl;
	cout << turtles.at(0).getXPos()<<" player1 X"<<endl;
	cout << turtles.at(0).getYPos()<<" player1 Y"<<endl;
	cout << turtles.at(1).getXPos()<<" player2 X"<<endl;
	cout << turtles.at(1).getYPos()<<" player2 Y"<<endl;
	*/

	for (int i = 0; i < turtles.size(); i++) {
		for (int j = 0; j < turtleHeight; j++)
		{
			frameInString.at(j + turtles.at(i).getYPos()).replace(turtles.at(i).getXPos(), turtleWidth, turtleInString.at(j));
			//frameInString.at(j + player1.getYPos()).replace(player1.getXPos(), turtleWidth, turtleInString.at(j));
			//frameInString.at(j + player2.getYPos()).replace(player2.getXPos(), turtleWidth, turtleInString.at(j));
		}
	}

	for (int i = 0; i < straws.size(); i++) {
		for (int j = 0; j < strawHeight; j++)
		{	
			if (j + straws.at(i).getYPos() > 0)
			{
				if (j + straws.at(i).getYPos() < height-1)
					frameInString.at(j + straws.at(i).getYPos()).replace(straws.at(i).getXPos(), strawWidth, strawInString.at(j));
			}
		}
	}
}

/*
void drawTurtle() {

// tak cie widzą

	cout << "          ___		      " << endl;
	cout << "    __   |   |   __      " << endl;
	cout << "    \ \  |___|  / /      " << endl;
	cout << "     \ \ /   \ / /		  " << endl;
	cout << "      \ /\___/\ /		  " << endl;
	cout << "       |_/   \_|		  " << endl;
	cout << "       | \___/ |		  " << endl;
	cout << "      / \/   \/ \		  " << endl;
	cout << "     / / \___/ \ \		  " << endl;
	cout << "    /_/    v    \_\	  " << endl;
	

// tak cie piszą

	cout << "          ___		      " << endl;
	cout << "    __   |   |   __      " << endl;
	cout << "    \\ \\  |___|  / /      " << endl;
	cout << "     \\ \\ /   \\ / /		  " << endl;
	cout << "      \\ /\\___/\\ /		  " << endl;
	cout << "       |_/   \\_|		  " << endl;
	cout << "       | \\___/ |		  " << endl;
	cout << "      / \\/   \\/ \\		  " << endl;
	cout << "     / / \\___/ \\ \\		  " << endl;
	cout << "    /_/    v    \\_\\	  " << endl;

}

void drawStraw() {
// tak cie widzą

	cout << "      __      	      " << endl;
	cout << "      \ \			  " << endl;
	cout << "       \ \			  " << endl;
	cout << "        \ \ 		  " << endl;
	cout << "         \ \		  " << endl;
	cout << "          \ \		  " << endl;
	cout << "           \ \		  " << endl;
	cout << "            \ \	  " << endl;
	cout << "             \ \	  " << endl;
	cout << "	       	   \_\	  " << endl;


// tak cie piszą

	cout << "      __      	      " << endl;
	cout << "      \\ \\			  " << endl;
	cout << "       \\ \\			  " << endl;
	cout << "        \\ \\ 		  " << endl;
	cout << "         \\ \\		  " << endl;
	cout << "          \\ \\		  " << endl;
	cout << "           \\ \\		  " << endl;
	cout << "            \\ \\	  " << endl;
	cout << "             \\ \\	  " << endl;
	cout << "              \\_\\	  " << endl;
}
*/

void generateStraw() {
	int number = rand() % 30;
	if (number == 1) {
		int strawPosition = rand() % width;
		Straw newStraw(strawPosition, -9);
		straws.push_back(newStraw);
		elementsToFrame();
	}
}

void strawMustFall() {
	for(int i = 0; i < straws.size(); i++)
	{
		int oldY = straws.at(i).getYPos();
		oldY++;
		straws.at(i).setYPos(oldY);
	}
}

void input() {
	if (_kbhit())
	{
		int oldX1 = turtles.at(0).getXPos();	//player1.getXPos();
		int oldY1 = turtles.at(0).getYPos();	//player1.getYPos();
		int oldX2 = turtles.at(1).getXPos();	//player2.getXPos();
		int oldY2 = turtles.at(1).getYPos();	//player2.getYPos();

		switch (_getch())
		{
		case 72:		//up
			turtles.at(0).setYPos(oldY1 -=3);	//player1.setYPos(oldY1 -= 3);
			break;

		case 80:		//down
			turtles.at(0).setYPos(oldY1 += 3);	//player1.setYPos(oldY1 += 3);
			break;

		case 77:		//right
			turtles.at(0).setXPos(oldX1 += 3);	//player1.setXPos(oldX1 += 3);
			break;

		case 75:		//left
			turtles.at(0).setXPos(oldX1 -= 3);	//player1.setXPos(oldX1 -= 3);
			break;
		}
		
		switch (_getch()) 
		{
		case 'w':		//up
			turtles.at(1).setYPos(oldY2 -= 3);	//player2.setYPos(oldY2 -= 3);
			break;

		case 's':		//down
			turtles.at(1).setYPos(oldY2 += 3);	//player2.setYPos(oldY2 += 3);
			break;

		case 'd':		//right
			turtles.at(1).setXPos(oldX2 += 3);	//player2.setXPos(oldX2 += 3);
			break;

		case 'a':		//left
			turtles.at(1).setXPos(oldX2 -= 3);	//player2.setXPos(oldY2 -= 3);
			break;
		}
		elementsToFrame();
	}
}

int main()
{
	turtles.push_back(player1);
	turtles.push_back(player2);
	srand(time(0));

	Straw newStraw(40, 10);
	straws.push_back(newStraw);

	loadTurtle();
	loadFrame();
	loadStraw();
	elementsToFrame();
	start = clock();

	while (true)
	{
		system("cls");
		generateStraw();
		strawMustFall();
		input();
		

		for (unsigned int i = 0; i < frameInString.size(); i++) {
			cout << frameInString[i] << endl;
		}
		
		printf("Czas rozgrywki: %d s\n", ((clock() - start))/1000);
		cout << "Zycia gracza nr1: <3 <3 <3" << endl;
		cout << "Zycia gracza nr2: <3 <3 <3" << endl;
		Sleep(100);

	}
}