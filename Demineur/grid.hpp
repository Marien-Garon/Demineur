#pragma once
#include "cell.hpp"
#include <cstdlib>
#include <iostream>

struct Grid
{
	int line;
	int column;
	int totalMine;
	Cell** cellTab;
};

int AskInt(int min, int max, const char* text);

void AskDifficulty(Grid* grid);

void CreateGrid(Grid* grid);

void PrintElement(Grid* grid, int i, int j);

void DisplayGrid(Grid* grid);

int MineAroundCalculator(Grid* grid, int i, int j);

void UpdateCell(Grid* grid);

int GenerateRandomNumber(int min, int max);

void PlaceMine(Grid* grid);

void RevealCase(Grid* grid, int i, int j);

void RevealGrid(Grid* grid);

bool CheckWin(Grid* grid);

void DisplayWin(bool win);
