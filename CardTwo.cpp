#include "CardTwo.h"
#include "Ladder.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
}


void CardTwo::ReadCardParameters(Grid* pGrid)
{
	// no parameters inputted from user .. effect of card is same for all cases
	pGrid->GetOutput()->DrawCell(this->GetPosition(),2);
	pGrid->PrintErrorMessage("Card Two Added To Cell .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();
}



void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	Ladder* pLadder = pGrid->GetNextLadder(pPlayer->GetCell()->GetCellPosition());


	if (pLadder)
	{
		pGrid->UpdatePlayerCell(pPlayer, pLadder->GetEndPosition());
	}
	else
		pGrid->PrintErrorMessage("Unlucky ! No Ladder To Jump To .. Click To Continue ...");



}




CardTwo::~CardTwo()
{
	// avoiding being abstract class
}