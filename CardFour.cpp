#include "CardFour.h"


CardFour::CardFour(const CellPosition& pos) :Card(pos)
{
	cardNumber = 4;
}


void CardFour::ReadCardParameters(Grid* pGrid)
{
	// no input from user
	pGrid->GetOutput()->DrawCell(this->GetPosition(), 4);
	pGrid->PrintErrorMessage("Card Four Added To Cell .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();
}


void CardFour::Apply(Grid* pGrid,Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	pPlayer->SetCard4Penalty(1);

	pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Prohibited From Rolling Next Round ");

}

CardFour::~CardFour()
{
	// avoid being abstract .. avoid unexpected behaviour from deletion of base class pointers
}