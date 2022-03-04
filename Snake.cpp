#include "Snake.h"



Snake::Snake(const CellPosition& startCell , const CellPosition& endCell) : GameObject(startCell)
{
	endCellPos = endCell;
}


void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position,endCellPos) ;
}


void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
	int playernumber = pPlayer->GetPlayerNum();
	string playernumberStr = to_string(playernumber);

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("Player " + playernumberStr + " Have Reached A Snake .. Click To Continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}


Snake::~Snake()
{
	// to avoid being an abstract class
}