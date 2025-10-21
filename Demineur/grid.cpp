
#include "grid.hpp"

int AskInt(int min, int max, const char* text) {
	int variable = -1;
	while ((variable < min || variable > max)) {
		//std::cout << "Entrer un nombre entre " << min << " et " << max << ":" << std::endl;
		std::cout << text << std::endl;
		std::cin >> variable;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX);
		}
	}
	return variable;
}

void AskDifficulty(Grid* grid)
{
	int difficulty;
	difficulty = AskInt(1, 4, "Rentrer la difficulte :\n1 : facile 9x9\n2 : moyen 16x16\n3 : difficile 30x16\n4 : personalise");

	switch (difficulty)
	{
	case 1:
		grid->column = 9;
		grid->line = 9;
		break;
	case 2:
		grid->column = 16;
		grid->line = 16;
		break;
	case 3:
		grid->column = 16;
		grid->line = 30;
		break;
	case 4:
		grid->column = AskInt(1, 48, "Rentrer le nombre de colonne : ");
		grid->line = AskInt(1, 48, "Rentrer le nombre de ligne : ");
		break;
	default:
		break;
	}
}

void PrintElement(Grid* grid, int i, int j)
{
	if (grid->cellTab[i][j].isAMine)
	{
		std::cout << "\033[31m" << "*" << "\033[0m";
		return;
	}
	if (grid->cellTab[i][j].isReveal == false)
	{
		if (grid->cellTab[i][j].isFlag)
		{
			std::cout << "\033[33m" << "F" << "\033[0m";
			return;
		}
		std::cout << " ";
		return;
	}
	//if (grid->cellTab[i][j].isAMine)
	//{
	//	std::cout << "\033[31m" << "*" << "\033[0m";
	//	return;
	//}
	std::cout << grid->cellTab[i][j].mineAround;
}

void DisplayGrid(Grid* grid)
{
	system("cls");
	std::cout << "    ";
	for (int i = 0; i < grid->column; i++)
	{
		std::cout << i;
		if (i < 10) std::cout << " ";
		std::cout << "  ";
	}
	std::cout << std::endl;
	for (int j = 0; j < grid->line; j++)
	{
		std::cout << "  ";
		for (int n = 0; n < grid->column; n++)
		{
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;
		std::cout << j;
		if (j < 10)  std::cout << " ";
		std::cout << "| ";
		for (int k = 0; k < grid->column; k++)
		{
			PrintElement(grid, j, k);
			std::cout << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (int v = 0; v < grid->column; v++)
	{
		std::cout << "+---";
	}
	std::cout << "+" << std::endl;
}

int MineAroundCalculator(Grid* grid, int i, int j)
{
	int mineNbr = 0;

	for (int k = -1; k <= 1; k++)
	{
		for (int n = -1; n <= 1; n++)
		{
			if (k == 0 && n == 0)
			{
				continue;
			}

			if (i + k >= 0 && j + n >= 0 && i + k < grid->line && j + n < grid->column)
			{
				if (grid->cellTab[i + k][j + n].isAMine)
				{
					mineNbr++;
				}
			}
		}
	}
	return mineNbr;
}

void UpdateCell(Grid* grid)
{
	for (int i = 0; i < grid->line; i++)
	{
		for (int j = 0; j < grid->column; j++)
		{
			if (!grid->cellTab[i][j].isAMine)
			{
				grid->cellTab[i][j].mineAround = MineAroundCalculator(grid, i, j);
				//std::cout << grid->cellTab[i][j].mineAround << std::endl;
			}
		}
	}
}

void CreateGrid(Grid* grid)
{
	AskDifficulty(grid);

	grid->totalMine = (int)(grid->column * grid->line) * 0.15f;

	grid->cellTab = (Cell**)malloc(sizeof(Cell) * grid->line);
	if (grid->cellTab == nullptr) exit(1);
	for (int i = 0; i < grid->line; i++)
	{
		grid->cellTab[i] = (Cell*)malloc(sizeof(Cell) * grid->column);
		if (grid->cellTab[i] == nullptr) exit(1);
		for (int j = 0; j < grid->column; j++)
		{
			grid->cellTab[i][j] = InitialiseCell();
		}
	}
	DisplayGrid(grid);
}

int GenerateRandomNumber(int min, int max) {

	return rand() % (max - min + 1) + min;
}

void PlaceMine(Grid* grid)
{
	int i;
	int j;
	int mineCounter = grid->totalMine;
	for (int k = 0; k < mineCounter; k++)
	{
		i = GenerateRandomNumber(0, grid->column - 1);
		j = GenerateRandomNumber(0, grid->line - 1);
		if (grid->cellTab[i][j].isAMine || grid->cellTab[i][j].isReveal)
		{
			k--;
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
			if (i + k >= 0 && j + n >= 0 && i + k < grid->line && j + n < grid->column)
			{


				if (grid->cellTab[i + k][j + n].mineAround == 0 && !(grid->cellTab[i + k][j + n].isReveal) && !(grid->cellTab[i + k][j + n].isFlag))
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
	for (int i = 0; i < grid->column; i++)
	{
		for (int j = 0; j < grid->line; j++)
		{
			grid->cellTab[i][j].isReveal = true;
		}
	}
}

bool CheckWin(Grid* grid)
{
	int caseNbr = (grid->column * grid->line) - grid->totalMine;
	for (int i = 0; i < grid->column; i++)
	{
		for (int j = 0; j < grid->line; j++)
		{
			if (grid->cellTab[i][j].isReveal)
			{
				caseNbr -= 1;
			}
		}
	}
	if (caseNbr <= 0)
	{
		return true;
	}
	return false;
}

void DisplayWin(bool win)
{
	if (win)
	{
		std::cout << "GG well play ta gagne" << std::endl;
		return;
	}
	std::cout << "Cheh ta perdu" << std::endl;

}

//void MainLoop()
//{	
//	Grid grid;
//	Grid* gridPtr = &grid;
//	srand(time(NULL));
//	CreateGrid(gridPtr);
//	int x;
//	int y;
//	bool isPlaying = true;
//	bool win = false;
//	x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\nx :");
//	y = AskInt(0, gridPtr->line, "y : ");
//
//	gridPtr->cellTab[x][y].isAMine = false;
//	gridPtr->cellTab[x][y].isReveal = true;
//
//	PlaceMine(gridPtr);
//
//	UpdateCell(gridPtr);
//
//	RevealCase(gridPtr, x, y);
//
//	while (isPlaying)
//	{	
//		DisplayGrid(gridPtr);
//
//		while (AskInt(0,1, "Veux tu placer un drapeau ? (0 = non, 1 = oui)"))
//		{
//			x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\n");
//			y = AskInt(0, gridPtr->line, "y :");
//			gridPtr->cellTab[x][y].isFlag = true;
//			DisplayGrid(gridPtr);
//		}
//		
//		//std::cout << grid->cellTab[x][y].mineAround << std::endl;
//		x = AskInt(0, gridPtr->column, "Rentrer les coordonnees :\nx :");
//		y = AskInt(0, gridPtr->line, "y :");
//
//		gridPtr->cellTab[x][y].isReveal = true;
//
//		RevealCase(gridPtr, x, y);
//
//		if (gridPtr->cellTab[x][y].isAMine)
//		{	
//			win = false;
//			isPlaying = false;
//		}
//		if (CheckWin(gridPtr))
//		{	
//			win = true;
//			isPlaying = false;
//		}
//	}
//	EndGame(gridPtr);
//	DisplayWin(win);
//}
//
//void Game() {
//	bool playing = true;
//	while (playing)
//	{
//		MainLoop();
//		if (!AskInt(0, 1, "Veux tu rejouer ? (0 = non, 1 = oui)"))
//		{	
//			playing = false;
//		}
//		system("cls");
//	}
//}
