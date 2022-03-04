#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	if (endCellPos.IsValidCell())
		this->endCellPos = endCellPos;
	else this->endCellPos=(-1, -1);

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	int playernumber = pPlayer->GetPlayerNum();
	string playernumberStr = to_string(playernumber);

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("Player " + playernumberStr +  " Have Reached A Ladder .. Click To Continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}



Ladder::~Ladder()
{
}
