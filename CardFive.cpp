#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos) :Card(pos)
{
	cardNumber = 5;
}


void CardFive::ReadCardParameters(Grid* pGrid)
{
	// no parameters inputted from user .. effect of card is same for all cases
	pGrid->GetOutput()->DrawCell(this->GetPosition(), 5);
	pGrid->PrintErrorMessage("Card Five Added To Cell .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();

}


void CardFive::Apply(Grid* pGrid,Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	CellPosition returnToPos((pPlayer->GetCell()->GetCellPosition().GetCellNum())- 2 * (pPlayer->GetJustRolledDiceNum()));

	if (returnToPos.VCell() == -1)
	{
		returnToPos.SetVCell(8);
		returnToPos.SetHCell(0);
	}

	pGrid->UpdatePlayerCell(pPlayer,returnToPos);

	pGrid->GetOutput()->PrintMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Back To Cell " + to_string(returnToPos.GetCellNum()) + " ...");

	int v=returnToPos.VCell();
	int h=returnToPos.HCell();

	if (pGrid->GetHasObj(v, h))
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
	}

	return;
}


CardFive::~CardFive()
{
	// To Avoid Being An Abstract Class
}