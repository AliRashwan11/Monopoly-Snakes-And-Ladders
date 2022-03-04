#include "CardSix.h"


CardSix::CardSix(const CellPosition& pos) : Card(pos),ToMoveTo(-1,-1)
{
	cardNumber = 6;
}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	pGrid->GetOutput()->PrintMessage("Click On Cell Which ByPassers Will Be Moved To .. ");
	ToMoveTo = (pGrid->GetInput()->GetCellClicked());
	while (ToMoveTo.VCell() == -1)
	{
		pGrid->GetOutput()->PrintMessage("Invalid Entry .. Please Re-Click");
		ToMoveTo = (pGrid->GetInput()->GetCellClicked());
	}

	pGrid->GetOutput()->DrawCell(this->GetPosition(), 6);
	pGrid->PrintErrorMessage("Card Six Added To Cell " + to_string(position.GetCellNum()) + " And Will Teleport ByPassers To Cell "  +to_string(ToMoveTo.GetCellNum()) + " .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();



}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	pGrid->UpdatePlayerCell(pPlayer,ToMoveTo);

	pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum())   + " Moved To Cell " + to_string(ToMoveTo.GetCellNum()) + " .. Click To Continue ...");

	int v = ToMoveTo.VCell();
	int h = ToMoveTo.HCell();

	if (pGrid->GetHasObj(v, h))
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid,pPlayer);
	}

	return;
}



CardSix::~CardSix()
{
	// To Avoid Being An Abstract Class .. And Avoid Unexepected Behaviour When Deleting base Class Pointer
}