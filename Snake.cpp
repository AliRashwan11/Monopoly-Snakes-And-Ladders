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

	

	pGrid->PrintErrorMessage("Player " + playernumberStr + " Have Reached A Snake .. Click To Continue ...");


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