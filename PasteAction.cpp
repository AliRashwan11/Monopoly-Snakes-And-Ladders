#include "PasteAction.h"
#include "Card.h"

PasteAction::PasteAction(ApplicationManager* pApp) :Action(pApp)
{
	clicked = (-1,-1);
}


void PasteAction::ReadActionParameters()
{

	pManager->GetGrid()->GetOutput()->PrintMessage("Click On Cell You Want To Paste Card On ...");

	clicked = pManager->GetGrid()->GetInput()->GetCellClicked();

	while (clicked.IsValidCell()==0 )
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Cell Out Of Reach.. Please Re-Click ...");
		clicked = pManager->GetGrid()->GetInput()->GetCellClicked();
	}
	while (pManager->GetGrid()->CellAvailability(clicked) != 0)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Busy Cell .. Please Re-Click ...");
		clicked = pManager->GetGrid()->GetInput()->GetCellClicked();
	}

	pManager->GetGrid()->PrintErrorMessage("Card Pasted .. Click To Continue ...");


}


void PasteAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();

	Card* pCard =pGrid->GetClipboard();

	pCard->SetPosition(clicked);

	pGrid->AddObjectToCell(pCard);

}


PasteAction::~PasteAction()
{

}