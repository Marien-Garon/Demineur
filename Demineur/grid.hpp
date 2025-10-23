#pragma once
#include <cstdlib>
#include <iostream>
#include "cell.hpp"
#include "color.h"

struct Grid
{
	int rowCount;
	int colCount;
	int totalMine;
	Cell** cellTab;
};


int AskInt(int min, int max, const char* text);

int GenerateRandomNumber(int min, int max);

const char* ChooseColor(bool condition, const char* firstColor, const char* secondColor);




bool CheckCoordinate(Grid* grid, int row, int col);

void AskDifficulty(Grid* grid);

void CreateGrid(Grid* grid);

void PrintElement(Grid* grid, int i, int j, bool won);

void DisplayGrid(Grid* grid, int x, int y, bool isFlagMode, bool won);

int MineAroundCalculator(Grid* grid, int i, int j);

void UpdateCells(Grid* grid);

void PlaceMine(Grid* grid);

void RevealCase(Grid* grid, int i, int j);

void RevealGrid(Grid* grid);

bool CheckWin(Grid* grid);

