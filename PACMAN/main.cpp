#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "Board.h"
#include "Game.h"
#include "Pacman.h"
#include "Position.h"
#include "Fruit.h"
#include "misc.h"

using namespace std;
namespace fs = std::filesystem;

bool fileExists(string fileName, vector<string> files);
void readFiles(vector<string>& files, int& numOfFiles);
void printMessage(int gameOver, int filesLeft, bool isDesigned);


int main()
{
	bool isDesigned, specificMap = false, gameOver = false, gameLoop = false;
	int i, ghostCounter, filesLeft = 0, numOfFiles = 0, userDifficulty, totalScore = 0, pacmanLives = 3;
	Position pacmanPos, scorePos, ghostPositions[4];
	vector<string> files{};
	string currLine, mapName;

	readFiles(files, numOfFiles);

	if (numOfFiles == 0) {
		cout << "Error: There are no \".screen\" files in this directory." << endl;
		return 0;
	}

	filesLeft = numOfFiles;

	mapName = menu(isDesigned, specificMap, files, userDifficulty);

	if (fileExists(mapName, files))
		gameLoop = true;
	else
		cout << "\n\nError: file does not exist!" << endl;

	if (specificMap)
		filesLeft = 1;


	while (gameLoop) {
		system("cls");
		ghostCounter = 0;
		char newBoard[25][80];

		//read board from file
		ifstream file(mapName);
		i = 0;
		while (getline(file, currLine))
			currLine.copy(newBoard[i++], currLine.length());

		const int winScore = initBoard(newBoard, ghostCounter, ghostPositions, pacmanPos, scorePos);

		//init and run game
		Game game(winScore + totalScore, totalScore, isDesigned, userDifficulty);
		game.start(newBoard, ghostCounter, ghostPositions, pacmanPos, scorePos, totalScore, pacmanLives, gameOver);

		printMessage(gameOver, filesLeft, isDesigned);

		char input = _getch();

		system("cls");
		file.close();
		resetBoard(newBoard);
		filesLeft--;

		if (filesLeft == 0 || gameOver) {
			mapName = menu(isDesigned, specificMap, files, userDifficulty);
			gameOver = false; pacmanLives = 3; totalScore = 0; filesLeft = numOfFiles;
			if (specificMap)
				filesLeft = 1;
			else
				filesLeft = numOfFiles;
		}
		else
			mapName = files[numOfFiles - filesLeft];


		if (!fileExists(mapName, files)) {
			gameLoop = false;
			cout << "\n\nError: file does not exist!" << endl;
		};
	}
}



bool fileExists(string fileName, vector<string> files) {
	int exists = 0;
	for (auto file : files) {
		if (fileName == file) {
			exists++;
		}
	}
	return exists;
}

void readFiles(vector<string>& files, int& numOfFiles)
{
	for (const auto& entry : fs::directory_iterator("./")) {
		if (entry.path().extension() == ".screen") {
			string fileNameString{ entry.path().u8string() };
			fileNameString.erase(0, 2);
			files.push_back(fileNameString);
			numOfFiles++;
		}
	}

}

