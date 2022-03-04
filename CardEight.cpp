#include "CardEight.h"



CardEight::CardEight(const CellPosition& pos) :Card(pos)
{
	cardNumber = 8;
	PrisonFee = 0;
}


void CardEight::ReadCardParameters(Grid* pGrid)
{

	pGrid->GetOutput()->DrawCell(this->GetPosition(), 8);
	pGrid->PrintErrorMessage("Card Eight Added To Cell " + to_string(position.GetCellNum()) + " .. Click To Continue ...");

    pGrid->GetOutput()->PrintMessage("Input Prison Fees To Get Prisoner Out ..");
	PrisonFee = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	pGrid->GetOutput()->ClearStatusBar();

	while (PrisonFee <= 0)
	{
		pGrid->GetOutput()->PrintMessage("Invalid ..Fees Have To Be A Positive Amount .. Please Re-Enter ...");
		PrisonFee = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		pGrid->GetOutput()->ClearStatusBar();
	}

	pGrid->PrintErrorMessage("Card Eight Added With Prison Fees = " + to_string(PrisonFee) + " .. Click To Continue ...");

}


void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	pGrid->GetOutput()->PrintMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Choose (1) For Prison Or (2) To Pay " + to_string(PrisonFee) + " As Prison Fees ..");
	int choice = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	pGrid->GetOutput()->ClearStatusBar();

	bool HaveFunds = 1;

	

	while (choice != 1 && choice != 2)
	{
		pGrid->GetOutput()->PrintMessage("Invalid Entry .. Please Choose (1) For Prison Or (2) To Pay " +to_string(PrisonFee)+ " As Prison Fees ..");
		int choice = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		pGrid->GetOutput()->ClearStatusBar();
	}

	if (pPlayer->GetWallet() < PrisonFee)
	{
		pGrid->PrintErrorMessage("Insufficient Funds .. Player " + to_string(pPlayer->GetPlayerNum()) + " Will Be Imprisoned For 3 Turns .. Click To Continue ...");
		choice = 1;
		HaveFunds = 0;
	}

	switch (choice)
	{
	case(1):
		pPlayer->SetImprisoned(1);
		if (HaveFunds)
			pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Imprisoned For 3 Rounds .. Click To Continue ...");
		return;

	case(2):
		pPlayer->SetWallet(pPlayer->GetWallet() - PrisonFee);
		pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Paid The Prison Fees .. Click To Continue ...");
		return;


	default:
		return;


	}


}


CardEight::~CardEight()
{
	// to avoid being an abstract class .. and avoid unexpected behaviour on deleting base class pointers to derived class objects < virtual >
}