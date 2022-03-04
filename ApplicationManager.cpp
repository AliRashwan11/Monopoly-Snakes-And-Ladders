#include "ApplicationManager.h"

#include "Grid.h"
#include "AddLadderAction.h"
#include "AddCardAction.h"
#include "AddSnakeAction.h"
#include "ActionDeleteObject.h"
#include "RollDiceAction.h"
#include "InputDiceAction.h"
#include "CopyAction.h"
#include "PasteAction.h"
#include "NewGame.h"



ApplicationManager::ApplicationManager()
{
	
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}



ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}



Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}



ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}



// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case EXIT_DESIGN_MODE:
		break;

	case EXIT_PLAY_MODE:
		break;

	case TO_PLAY_MODE:
		pOut->CreatePlayModeToolBar(); 
		break;

	case ROLL_DICE:
		pAct = new RollDiceAction(this);
		break;

	case TO_DESIGN_MODE:
		pOut->CreateDesignModeToolBar(); 
		break;

	case INPUT_DICE:
		pAct = new InputDiceAction(this);
		break;

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case DELETE_OBJECT:
		pAct = new ActionDeleteObject(this);
		break;

	case NEW_GAME:
		pAct = new NewGame(this);
		break;

	//case COPY_CARD:
		//pAct = new CopyAction(this);
		//break;
	//case PASTE_CARD:
		//pAct = new PasteAction(this);
		//break;











	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 
		pAct = NULL;
	}
}
