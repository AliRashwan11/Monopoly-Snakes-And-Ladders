#include "NewGame.h"

NewGame::NewGame(ApplicationManager* pApp):Action(pApp)
{
	acceptance = "n";
}


void NewGame::ReadActionParameters()
{
	// no parameters to read from user
	pManager->GetGrid()->GetOutput()->PrintMessage("Are You Sure You Want To Start A New Game ? (y/n)");
	acceptance = pManager->GetGrid()->GetInput()->GetString(pManager->GetGrid()->GetOutput());
	if (acceptance != "y" && acceptance !="yes" && acceptance != "Y" && acceptance != "Yes")
	{
		pManager->GetGrid()->PrintErrorMessage("Resetting Game Denied .. Click To Continue ...");
	}
	pManager->GetGrid()->GetOutput()->ClearStatusBar();
}

void NewGame::Execute()
{
	ReadActionParameters();
	if (acceptance != "y" && acceptance != "yes" && acceptance != "Y" && acceptance != "Yes")
	{
	}
	else
	{
		Grid* pGrid = pManager->GetGrid();
		pGrid->UpdateInterface();
		CellPosition start;
		start.SetVCell(8);
		start.SetHCell(0);
		for (int i = 0; i < 4; i++)
		{
			Player* p = pGrid->GetCurrentPlayer();
			p->SetWallet(100);
			p->SetTurnCount(0);
			pGrid->AdvanceCurrentPlayer();
			pGrid->UpdatePlayerCell(p, start);

		}
		pGrid->ResetToPlayer0();
		pGrid->SetEndGame(false);
	}
	
}

NewGame::~NewGame()
{

}