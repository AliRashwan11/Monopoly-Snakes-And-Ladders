#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "CardNine.h"
#include "Player.h"


Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}
	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;

	HasACardNine = 0;
	HasACardTen = 0;
	HasACardEleven = 0;
}

// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

int Grid::CellAvailability(CellPosition& cellObj)  // 0 no object .. 1 ladder .. 2 snake .. 3 card
{
	int V = cellObj.VCell();
	int H = cellObj.HCell();

	if (CellList[V][H]->HasCard())
		return 3;
	else if (CellList[V][H]->HasLadder())
		return 1;
	else if (CellList[V][H]->HasSnake())
		return 2;

	return 0;

}

Ladder* Grid::GetLadderObject(CellPosition Objpos)
{
	int V = Objpos.VCell();
	int H = Objpos.HCell();

	return CellList[V][H]->HasLadder();

}

Snake* Grid::GetSnakeObject(CellPosition Objpos)
{
	int V = Objpos.VCell();
	int H = Objpos.HCell();

	return CellList[V][H]->HasSnake();

}

Card* Grid::GetCardObject(CellPosition Objpos)
{
	int V = Objpos.VCell();
	int H = Objpos.HCell();

	return CellList[V][H]->HasCard();
}




// Note: You may need to change the return type of this function (Think)


void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}



void Grid::ResetToPlayer0()
{
	currPlayerNumber = 0;   // The player number that has the turn to play 
}
// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

Player* Grid::GetPlayerFromNum(int a)
{
	return this->PlayerList[a];
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

void Grid::RetardCurrentPlyaer()
{
	currPlayerNumber = (currPlayerNumber -1) % MaxPlayerCount;
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it

			if (CellList[i][j]->HasLadder())
			{
				return CellList[i][j]->HasLadder();
			}
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


int* Grid::GetNextPlayer(const CellPosition& position,int& j)
{
	int PlayersCellNums[4];


	for (int i = 0; i < 4; i++)
	{
		PlayersCellNums[i] = this->PlayerList[i]->GetCell()->GetCellPosition().GetCellNum();
	}



	int positionOfCardPlayer = position.GetCellNum();
	int minDistance = 100;

	for (int i = 0; i < 4; i++)
	{
		if (PlayersCellNums[i] > positionOfCardPlayer)
		{
			if (minDistance > (PlayersCellNums[i] - positionOfCardPlayer))
			{
				minDistance = (PlayersCellNums[i] - positionOfCardPlayer);

			}
		}
	}

	int counter = 0;

	for (int i = 0; i < 4; i++)
	{
		if ((PlayersCellNums[i] - positionOfCardPlayer) == minDistance)
			counter++;
	}

	int* PtrToLeaders = new int[counter];
	j = 0;

	for (int i = 0; i < 4; i++)
	{
		if ((PlayersCellNums[i] - positionOfCardPlayer) == minDistance)
		{
			PtrToLeaders[j] = i;
			j++;
		}
	}

	if (j == 0)
	{		
		return NULL;
	}

	if (j == 1)
	{
		int* ToReturn = new int[1];
		ToReturn[0] = PtrToLeaders[0];
		return ToReturn;
	}

	if (j == 2)
	{
		int* ToReturn = new int[2];
		for (int i = 0; i < 2; i++)
			ToReturn[i] = PtrToLeaders[i];
		return ToReturn;
	}

	if (j == 3)
	{
		int* ToReturn = new int[3];
		for (int i = 0; i < 3; i++)
			ToReturn[i] = PtrToLeaders[i];
		return ToReturn;
	}
		
}


				


void Grid::SetCrowded(int startV, int endV, int H)
{
	for (int i = endV; i <= startV; i++)
	{
		this->CellList[i][H]->SetIsCrowded(1);
	}
}


void Grid::SetCrowdedOfSnake(int startV, int endV, int H,bool a)
{
	for (int i = endV; i <= startV; i++)
	{
		this->CellList[i][H]->SetCrowdedFromSnake(a);
	}
}

void Grid::SetCrowdedOfLadder(int startV, int endV, int H, bool a)
{
	for (int i = endV; i <= startV; i++)
	{
		this->CellList[i][H]->SetCrowdedFromLadder(a);
	}
}

void Grid::SetNotCrowded(int startV, int endV, int H)
{
	for (int i = endV; i <= startV; i++)
	{
		this->CellList[i][H]->SetIsCrowded(0);
	}
}



bool Grid ::GetCrowded(int startV, int endV, int H)
{
	for (int i = endV; i <= startV; i++)
	{
		if (this->CellList[i][H]->GetIsCrowded() == 1)
			return true;
	}
	return false;
}


int Grid::GetCardNumInCell(int v, int h) const
{
	return this->CellList[v][h]->HasCard()->GetCardNumber();
}

bool Grid::CellHasCard(int v, int h) const
{
	if (this->CellList[v][h]->HasCard())
		return true;
	return false;
}



bool Grid::GetHasObj(int vcell, int hcell)
{
	if (this->CellList[vcell][hcell]->HasCard() || this->CellList[vcell][hcell]->HasSnake() || this->CellList[vcell][hcell]->HasLadder())
		return true;

	return false;
}


bool Grid::GetCrowdedOfSnake(int v,int h)
{
	return this->CellList[v][h]->GetCrowdedFromSnake();
}

bool Grid::GetCrowdedOfLadder(int v, int h)
{
	return this->CellList[v][h]->GetCrowdedFromLadder();
}


void Grid::SetHasLadderEnd(int v, int h ,bool a)
{
	this->CellList[v][h]->SetHasLadderEnd(a);
}

void Grid::SetHasSnakeEnd(int v, int h, bool a)
{
	this->CellList[v][h]->SetHasSnakeEnd(a);
}
void Grid::SetHasSnakeHead(int v, int h, bool a)
{
	this->CellList[v][h]->SetHasSnakeHead(a);
}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}