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
	Turtle(int x, int y);
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
	int id;
public:
	Straw(int x, int y, int i);
	int getXPos();
	int getYPos();
	int getId();
	void setXPos(int x);
	void setYPos(int y);
};

Straw::Straw(int x, int y, int i) {
	xPos = x;
	yPos = y;
	id = i;

}
int Straw::getXPos(void) {
	return xPos;
}
int Straw::getYPos(void) {
	return yPos;
}
int Straw::getId(void) {
	return id;
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

int howManyStraws = 0;
int oldIndexOfStrawToDel = -1;
int indexOfStrawToDel = -1;

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
				if (j + straws.at(i).getYPos() < height - 1)
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
void deleteStraw(int index) {
	straws.erase(straws.begin() + index);
}
void generateStraw() {
	int number = rand() % 20;
	if (number == 1) {
		int strawPosition = rand() % width;
		Straw newStraw(strawPosition, -9, howManyStraws);
		howManyStraws++;
		straws.push_back(newStraw);
		elementsToFrame();
	}
}

void isTurtleHurt() {
	for (int i = 0; i < straws.size(); i++) {
		if ((straws.at(i).getXPos() >= turtles.at(0).getXPos()+1 && straws.at(i).getXPos() <= (turtles.at(0).getXPos() + turtleWidth - 1)) ||
		   ((straws.at(i).getXPos() + strawWidth) >= turtles.at(0).getXPos()+1 && (straws.at(i).getXPos() + strawWidth) <= (turtles.at(0).getXPos() + turtleWidth -1)))
		{
			if ((straws.at(i).getYPos() >= turtles.at(0).getYPos()+2 && straws.at(i).getYPos() <= (turtles.at(0).getYPos() + turtleHeight -2)) ||
				((straws.at(i).getYPos() + strawHeight) >= turtles.at(0).getYPos()+2 && (straws.at(i).getYPos() + strawHeight) <= (turtles.at(0).getYPos() + turtleHeight - 2)))
			{
				turtles.at(0).setLifes(turtles.at(0).getLifes() - 1);
				cout << "trafiony";
				indexOfStrawToDel = straws.at(i).getId();
				
			}
		}
		if (oldIndexOfStrawToDel != indexOfStrawToDel)
		{
			oldIndexOfStrawToDel = indexOfStrawToDel;
			deleteStraw(i);
			break;
		}

		if ((straws.at(i).getXPos() >= turtles.at(1).getXPos()+1 && straws.at(i).getXPos() <= (turtles.at(1).getXPos() + turtleWidth -1 )) ||
			((straws.at(i).getXPos() + strawWidth) >= turtles.at(1).getXPos()+1 && (straws.at(i).getXPos() + strawWidth) <= (turtles.at(1).getXPos() + turtleWidth -1)))
		{
			if ((straws.at(i).getYPos() >= turtles.at(1).getYPos()+2 && straws.at(i).getYPos() <= (turtles.at(1).getYPos() + turtleHeight -2)) ||
				((straws.at(i).getYPos() + strawHeight) >= turtles.at(1).getYPos() +2 && (straws.at(i).getYPos() + strawHeight) <= (turtles.at(1).getYPos() + turtleHeight -2)))
			{
				turtles.at(1).setLifes(turtles.at(1).getLifes() - 1);
				cout << "trafiony";
				indexOfStrawToDel = straws.at(i).getId();
			}
		}
		if (oldIndexOfStrawToDel != indexOfStrawToDel)
		{
			oldIndexOfStrawToDel = indexOfStrawToDel;
			deleteStraw(i);
			break;
		}

	/*	if ((turtles.at(0).getXPos() == i.getXPos()) || (turtles.at(0).getYPos() == i.getYPos())) {
			turtles.at(0).setLifes(turtles.at(0).getLifes() - 1);
		}
		if ((turtles.at(1).getXPos() == i.getXPos()) || (turtles.at(1).getYPos() == i.getYPos())) {
			turtles.at(1).setLifes(turtles.at(1).getLifes() - 1);
		}*/
	}
}

void strawMustFall() {
	for (int i = 0; i < straws.size(); i++)
	{
		int oldY = straws.at(i).getYPos();
		oldY++;
		straws.at(i).setYPos(oldY);
	}
	for (int i = 0; i < straws.size(); i++)
	{
		if (straws.at(i).getYPos() > height) 
		{
			deleteStraw(i);
			break;
		}
	}
	isTurtleHurt();

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
			if (turtles.at(0).getYPos() > 1)
			{
				turtles.at(0).setYPos(oldY1 -= 1);	//player1.setYPos(oldY1 -= 3);
			}
			break;

		case 80:		//down
			if (turtles.at(0).getYPos() + turtleHeight < height - 1)
			{
				turtles.at(0).setYPos(oldY1 += 1);	//player1.setYPos(oldY1 += 3);
			}
			break;

		case 77:		//right
			if (turtles.at(0).getXPos() + turtleWidth < width - 1)
			{
				turtles.at(0).setXPos(oldX1 += 1);	//player1.setXPos(oldX1 += 3);
			}
			break;

		case 75:		//left
			if (turtles.at(0).getXPos() > 1)
			{
				turtles.at(0).setXPos(oldX1 -= 1);	//player1.setXPos(oldX1 -= 3);
			}
			break;
		}

		switch (_getch())
		{
		case 'w':		//up
			if (turtles.at(1).getYPos() > 1)
			{
				turtles.at(1).setYPos(oldY2 -= 1);	//player2.setYPos(oldY2 -= 3);
			}
			break;

		case 's':		//down
			if (turtles.at(1).getYPos() + turtleHeight < height - 1)
			{
				turtles.at(1).setYPos(oldY2 += 1);	//player2.setYPos(oldY2 += 3);
			}
			break;

		case 'd':		//right
			if (turtles.at(1).getXPos() + turtleWidth < width - 1)
			{
				turtles.at(1).setXPos(oldX2 += 1);	//player2.setXPos(oldX2 += 3);
			}
			break;

		case 'a':		//left
			if (turtles.at(1).getXPos() > 1)
			{
				turtles.at(1).setXPos(oldX2 -= 1);	//player2.setXPos(oldY2 -= 3);
			}
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

		printf("Czas rozgrywki: %d s\n", ((clock() - start)) / 1000);
		cout << "Zycia gracza nr1: " << turtles.at(0).getLifes() << endl;
		cout << "Zycia gracza nr2: " << turtles.at(1).getLifes() << endl;
		Sleep(100);

	}
}