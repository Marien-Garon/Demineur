#include "grid.h"

int AskInt(int min, int max, const char* text)
{
	int variable = min - 1;
	while ((variable < min || variable > max)) {
		std::cout << text << std::endl;
		std::cin >> variable;

		if (std::cin.fail()) {
			std::cin.clear(); 
			std::cin.ignore(INT_MAX);
		}
	}
	return variable;
}

int GenerateRandomNumber(int min, int max) 
{
	return rand() % (max - min + 1) + min;
}

const char* ChooseColor(bool condition, const char* firstColor, const char* secondColor)
{
	return (condition ? firstColor : secondColor);
}




void PrintElement(Grid* grid, int row, int col, bool won)
{
	std::cout << RESETCOLOR;

	if (grid->cellTab[row][col].isReveal == false)
	{
		if (grid->cellTab[row][col].isFlag)
		{
			std::cout << ORANGE << "F" << RESETCOLOR;
		}
		else
		{
			std::cout << " ";
		}
		return;
	}

	if (grid->cellTab[row][col].isAMine && grid->cellTab[row][col].isReveal)
	{	
		std::cout << ChooseColor(won, GREEN, RED) << "*" << RESETCOLOR;
		return;
	}

	std::cout << grid->cellTab[row][col].mineAround;

}

void PrintColumnNumber(Grid* grid)
{
	for (int col = 0; col < grid->colCount; col++)
	{
		std::cout << col;
		if (col < 10) std::cout << " ";
		std::cout << "  ";
	}
	std::cout << std::endl;
}

void PrintTopBorder(Grid* grid, int row, int posRow, int posCol, bool isFlagMode)
{
	bool needWrapp = false;
	std::cout << "  ";

	for (int col = 0; col < grid->colCount; col++)
	{
		needWrapp = ((row >= posRow && row <= posRow + 1) && (col >= posCol && col <= posCol + 1));

		std::cout << BLUE;
		if (needWrapp)
			std::cout << ChooseColor(isFlagMode, ORANGE, RED);

		std::cout << "+";

		if (col == posCol + 1)
			std::cout << BLUE;

		std::cout << "---" << BLUE;

		needWrapp = ((row >= posRow && row <= posRow + 1) && (col == posCol));
	}

	if (needWrapp)
		std::cout << ChooseColor(isFlagMode, ORANGE, RED);

	std::cout << "+" << BLUE << std::endl;
}

void PrintBottomBorder(Grid* grid, int posRow, int posCol, bool isFlagMode)
{
	std::cout << "  ";
	bool needWrapp = false;

	for (int col = 0; col < grid->colCount; col++)
	{
		needWrapp = ((posRow == grid->rowCount - 1) && (posCol <= col && posCol >= col - 1));

		if (needWrapp)
			std::cout << ChooseColor(isFlagMode, ORANGE, RED);

		std::cout << "+" << BLUE;

		needWrapp = (posCol == col && posRow == grid->rowCount - 1);

		if (needWrapp)
			std::cout << ChooseColor(isFlagMode, ORANGE, RED);

		std::cout << "---" << BLUE;
	}

	if (needWrapp)
		std::cout << ChooseColor(isFlagMode, ORANGE, RED);

	std::cout << "+" << BLUE << std::endl;
}

void PrintLeftBar(int row, int posRow, int posCol, bool isFlagMode)
{
	if (row < 10)  std::cout << " ";

	if ((posCol == 0) && (row == posRow))
		std::cout << ChooseColor(isFlagMode, ORANGE, RED);

	std::cout << "| " << BLUE;
}

void PrintRightBar(int row, int col, int posRow, int posCol, bool isFlagMode)
{
	std::cout << BLUE;
	if ((row == posRow && col == posCol) || (row == posRow && col == posCol - 1))
		std::cout << ChooseColor(isFlagMode, ORANGE, RED);

	std::cout << " | " << BLUE;
}


void DisplayGrid(Grid* grid, int posRow, int posCol, bool isFlagMode, bool won)
{
	system("cls");
	std::cout << RESETCOLOR << "    ";

	PrintColumnNumber(grid);

	for (int row = 0; row < grid->rowCount; ++row)
	{

		PrintTopBorder(grid, row, posRow, posCol, isFlagMode);

		std::cout << RESETCOLOR << row << BLUE;

		PrintLeftBar(row, posRow, posCol, isFlagMode);

		for (int col = 0; col < grid->colCount; ++col)
		{
			PrintElement(grid, row, col, won);
			
			PrintRightBar(row, col, posRow, posCol, isFlagMode);
		}
		std::cout << std::endl;
	}

	PrintBottomBorder(grid, posRow, posCol, isFlagMode);

	std::cout << RESETCOLOR;

	if (isFlagMode)
		std::cout << "Mode Drapeau :\nENTER : Placer/enlever un drapeau\nESC : Quitter le mode Drapeau" << std::endl;
	else
		std::cout << "ENTER : Reveler la case" << std::endl;
	
	if (won)
		std::cout << GREEN;
	else
		std::cout << RED;
}


bool CheckCoordinate(Grid* grid, int row, int col)
{
	return (row >= 0 && col >= 0 && row < grid->rowCount && col < grid->colCount);
}

void AskDifficulty(Grid* grid)
{
	int difficulty;
	difficulty = AskInt(1, 4, "Rentrer la difficulte :\n1 : facile 9x9\n2 : moyen 16x16\n3 : difficile 30x16\n4 : personalise");

	switch (difficulty)
	{
	case 1:
		grid->rowCount = 9;
		grid->colCount = 9;
		break;
	case 2:
		grid->rowCount = 16;
		grid->colCount = 16;
		break;
	case 3:
		grid->rowCount = 16;
		grid->colCount = 30;
		break;
	case 4:
		grid->rowCount = AskInt(1, 48, "Rentrer le nombre de colonne : ");
		grid->colCount = AskInt(1, 48, "Rentrer le nombre de ligne : ");
		break;
	}
}

void CreateGrid(Grid* grid)
{
	AskDifficulty(grid);

	grid->totalMine = (int)((grid->colCount * grid->rowCount) * 0.15f);

	grid->cellTab = (Cell**)malloc(sizeof(Cell*) * grid->rowCount);

	if (grid->cellTab == nullptr) exit(1);


	for (int col = 0; col < grid->rowCount; ++col)
	{
		grid->cellTab[col] = (Cell*)malloc(sizeof(Cell) * grid->colCount);

		if (grid->cellTab[col] == nullptr) exit(1);

		for (int row = 0; row < grid->colCount; ++row)
			grid->cellTab[col][row] = InitialiseCell();
	}


	DisplayGrid(grid, 0, 0, false, false);
}


int MineAroundCalculator(Grid* grid, int i, int j)
{
	int mineNbr = 0;

	for (int k = -1; k <= 1; ++k)
	{
		for (int n = -1; n <= 1; ++n)
		{
			if (k == 0 && n == 0)
			{
				continue;
			}

			int ki = i + k;
			int nj = j + n;

			if (CheckCoordinate(grid, ki, nj) && grid->cellTab[ki][nj].isAMine)
				mineNbr++;
		}
	}
	return mineNbr;
}

void UpdateCells(Grid* grid)
{
	for (int i = 0; i < grid->rowCount; ++i)
	{
		for (int j = 0; j < grid->colCount; ++j)
		{
			if (!grid->cellTab[i][j].isAMine)
			{
				grid->cellTab[i][j].mineAround = MineAroundCalculator(grid, i, j);
			}
		}
	}
}

void PlaceMine(Grid* grid)
{
	int i;
	int j;
	int mineCounter = grid->totalMine;

	for (int k = 0; k < mineCounter; ++k)
	{
		i = GenerateRandomNumber(0, grid->rowCount - 1);
		j = GenerateRandomNumber(0, grid->colCount - 1);

		if (grid->cellTab[i][j].isAMine || grid->cellTab[i][j].isReveal)
		{
			--k;
			continue;
		}

		grid->cellTab[i][j].isAMine = true;
	}
}

void RevealCase(Grid* grid, int i, int j)
{
	for (int k = -1; k <= 1; k++)
	{
		for (int n = -1; n <= 1; n++)
		{
			if (i + k >= 0 && j + n >= 0 && i + k < grid->rowCount && j + n < grid->colCount)
			{


				if (grid->cellTab[i + k][j + n].mineAround == 0 && !(grid->cellTab[i + k][j + n].isReveal) && !(grid->cellTab[i + k][j + n].isFlag) && !(grid->cellTab[i+k][j+n].isAMine))
				{
					grid->cellTab[i + k][j + n].isReveal = true;
					RevealCase(grid, i + k, j + n);
				}
				if (!(grid->cellTab[i + k][j + n].isReveal) && !(grid->cellTab[i + k][j + n].isAMine) && !(grid->cellTab[i + k][j + n].isFlag))
				{
					grid->cellTab[i + k][j + n].isReveal = true;
				}
			}
		}
	}
}

void RevealGrid(Grid* grid)
{
	for (int row = 0; row < grid->rowCount; ++row)
		for (int col = 0; col < grid->colCount; ++col)
			grid->cellTab[row][col].isReveal = true;
}


bool CheckWin(Grid* grid)
{
	int caseNbr = (grid->colCount * grid->rowCount) - grid->totalMine;

	for (int row = 0; row < grid->rowCount; ++row)
	{
		for (int col = 0; col < grid->colCount; ++col)
		{
			if (grid->cellTab[row][col].isReveal)
			{
				--caseNbr;
			}
		}
	}

	return caseNbr <= 0;
}
