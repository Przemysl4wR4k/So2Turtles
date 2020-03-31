#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Turtle {
	private:
		int xPos;
		int yPos;	
	public:
		Turtle(int x, int y );
		int getXPos();
		int getYPos();
		void setXPos(int x);
		void setYPos(int y);
};

Turtle::Turtle(int x, int y) {
	xPos = x;
	yPos = y;
}
int Turtle::getXPos(void) {
	return xPos;
}
int Turtle::getYPos(void) {
	return yPos;
}
void Turtle::setXPos(int x) {
	xPos = x;
}
void Turtle::setYPos(int y) {
	yPos = y;
}

vector <string> turtleInString;
vector <string> frameInString;
vector <Turtle> turtles;

int height = 40;
int width = 120;

int turtleWidth = 17;
int turtleHeight = 10;

int turtleX = 5;
int turtleY = 9;

void loadTurtle() {
	turtleInString.push_back("|      ___      |");
	turtleInString.push_back("|__   |   |   __|");
	turtleInString.push_back("|\\ \\  |___|  / /|");
	turtleInString.push_back("| \\ \\ /   \\ / / |");
	turtleInString.push_back("|  \\ /\\___/\\ /  |");
	turtleInString.push_back("|   |_/   \\_|   |");
	turtleInString.push_back("|   | \\___/ |   |");
	turtleInString.push_back("|  / \\/   \\/ \\  |");
	turtleInString.push_back("| / / \\___/ \\ \\ |");
	turtleInString.push_back("|/_/    v    \\_\\|");
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

void turtleToFrame() {
	loadFrame();
	for (int j = 0; j < turtles.size(); j++) {
		for (int i = 0; i < turtleHeight; i++)
		{
			frameInString.at(i + turtles.at(j).getYPos()).replace(turtles.at(j).getXPos(), turtleWidth, turtleInString.at(i));
		}
	}
}

void drawTurtle() {

	/* tak cie widzą

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
*/

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
/* tak cie widzą

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
*/

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

void input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 72:		//up
			turtleY -= 3;
			break;
		case 80:		//down
			turtleY += 3;
			break;
		case 77:		//right
			turtleX += 3;
			break;
		case 75:		//left
			turtleX -= 3;
			break;
		}
		turtleToFrame();
	}
}
int main()
{
	Turtle player1(4,10);
	turtles.push_back(player1);

	Turtle player2(22, 30);
	turtles.push_back(player2);



	loadTurtle();
	loadFrame();
	turtleToFrame();


	while (true)
	{
		system("cls");
		input();
		

		for (unsigned int i = 0; i < frameInString.size(); i++) {
			cout << frameInString[i] << endl;
		}
		Sleep(100);
	}
}