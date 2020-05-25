#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <process.h>

using namespace std;

// klasa zolw
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

// klasa slomka
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

// wektory sluzace do graficznego przedstawienia kolejno: zolwii, slomek, ramki gry
vector <string> turtleInString;
vector <string> strawInString;
vector <string> frameInString;
// wektory obiektow
vector <Turtle> turtles;
vector <Straw> straws;

// deklaracja wystapienia dwoch zolwii
Turtle player1(4, 10);
Turtle player2(22, 29);

//wielkosc ramki gry
const int height = 40;
const int width = 120;

// zmienne opisujace szerokosc i wysokosc graficznego przedstawienia zolwia
const int turtleWidth = 15;
const int turtleHeight = 10;

// zmienne opisujace szerokosc i wysokosc graficznego przedstawienia slomki
const int strawWidth = 4;
const int strawHeight = 10;

// zmienne potrzebne do rozpoczecia generowania slomek
int howManyStraws = 0;
int oldIndexOfStrawToDel = -1;
int indexOfStrawToDel = -1;


clock_t start; // sluzy do liczenia czasu rozgrywki

// sekcje krytyczne kolejno wyswietlania obrazu i obslugi ruchu gracza
CRITICAL_SECTION paint_Section;
CRITICAL_SECTION move_Section;

// funkcja odpowiedzalna za wyswietlenie komunikatu o zakonczeniu gry
void loadEnd(int losser) {
	if (losser == 1)	// w zaleznosci od tego kto zakonczyl gre, tj. kto stracil wszystkie zycia, zostaje wyswietlona informacja o zwyciestwie przeciwnika
	{
		std::cout << 
			"                 __   __    _            __   __    _    ___ ____          __     ___ \n" <<				//                __	__    _            __   __    _    ___ ____         __     ___ _____
			"  \\      / \\  / /  \\ |  \\  / \\  |       /  \\ |  \\  / \\  /       /   |\\  | |  \\     |  \n" <<     // \      / \  / /  \ |  \  / \  |       /  \ |  \  / \  /       /   |\  | |  \     |   | | 
			"   \\    /   \\/ |  __ |__/ |___| |      |  __ |__/ |___| |      /    | \\ | |__/     |  \n" <<            //  \    /   \/ |  __ |__/ |___| |      |  __ |__/ |___| |      /    | \ | |__/     |   | | 
			"    \\/\\/    /   \\__/ |  \\ |   | |___    \\__/ |  \\ |   | \\___ /___   |  \\| |  \\    _|_ \n"			//   \/\/    /   \__/ |  \ |   | |___    \__/ |  \ |   | \___  / __  |  \| |  \    _|_ _|_|_
		;
		
	}
	else
	{
		std::cout <<
			"                 __   __    _            __   __    _    ___ ____          __     _____\n" <<
			"  \\      / \\  / /  \\ |  \\  / \\  |       /  \\ |  \\  / \\  /       /   |\\  | |  \\     | | \n" <<
			"   \\    /   \\/ |  __ |__/ |___| |      |  __ |__/ |___| |      /    | \\ | |__/     | | \n" <<
			"    \\/\\/    /   \\__/ |  \\ |   | |___    \\__/ |  \\ |   | \\___ /___   |  \\| |  \\    _|_|_\n"
			;

	}
	Sleep(10000);
	exit(0);
}

// funkcja odpowiedzialna wczytanie "grafiki" przedstawiajacej zolwia do wektora
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

// funkcja odpowiedzialna wczytanie "grafiki" przedstawiajacej slomke do wektora
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

// funkcja odpowiedzialna wczytanie ramki gry do wektora
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

// funkcja odpowiedzialna za naniesienie slomek i zolwii na ramke
void __cdecl elementsToFrame( void *Args) {

	EnterCriticalSection(&paint_Section);	//rozpoczecie sekcji ktytycznej majace na celu zapewnienie prawidlowego wyswietlania gry
	loadFrame();

	// naniesienie wszystkich zolwii
	for (int i = 0; i < turtles.size(); i++) {
		for (int j = 0; j < turtleHeight; j++)
		{
			frameInString.at(j + turtles.at(i).getYPos()).replace(turtles.at(i).getXPos(), turtleWidth, turtleInString.at(j));
		}
	}

	// naniesienie slomek
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
	LeaveCriticalSection(&paint_Section);	//koniec sekcji krytyczne
	_endthread();
}

/*
void drawTurtle() {
// zolw wyswietlony jako:
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
// bedzie zapisany jako:
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
// slomka wyswietlana jako
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
// bedzie zapisana jako
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

// usuwanie slomek
void deleteStraw(int index) {
	straws.erase(straws.begin() + index);
}

// generowanie slomek
void generateStraw() {
	int number = rand() % 20;	// tutaj wybieramy "zageszczenie" slomek / zasmiecenie zbornika wodnego, tym mozna regulowac poziom trudnosci gry
	if (number == 1) {
		int strawPosition = rand() % width;					// losowanie umiejscowienia nowogenerowanej slomkki
		Straw newStraw(strawPosition, -9, howManyStraws);	// nowa slomka ma wspolzedna Y = -9, zeby cala "schowala sie" na poczatku nad ramka gry i z niej dopiero spadala
		howManyStraws++;				// licznik slomek
		straws.push_back(newStraw);		// dodanie nowej slomki do wektora tychze obiektow
		HANDLE hThread = (HANDLE) _beginthread( elementsToFrame, 0, NULL);	//naniesienie  nowych slomek na ekran
	}
}

// mechanizm utraty zycia przez ktorego z graczy
void isTurtleHurt() {
	// dla kazdej slomki sprawdzamy, czy zajmowane przez nia pole nie koliduje z polem zajmowanym przez ktoregos z zolwii
	for (int i = 0; i < straws.size(); i++) {
		if ((straws.at(i).getXPos() >= turtles.at(0).getXPos()+1 && straws.at(i).getXPos() <= (turtles.at(0).getXPos() + turtleWidth - 1)) ||
		   ((straws.at(i).getXPos() + strawWidth) >= turtles.at(0).getXPos()+1 && (straws.at(i).getXPos() + strawWidth) <= (turtles.at(0).getXPos() + turtleWidth -1)))
		{
			if ((straws.at(i).getYPos() >= turtles.at(0).getYPos()+2 && straws.at(i).getYPos() <= (turtles.at(0).getYPos() + turtleHeight -2)) ||
				((straws.at(i).getYPos() + strawHeight) >= turtles.at(0).getYPos()+2 && (straws.at(i).getYPos() + strawHeight) <= (turtles.at(0).getYPos() + turtleHeight - 2)))
			{
				// jesli koliduje, to zolw traci zycie, zapisujemy tez ktora slomka go trafila
				turtles.at(0).setLifes(turtles.at(0).getLifes() - 1);
				indexOfStrawToDel = straws.at(i).getId();
				
			}
		}
		// kazda slomka ma swoje id, jest to zabezpieczenie przed roznego rodzaju usuwaniem wiekszych ilosci slomek niz bysmy chcieli
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
				indexOfStrawToDel = straws.at(i).getId();
			}
		}
		if (oldIndexOfStrawToDel != indexOfStrawToDel)
		{
			oldIndexOfStrawToDel = indexOfStrawToDel;
			deleteStraw(i);
			break;
		}

		// sprawdzamy czy gra powinna zostac zakoczona, czyli czy ktorys z graczy stracil wszystkie zycia, jesli tak, to konczymy gre
		if (turtles.at(0).getLifes() <= 0)
		{
			loadEnd(0);
		}
		if (turtles.at(1).getLifes() <= 0)
		{
			loadEnd(1);
		}

	}
}

// funkcja odpowiadajaca za spadanie slomek o jedna pozycje w dol
void strawMustFall() {
	// obnizanie slomki
	for (int i = 0; i < straws.size(); i++)
	{
		int oldY = straws.at(i).getYPos();
		oldY++;
		straws.at(i).setYPos(oldY);
	}
	// jesli slomka znajdzie sie pod ekranem gry, to ja usuwamy
	for (int i = 0; i < straws.size(); i++)
	{
		if (straws.at(i).getYPos() > height) 
		{
			deleteStraw(i);
			break;
		}
	}
	// sprawdzamy czy slomki trafily zolwie
	isTurtleHurt();

}


// funkcja odp za przemieszczanie sie zolwii
void __cdecl input( void *Args) {
	EnterCriticalSection(&move_Section); // poczatek sekcji krytycznej ruchu

		int oldX0 = turtles.at(0).getXPos();
		int oldY0 = turtles.at(0).getYPos();
		int oldX1 = turtles.at(1).getXPos();
		int oldY1 = turtles.at(1).getYPos();

		switch (_getch())	//sprawdzamy czy jakis klawisz zostal wcisniety
		{
		case 72:		//up
			if (turtles.at(0).getYPos() > 1)
			{
				// warunku konieczne do spelnienia, aby dany ruch mogl sie odbyc
				if ((( oldY0 - 1 > (oldY1 + turtleHeight)) || (oldX0 > oldX1 + turtleWidth )) || (oldX0 + turtleWidth < oldX1)) 
				{
					turtles.at(0).setYPos(oldY0 -= 1);	//player1.setYPos(oldY1 -= 3); w ten sposob mozna zmieniac tempo przemieszczania sie zolwii
				}
			}
			break;

		case 80:		//down
			if (turtles.at(0).getYPos() + turtleHeight < height - 1)
			{
				if (((oldY0 + 1 + turtleHeight) < oldY1 || (oldX0 > oldX1 + turtleWidth)) || (oldX0 + turtleWidth < oldX1))
				{
					turtles.at(0).setYPos(oldY0 += 1);	//player1.setYPos(oldY1 += 3);
				}
			}
			break;

		case 77:		//right
			if (turtles.at(0).getXPos() + turtleWidth < width - 1)
			{
				if ((((oldX0 + 1 + turtleWidth) < oldX1) || (oldY0 > oldY1 + turtleHeight)) || (oldY0 + turtleHeight < oldY1))
				{
					turtles.at(0).setXPos(oldX0 += 1);	//player1.setXPos(oldX1 += 3);
				}
			}
			break;

		case 75:		//left
			if (turtles.at(0).getXPos() > 1)
			{	
				if ((( oldX0 -1 > (oldX1 + turtleWidth)) || (oldY0 > oldY1 + turtleHeight)) || (oldY0 + turtleHeight < oldY1))
				{
					turtles.at(0).setXPos(oldX0 -= 1);	//player1.setXPos(oldX1 -= 3);
				}
			}
			break;
		}

		switch (_getch())
		{
		case 'w':		//up
			if (turtles.at(1).getYPos() > 1)
			{
				if (((oldY1 - 1 > (oldY0 + turtleHeight)) || (oldX0 > oldX1 + turtleWidth)) || (oldX0 + turtleWidth < oldX1))
				{
					turtles.at(1).setYPos(oldY1 -= 1);	//player2.setYPos(oldY2 -= 3);
				}
			}
			break;

		case 's':		//down
			if (turtles.at(1).getYPos() + turtleHeight < height - 1)
			{
				if (((oldY1 + 1 + turtleHeight) < oldY0 || (oldX0 > oldX1 + turtleWidth)) || (oldX0 + turtleWidth < oldX1))
				{
					turtles.at(1).setYPos(oldY1 += 1);	//player2.setYPos(oldY2 += 3);
				}
			}
			break;

		case 'd':		//right
			if (turtles.at(1).getXPos() + turtleWidth < width - 1)
			{
				if ((((oldX1 + 1 + turtleWidth) < oldX0) || (oldY0 > oldY1 + turtleHeight)) || (oldY0 + turtleHeight < oldY1))
				{
					turtles.at(1).setXPos(oldX1 += 1);	//player2.setXPos(oldX2 += 3);
				}
			}
			break;

		case 'a':		//left
			if (turtles.at(1).getXPos() > 1)
			{
				if ((( oldX1 - 1 > (oldX0 + turtleWidth)) || (oldY0 > oldY1 + turtleHeight)) || (oldY0 + turtleHeight < oldY1))
				{
					turtles.at(1).setXPos(oldX1 -= 1);	//player2.setXPos(oldY2 -= 3);
				}
			}
			break;
		}
		HANDLE hThread3 = (HANDLE)_beginthread(elementsToFrame, 0, NULL);	// narysowanie wprowadzonych zmian
	LeaveCriticalSection(&move_Section);	// koniec sekcji krytycznej
	_endthread();
}

int main()
{
	InitializeCriticalSection(&paint_Section);	// sekcje krytyczne
	InitializeCriticalSection(&move_Section);	

	turtles.push_back(player1);	
	turtles.push_back(player2);
	srand(time(0));



	loadTurtle();
	loadFrame();
	loadStraw();
	HANDLE hThread = (HANDLE)_beginthread(elementsToFrame, 0, NULL);
	start = clock();	// rozpoczecie odleiczania czasu

	while (true)
	{
		system("cls");
		generateStraw();
		strawMustFall();
		if (_kbhit())
		{
			HANDLE hThread2 = (HANDLE)_beginthread(input, 0, NULL);
		}
		
		for (unsigned int i = 0; i < frameInString.size(); i++) {
			std::cout << frameInString[i] << endl;
		}

		// informacje o czasie rozgrywki i ilosci zyc graczy
		printf("Czas rozgrywki: %d s\n", ((clock() - start)) / 1000);
		std::cout << "Zycia gracza nr1: " << turtles.at(0).getLifes() << endl;
		std::cout << "Zycia gracza nr2: " << turtles.at(1).getLifes() << endl;
		Sleep(100);

	}

	//DeleteCriticalSection( & paint_Section);
}