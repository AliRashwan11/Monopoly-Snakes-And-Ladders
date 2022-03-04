#include "AddSnakeAction.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) :Action(pApp), startPos(-1, -1), endPos(-1, -1), validation1(0), validation2(0)
{

}

void AddSnakeAction::ReadActionParameters()
{

	CellPosition click;
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	while (startPos.VCell() == -1)
	{
		pOut->PrintMessage("Invalid Cell .. Please Re-Enter ...");
		startPos = pIn->GetCellClicked();
	}

	while ((startPos.VCell() == 0) && (startPos.HCell()==10))
	{
		pOut->PrintMessage("Start Cell Of Snake Cannot Be Last Cell Of Grid .. Please Re-Click ...");
		startPos = pIn->GetCellClicked();
	}

	// Read the endPos parameter
	pOut->PrintMessage("Click On Appropriate End Cell ...");
	endPos = pIn->GetCellClicked();

	while (endPos.VCell() == -1)
	{
		pOut->PrintMessage("Invalid Cell .. Please Re-Enter ...");
		endPos = pIn->GetCellClicked();
	}


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
		pGrid->PrintErrorMessage("Invalid .. The Snake Must Be Vertical .. Click To Continue ...");
		click = pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}


	if (startV < endV)
		v12 = 1;
	else
	{
		pGrid->PrintErrorMessage("Invalid .. End Of Snake Must Be Below The Start Of The Ladder .. Click To Continue ...");
		click = pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}

	if (v11 == 1 && v12 == 1)
		validation1 = 1;



	validation2 = pManager->GetGrid()->GetCrowded(endV,startV, endH);

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
		pManager->GetGrid()->GetOutput()->PrintMessage("Snake Added ! ");
		pGrid->SetCrowded(endV,startV,endH);
		pGrid->SetCrowdedOfSnake(endV, startV, endH, 1);
		pGrid->SetHasSnakeHead(startPos.VCell(),startPos.HCell(),1);
		pGrid->SetHasSnakeEnd(endPos.VCell(),endPos.HCell(),1);
		return;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return;


}



void AddSnakeAction::Execute()
{


	ReadActionParameters();

	if (validation1 == 1 && validation2 == 0)
	{
		
		Snake* pSnake = new Snake(startPos,endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		
		bool added = pGrid->AddObjectToCell(pSnake);

		// if the GameObject cannot be added
		if (!added)
		{
			
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		

	}
}



AddSnakeAction::~AddSnakeAction()
{
	// avoiding being an abstract class
}

