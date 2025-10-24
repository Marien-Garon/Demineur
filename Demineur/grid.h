#pragma once

#include <cstdlib>
#include <iostream>
#include "cell.h"
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



void PrintElement(Grid* grid, int i, int j, bool won);

void PrintColumnNumber(Grid* grid);

void PrintTopBorder(Grid* grid, int row, int posRow, int posCol, bool isFlagMode);

void PrintBottomBorder(Grid* grid, int posRow, int posCol, bool isFlagMode);

void PrintLeftBar(int row, int posRow, int posCol, bool isFlagMode);

void PrintRightBar(int row, int col, int posRow, int posCol, bool isFlagMode);


void DisplayGrid(Grid* grid, int x, int y, bool isFlagMode, bool won);


bool CheckCoordinate(Grid* grid, int row, int col);

void AskDifficulty(Grid* grid);

void CreateGrid(Grid* grid);


int MineAroundCalculator(Grid* grid, int i, int j);

void UpdateCells(Grid* grid);

void PlaceMine(Grid* grid);

void RevealCase(Grid* grid, int i, int j);

void RevealGrid(Grid* grid);


bool CheckWin(Grid* grid);

