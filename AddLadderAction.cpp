#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp),startPos(-1,-1),endPos(-1,-1),validation1(0),validation2(0)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	CellPosition click;
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	while (startPos.VCell() == -1)
	{
		pOut->PrintMessage("Invalid Cell .. Please Re-Enter ...");
		startPos = pIn->GetCellClicked();
	}

	while (((startPos.VCell() == 8) && (startPos.HCell() == 0)) || ((startPos.VCell()==0) && (startPos.HCell()==10)))
	{
		pOut->PrintMessage("Start Cell Of Ladder Cant Be Cell 1 Or 99 .. Please Re-Click ...");
		startPos = pIn->GetCellClicked();
	}

	// Read the endPos parameter
	pOut->PrintMessage("Click On Appropriate End Cell ...");
	endPos = pIn->GetCellClicked();

	while (endPos.VCell() == -1)
	{
		pOut->PrintMessage("Invalid Cell .. Please Re-Click ...");
		endPos = pIn->GetCellClicked();
	}

	

	///TODO: Make the needed validations on the read parameters

	bool v11 = 0;
	bool v12 = 0;

// 1st .. validate points are vertical and correct << validation1 >>

	int startH = startPos.HCell();
	int endH = endPos.HCell();
	int startV = startPos.VCell();
	int endV = endPos.VCell();


	if (startH == endH)
		v11 = 1;
	else
	{
		pGrid->PrintErrorMessage("Invalid .. The Ladder Must Be Vertical .. Click To Continue ...");
		click = pIn->GetCellClicked();
		pOut->ClearStatusBar();
	    return;
	}
	if (startV > endV)
		v12 = 1;
	else
	{
		pGrid->PrintErrorMessage("Invalid .. End Of Ladder Must Be Above The Start Of The Ladder .. Click To Continue ...");
		click = pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}

	if (v11 == 1 && v12 == 1)
		validation1 = 1;


	

	// 2nd .. validation for no overlapping

	validation2=pManager->GetGrid()->GetCrowded(startV, endV, endH);

	if (validation2 == 1)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Invalid .. Objects Are Overlapping .. Click To Continue ... ");
		click = pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}

	// both validation are clear

	if (validation1 == 1 && validation2 == 0)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Ladder Added ! .. ");
		pGrid->SetCrowded(startV,endV,endH);
		pGrid->SetCrowdedOfLadder(startV,endV,endH,1);
		pGrid->SetHasLadderEnd(startPos.VCell(),startPos.HCell(),1);
		pGrid->SetHasLadderEnd(endPos.VCell(),endPos.HCell(),1);
		return;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return;
}


void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if (validation1 == 1 && validation2 == 0)
	{
		// Create a Ladder object with the parameters read from the user
		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pLadder);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

	}

}
