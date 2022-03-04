#include "CardThree.h"



CardThree::CardThree(const CellPosition& pos) :Card(pos)
{
	cardNumber = 3;
}


void CardThree::ReadCardParameters(Grid* pGrid)
{
	// no input from user
	pGrid->GetOutput()->DrawCell(this->GetPosition(), 3);
	pGrid->PrintErrorMessage("Card Three Added To Cell .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();
}


void CardThree::Apply(Grid* pGrid,Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	pPlayer->SetTurnCount(pPlayer->GetTurnCount()-1);
	pGrid->RetardCurrentPlyaer();
	
	pGrid->GetOutput()->PrintMessage("You Have Another Dice Roll ! Have A Go ...");

}


CardThree::~CardThree()
{
	// avoiding being an abstract class
}