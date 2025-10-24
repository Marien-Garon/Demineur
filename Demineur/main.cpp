#include <conio.h>
#include "grid.h"
#include "color.h"


int const KEY_UP = 72;
int const KEY_DOWN = 80;
int const KEY_LEFT = 75;
int const KEY_RIGHT = 77;
int const ENTER = 13;
int const ESC = 27;



int clamp(int val, int min, int max)
{
	if (val < min) val = min;
	else if (val >= max)  val = max -1;
	return val;
}

bool KeyInput(Grid* grid, int* row, int* col, bool isFlagMode)
{
	// le boolean noteEscape sert a savoir si on quitte le mode drapeau
	bool notEscape = true;
	int key = sizeof(int);

	while (key != ENTER && key != ESC)
	{
		switch (key = _getch())
		{
		case KEY_UP :
			*row-=1;
			break;
		case KEY_DOWN :
			*row += 1;
			break;
		case KEY_LEFT :
			*col -= 1;
			break;
		case KEY_RIGHT :
			*col += 1;
			break;
		case ESC:
			notEscape = false;
			break; 
		}

		*row = clamp(*row,0, grid->rowCount);
		*col = clamp(*col, 0, grid->colCount);
		DisplayGrid(grid, *row, *col, isFlagMode, false);
	}
	return notEscape;
}

void DisplayWin(bool win)
{
	if (win)
	{
		std::cout << "Felicitation tu a gagne" << RESETCOLOR << std::endl;
		return;
	}
	std::cout << "Dommage tu as perdu" << RESETCOLOR << std::endl;

}


void MainLoop()
{
	Grid grid;

	srand(time(NULL));

	CreateGrid(&grid);

	int row = 0;
	int col = 0;
	bool isPlaying = true;
	bool won = false;

	KeyInput(&grid, &row, &col,false);


	grid.cellTab[row][col].isAMine = false;
	grid.cellTab[row][col].isReveal = true;

	PlaceMine(&grid);

	UpdateCells(&grid);

	RevealCase(&grid, row, col);

	DisplayGrid(&grid, row, col, false, false);

	//Cas particulier ou la grille est si petite que l'on peut révéler toute les case d'un seule coup
	if (CheckWin(&grid))  
	{
		won = true;
		isPlaying = false;
	}

	while (isPlaying)
	{

		//Boucle tant que le joueur veut placer des drapeaux
		while (KeyInput(&grid, &row, &col, true))
		{	
			grid.cellTab[row][col].isFlag = !grid.cellTab[row][col].isFlag;

			DisplayGrid(&grid, row, col, true, false);
		}

		
		KeyInput(&grid, &row, &col, false);

		grid.cellTab[row][col].isReveal = true;

		RevealCase(&grid, row, col);

		DisplayGrid(&grid, row, col, false, false);


		if (grid.cellTab[row][col].isAMine)
		{
			won = false;
			isPlaying = false;
		}
		else if (CheckWin(&grid))
		{
			won = true;
			isPlaying = false;
		}
	}

	RevealGrid(&grid);
	DisplayGrid(&grid, row, col, false, won);
	DisplayWin(won);
}

void Game() {

	bool playing = true;

	do
	{
		system("cls");
		MainLoop();
	} 
	while (AskInt(0, 1, "Veux tu rejouer ?\n0 = non\n1 = oui"));
}



int main()
{
	Game();

	return 0;
}