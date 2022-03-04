#include "InputDiceAction.h"


InputDiceAction::InputDiceAction(ApplicationManager* pApp) : Action(pApp),InputDice(0)
{

}


void InputDiceAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Player* pPlayer = pGrid->GetCurrentPlayer();

	ReadActionParameters();
	Grid* pG = pManager->GetGrid();
	int currentPlayerNum = pG->GetCurrentPlayer()->GetPlayerNum();
	string currentPlayerNumStr = to_string(currentPlayerNum);
	if (pG->GetCurrentPlayer()->GetTurnCount() != 2)
		pG->GetOutput()->PrintMessage("Player " + currentPlayerNumStr + " Has Moved " + to_string(InputDice) + " Via Input ..");
	else
	{
		if (pPlayer->GetImprisoned() == 0)
			pG->GetOutput()->PrintMessage("Player " + currentPlayerNumStr + " Has Added " + to_string(InputDice * 10) + " Coins To His Wallet Via Input ..");
		else
		{
			if (pPlayer->GetImprisonedCounter() != 2)
				pG->PrintErrorMessage("Player " + currentPlayerNumStr + " Cannot Add Money To Wallet .. " +to_string(3- pPlayer->GetImprisonedCounter())+ " Rounds Left In Prison .. Click To Continue ...");
			else
				pG->PrintErrorMessage("Player " + currentPlayerNumStr + " Cannot Add Money To Wallet .. " + to_string(1) + " Round Left In Prison .. Click To Continue ...");

		}
	}




	pG->GetCurrentPlayer()->Move(pG, InputDice);
	pG->AdvanceCurrentPlayer();
}



void InputDiceAction::ReadActionParameters()
{
	
	Output* pO=pManager->GetGrid()->GetOutput();
	pO->PrintMessage("Input Dice Number To Roll ..");
	InputDice=pManager->GetGrid()->GetInput()->GetInteger(pO);


    while (InputDice > 6 || InputDice < 0)
 {
	 pO->PrintMessage("Invalid Entry .. Enter Number Between 0 and 6 :");
	 InputDice = pManager->GetGrid()->GetInput()->GetInteger(pO);
 }

}



InputDiceAction::~InputDiceAction()
{

}

