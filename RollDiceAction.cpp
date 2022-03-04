
#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include <string.h>

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{

}


void RollDiceAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Player* pPlayer = pGrid->GetCurrentPlayer();
	if (pGrid->GetEndGame() == 1)
	{
		int player = pGrid->GetCurrentPlayer()->GetPlayerNum();
		string playerstr = to_string(player);
		pGrid->GetOutput()->PrintMessage("The Game Has Ended .. Player " + playerstr + " Has Won The Game !");
	}
	else
	{
		srand((int)time(NULL)); // time is for different seed each run
		int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
		string diceNumberStr = to_string(diceNumber);
		string playerNumStr = to_string(pGrid->GetCurrentPlayer()->GetPlayerNum());
		if ((pGrid->GetCurrentPlayer()->GetTurnCount())!=2)
			pGrid->GetOutput()->PrintMessage("Player " + playerNumStr + " : You Rolled " + diceNumberStr);
		else
		{
			if (pPlayer->GetImprisoned())
				if (pPlayer->GetImprisonedCounter()!=2)
					pGrid->GetOutput()->PrintMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Imprisoned .. Can't Take Money .. Has " + to_string(3- pPlayer->GetImprisonedCounter()) + " Rounds Left In Prison");
				else
					pGrid->GetOutput()->PrintMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Imprisoned .. Can't Take Money .. Has " + to_string(1) + " Round Left In Prison");
			else
				pGrid->GetOutput()->PrintMessage("Player " + playerNumStr + " : We Are Filling Up Your Wallet");

		}
		pPlayer->Move(pGrid, diceNumber);
		pGrid->AdvanceCurrentPlayer();

	}

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action

	// -- If not ended, do the following --:

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	// srand((int)time(NULL)); // time is for different seed each run
	// int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

	// 3- Get the "current" player from pGrid

	// 4- Move the currentPlayer using function Move of class player

	// 5- Advance the current player number of pGrid


	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}




RollDiceAction::~RollDiceAction()
{
}






