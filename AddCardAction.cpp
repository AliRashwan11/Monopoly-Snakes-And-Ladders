#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"



AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp),ReDrawSnake(0),ReDrawLadder(0)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	bool passed = 0;

	pOut->PrintMessage("Adding A Card .. Please Select The Card Number (1-8) ...");
	cardNumber=pIn->GetInteger(pOut);

	while (cardNumber> 8 || cardNumber < 1)
	{
		pOut->PrintMessage("Invalid Card Number .. Please Re-Enter A Number From 1 To 8 ...");
		cardNumber = pIn->GetInteger(pOut);
	}

	pOut->PrintMessage("Click On Cell Of Card ..");
	cardPosition = pIn->GetCellClicked();

	while (cardPosition.VCell() == -1)
	{
		pOut->PrintMessage("Invalid Cell .. Please Re-Click ...");
		cardPosition = pIn->GetCellClicked();
	}

	while (pManager->GetGrid()->GetHasObj(cardPosition.VCell(), cardPosition.HCell()))
	{
		pGrid->GetOutput()->PrintMessage("Invalid .. Cell Already Has An Object .. Please Re-Click");
		cardPosition = pIn->GetCellClicked();
		passed = 1;
	}

	if (pManager->GetGrid()->GetCrowded(cardPosition.VCell(), cardPosition.VCell(), cardPosition.HCell()))
	{
		if (pManager->GetGrid()->GetCrowdedOfSnake(cardPosition.VCell(), cardPosition.HCell()))
			ReDrawSnake = 1;
		else if (pManager->GetGrid()->GetCrowdedOfLadder(cardPosition.VCell(), cardPosition.HCell()))
			ReDrawLadder = 1;
	}

	

	pOut->ClearStatusBar();

	return;

	
}

void AddCardAction::Execute() 
{


	ReadActionParameters();

	
	

	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;

	case 2:
		pCard = new CardTwo(cardPosition);
		break;

	case 3:
		pCard = new CardThree(cardPosition);
		break;

	case 4:
		pCard = new CardFour(cardPosition);
		break;

	case 5:
		pCard = new CardFive(cardPosition);
		break;

	case 6:
	    pCard = new CardSix(cardPosition);
		break;

	case 7:
		pCard = new CardSeven(cardPosition);
		break;

	case 8:
		pCard = new CardEight(cardPosition);
		break;

	

		// allowed to add more cards to make game more interesting .. please do !

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{

		Grid* pGrid = pManager->GetGrid();

		pCard->ReadCardParameters(pGrid);

		bool valid = pGrid->AddObjectToCell(pCard);


		if (valid == 0)
			pGrid->PrintErrorMessage("Invalid Cell .. Objects Are Overlapping .. Click To Continue ...");
		
		return;
		
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

	if (ReDrawLadder == 1)
	{
		pManager->GetGrid()->GetOutput()->DrawLadder(cardPosition,cardPosition);
	}
	else if (ReDrawSnake == 1)
	{
		pManager->GetGrid()->GetOutput()->DrawSnake(cardPosition, cardPosition);
	}

}
