#include "ActionDeleteObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Snake.h"

ActionDeleteObject::ActionDeleteObject(ApplicationManager* pApp) : Action(pApp)
{

}



void ActionDeleteObject::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("Removing An Object .. Click On Object Cell ...");
}

void ActionDeleteObject::Execute()
{

	ReadActionParameters();
	CellPosition beginning(-1, -1);
	CellPosition end(-1, -1);
	Grid* pGrid = pManager->GetGrid();                   // grid pointer
	Output* pOut = pGrid->GetOutput();                   // output pointer
	Input* pIn = pGrid->GetInput();

	CellPosition ClickedCell;

	ClickedCell=pIn->GetCellClicked();

	if (pGrid->CellAvailability(ClickedCell)==1)                 // ladder
	{
		Ladder* pLadder= pGrid->GetLadderObject(ClickedCell);
		beginning=pLadder->GetPosition();
		end = pLadder->GetEndPosition();
    	pGrid->SetNotCrowded(beginning.VCell(),end.VCell(),end.HCell());
		pGrid->SetCrowdedOfLadder(beginning.VCell(), end.VCell(), end.HCell(), 0);
		pGrid->SetHasLadderEnd(end.VCell(),end.HCell(),0);
		pGrid->RemoveObjectFromCell(ClickedCell);
		pOut->PrintMessage("Ladder Removed From Cell ...");
		return;
	}
	else if (pGrid->CellAvailability(ClickedCell) == 2)               // snake
	{
		Snake* pSnake = pGrid->GetSnakeObject(ClickedCell);
		beginning = pSnake->GetPosition();
		end = pSnake->GetEndPosition();
		pGrid->SetNotCrowded(end.VCell(),beginning.VCell(),end.HCell());
		pGrid->SetCrowdedOfSnake(end.VCell(), beginning.VCell(), end.HCell(), 0);
		pGrid->SetHasSnakeEnd(end.VCell(),end.HCell(),0);
		pGrid->SetHasSnakeHead(beginning.VCell(), beginning.HCell(),0);
		pGrid->RemoveObjectFromCell(ClickedCell);
		pOut->PrintMessage("Snake Removed From Cell ...");
		return;
	}
	else if (pGrid->CellAvailability(ClickedCell) == 3)                          // Card
	{
		Card* pCard = pGrid->GetCardObject(ClickedCell);
		beginning = pCard->GetPosition();
		pGrid->SetNotCrowded(beginning.VCell(),beginning.VCell(),beginning.HCell());
		//pGrid->SetHasLadderEnd(beginning.VCell(),beginning.HCell(),0);
		//pGrid->SetHasLadderEnd(end.VCell(), end.HCell(), 0);
		pGrid->RemoveObjectFromCell(ClickedCell);
		pOut->PrintMessage("Card removed From Cell ...");
		return;
	}
	

	pGrid->PrintErrorMessage("Cell Is Not A Starting Cell Of A Game Object .. Click To Continue ...");
}



ActionDeleteObject::~ActionDeleteObject()
{

}