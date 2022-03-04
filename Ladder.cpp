#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	if (endCellPos.IsValidCell())
		this->endCellPos = endCellPos;
	else this->endCellPos=(-1, -1);

}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	int playernumber = pPlayer->GetPlayerNum();
	string playernumberStr = to_string(playernumber);



	pGrid->PrintErrorMessage("Player " + playernumberStr +  " Have Reached A Ladder .. Click To Continue ...");


	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}



Ladder::~Ladder()
{
}
