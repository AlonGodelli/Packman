#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

inline string menu(bool& isDesigned, bool& specificMap, vector<string> files, int& userDifficulty) {
	int choice = 0;
	int ghostUserChoice = 2;

	cout << "Please enter your choice:" << endl;
	cout << "(1) Start a new game (with color & wall styles)" << endl;
	cout << "(2) Start a new game (no color & no wall styles)" << endl;
	cout << "(3) Start a new game (specific map)" << endl;
	cout << "(8) Show instructions & controls" << endl;
	cout << "(9) Exit" << endl;
	cin >> choice;

	while (choice != 1 && choice != 2 && choice != 3) {
		if (choice == 8) {
			system("cls");
			cout << "Instructions:" << endl;
			cout << "Guide Pacman around the maze and eat all the breadcrumbs whilst avoiding ghosts." << endl;
			cout << "Keys:" << endl;
			cout << "LEFT - A/a" << endl;
			cout << "RIGHT - D/d" << endl;
			cout << "DOWN - X/x" << endl;
			cout << "UP - W/w" << endl;
			cout << "STAY - S/s" << endl;

			cout << "\nPlease enter your choice:" << endl;
			cout << "(1) Start a new game (with color & wall styles)" << endl;
			cout << "(2) Start a new game (no color & no wall styles)" << endl;
			cout << "(3) Start a new game (specific map)" << endl;
			cout << "(8) Show instructions & controls" << endl;
			cout << "(9) Exit" << endl;
		}
		else if (choice == 9) {
			cout << "Goodbye!";
			exit(0);
		}
		else {
			cout << "invalid input, please select a valid input" << endl;
		}
		cin >> choice;
	}
	isDesigned = true;
	string mapName;
	userDifficulty = -1;
	system("cls");
	do
	{
		cout << "Please select difficulty (0-2):" << endl;
		cout << "(0) NOVICE" << endl;
		cout << "(1) GOOD" << endl;
		cout << "(2) BEST" << endl;
		cin >> userDifficulty;
		cout << endl;
		if (userDifficulty > 2 || userDifficulty < 0) {
			system("cls");
			cout << "Invalid Input!\n" << endl;
		}
	} while (userDifficulty > 2 || userDifficulty < 0);

	switch (choice)
	{
	case 1:
		specificMap = false;
		return files[0];
	case 2:
		isDesigned = false;
		specificMap = false;
		return files[0];
	case 3:
		system("cls");
		specificMap = true;
		cout << "Please enter desired map file name: ";
		cin >> mapName;
		return mapName;
	default:
		break;
	}



}

inline const int initBoard(char(&newBoard)[25][80], int& ghostCounter, Position(&ghostPositions)[4], Position& pacmanPos, Position& scorePos) {
	int counter = 0;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			switch (newBoard[i][j])
			{
			case '#':
				break;
			case 32:
				newBoard[i][j] = 250; //breadcrumb
				counter++;
				break;
			case '%':
				break;
			case '$':
				ghostPositions[ghostCounter++].setPosition(j, i);
				newBoard[i][j] = 250;
				counter++;
				break;
			case '@':
				pacmanPos = Position(j, i);
				newBoard[i][j] = ' ';
				break;
			case '&':
				scorePos = Position(j, i);
				newBoard[i][j] = '%';
				break;
			default:
				newBoard[i][j] = '%';
				break;
			}
		}
	}
	return counter;
}

inline void resetBoard(char(&board)[25][80]) {
	for (int h = 0; h < 25; h++)
	{
		for (int w = 0; w < 80; w++)
		{
			board[h][w] = '%';
		}
	}
}

inline const bool isLegal(char& input) {
	input = tolower(input);
	if (input == 'w' ||
		input == 'a' ||
		input == 's' ||
		input == 'd' ||
		input == 'x') {
		return true;
	}
	return false;
}

inline void gotoxy(const int x, const int y)
{
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x, y };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

inline const int randomNum(const int min, int max)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(min, max + 1);
	return (dist(mt));
}


//--------------- print functions -------------------//

inline void changeColor(int desiredColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

inline void printGamePaused(int color) {
	const char* gamePuesed = R"(
 _____   ___  ___  ___ _____  ______  ___  _   _ _____ ___________ 
|  __ \ / _ \ |  \/  ||  ___| | ___ \/ _ \| | | /  ___|  ___|  _  \
| |  \// /_\ \| .  . || |__   | |_/ / /_\ \ | | \ `--.| |__ | | | |
| | __ |  _  || |\/| ||  __|  |  __/|  _  | | | |`--. \  __|| | | |
| |_\ \| | | || |  | || |___  | |   | | | | |_| /\__/ / |___| |/ / 
 \____/\_| |_/\_|  |_/\____/  \_|   \_| |_/\___/\____/\____/|___/  
                                                                   
                                                                   )";

	system("cls");
	changeColor(15);
	cout << gamePuesed;
}

inline void printyouWin(int color) {
	const char* youWin = R"(
__   _______ _   _    _    _ _____ _   _    _   _ 
\ \ / /  _  | | | |  | |  | |_   _| \ | |  | | | |
 \ V /| | | | | | |  | |  | | | | |  \| |  | | | |
  \ / | | | | | | |  | |/\| | | | | . ` |  | | | |
  | | \ \_/ / |_| |  \  /\  /_| |_| |\  |  |_| |_|
  \_/  \___/ \___/    \/  \/ \___/\_| \_/  (_) (_)
                                                  
                                                  )";

	system("cls");
	changeColor(color);
	cout << youWin;
	changeColor(15);
	cout << "\n\n\n Press any key to return to menu";
}

inline void printgameOver(int color) {
	const char* gameOver = R"(
 _____   ___  ___  ___ _____   _____  _   _ ___________ 
|  __ \ / _ \ |  \/  ||  ___| |  _  || | | |  ___| ___ \
| |  \// /_\ \| .  . || |__   | | | || | | | |__ | |_/ /
| | __ |  _  || |\/| ||  __|  | | | || | | |  __||    / 
| |_\ \| | | || |  | || |___  \ \_/ /\ \_/ / |___| |\ \ 
 \____/\_| |_/\_|  |_/\____/   \___/  \___/\____/\_| \_|
                                                        
                                                        )";

	system("cls");
	changeColor(color);
	cout << gameOver;
	changeColor(15);
	cout << "\n\n\n Press any key to return to menu";
}

inline void printLevelClear(int color) {
	const char* levelClear = R"(
 _      _____ _   _ _____ _       _____  _      _____  ___  ______ 
| |    |  ___| | | |  ___| |     /  __ \| |    |  ___|/ _ \ | ___ \
| |    | |__ | | | | |__ | |     | /  \/| |    | |__ / /_\ \| |_/ /
| |    |  __|| | | |  __|| |     | |    | |    |  __||  _  ||    / 
| |____| |___\ \_/ / |___| |____ | \__/\| |____| |___| | | || |\ \ 
\_____/\____/ \___/\____/\_____/  \____/\_____/\____/\_| |_/\_| \_|
																		)";

	system("cls");
	changeColor(color);
	cout << levelClear;
	changeColor(15);
	cout << "\n\n\n Press any key to procceed to the next screen";
}

inline void printMessage(const int gameOver, const int filesLeft, const bool isDesigned)
{
	if (gameOver)
		printgameOver(15 - 3 * isDesigned); //red
	else if (filesLeft != 1)
		printLevelClear(15 - 6 * isDesigned); // blue
	else
		printyouWin(15 - 5 * isDesigned); //green

}



