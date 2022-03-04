#include "CardSeven.h"
#include<string.h>


CardSeven::CardSeven(const CellPosition& pos) : Card(pos)
{
	cardNumber = 7;
}


void CardSeven::ReadCardParameters(Grid* pGrid)
{
	// No Input Parameters From User

	pGrid->GetOutput()->DrawCell(this->GetPosition(), 7);
	pGrid->PrintErrorMessage("Card Seven Added To Cell " + to_string(position.GetCellNum()) + " .. Click To Continue ...");
	pGrid->GetOutput()->ClearStatusBar();

}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	int sizeArr = 0;

	int* LeadingPlayers = pGrid->GetNextPlayer(pPlayer->GetCell()->GetCellPosition(),sizeArr);
	int cases = 0;
	int choosen = 0;
	int size = 0;


	if (sizeArr==0)
	{
		pGrid->PrintErrorMessage("No Players Leading Player " + to_string(pPlayer->GetPlayerNum()) + " .. Click To Continue ...");
		return;
	}
	else if (sizeArr== 2)
	{
		cases = 1;
		pGrid->GetOutput()->PrintMessage("Choose Player " + to_string(LeadingPlayers[0]) + " Or Player " + to_string(LeadingPlayers[1]) + " To Bring Back To Cell 1 ..");
		choosen = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		while (choosen != LeadingPlayers[0] && choosen != LeadingPlayers[1])
		{
			pGrid->GetOutput()->ClearStatusBar();
			pGrid->GetOutput()->PrintMessage("Invalid Player Entry .. Please Choose From Players " +to_string(LeadingPlayers[0]) + " Or " + to_string(LeadingPlayers[1]));
			choosen = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		}
	}
	else if(sizeArr==1) 
	{
		pGrid->PrintErrorMessage("Player " + to_string(LeadingPlayers[0]) + " Is Leading Player " + to_string(pPlayer->GetPlayerNum()) + " .. Click To Bring Back To Cell 1 ...");
		cases = 0;
	}
	
	else
	{
		cases = 2;
		pGrid->GetOutput()->PrintMessage("Choose Player " + to_string(LeadingPlayers[0]) + " Or Player " + to_string(LeadingPlayers[1]) +" Or Player " + to_string(LeadingPlayers[2]) +  " To Bring Back To Cell 1 ..");
		choosen = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		while (choosen != LeadingPlayers[0] && choosen != LeadingPlayers[1] && choosen != LeadingPlayers[2])
		{
			pGrid->GetOutput()->ClearStatusBar();
			pGrid->GetOutput()->PrintMessage("Invalid Player Entry .. Please Choose From Players " + to_string(LeadingPlayers[0]) + " Or " + to_string(LeadingPlayers[1]) + " Or " + to_string(LeadingPlayers[2]));
			choosen = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		}
	}

	CellPosition startCell(1);

	switch (cases)
	{
	case(0):
		pGrid->UpdatePlayerCell(pGrid->GetPlayerFromNum(LeadingPlayers[0]),startCell);
		pGrid->GetOutput()->PrintMessage("Player " + to_string(LeadingPlayers[0]) + " Back To Cell 1 ..");
		return;

	case(1):
		pGrid->UpdatePlayerCell(pGrid->GetPlayerFromNum(choosen),startCell);
		pGrid->GetOutput()->PrintMessage("Player " + to_string(choosen) + " Back To Cell 1 ..");
		return;

	case(2):
		pGrid->UpdatePlayerCell(pGrid->GetPlayerFromNum(choosen), startCell);
		pGrid->GetOutput()->PrintMessage("Player " + to_string(choosen) + " Back To Cell 1 ..");
		return;

	default:
		return;

	}

}


CardSeven::~CardSeven()
{
	// To avoid Being Abstarct
}