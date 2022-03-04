#include "CopyAction.h"

CopyAction::CopyAction(ApplicationManager* pApp) :Action(pApp)
{

}



void CopyAction::ReadActionParameters()
{
	pManager->GetGrid()->GetOutput()->PrintMessage("Click On Card You Want To Copy ..");

	CellPosition clicked = pManager->GetGrid()->GetInput()->GetCellClicked();

	

	while (clicked.VCell()==-1)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Invalid Click .. Please Re-Click ...");
        clicked = pManager->GetGrid()->GetInput()->GetCellClicked();
	}

	while (pManager->GetGrid()->CellHasCard(clicked.VCell(), clicked.HCell()) == 0)
	{
		pManager->GetGrid()->GetOutput()->PrintMessage("Clicked Cell Has No Card .. Please Re-Click ...");
		clicked = pManager->GetGrid()->GetInput()->GetCellClicked();
	}


	CopiedCard = pManager->GetGrid()->GetCardObject(clicked);
	pManager->GetGrid()->GetOutput()->PrintMessage("Card Copied !");

}

void CopyAction::Execute()
{
	ReadActionParameters();

	pManager->GetGrid()->SetClipboard(CopiedCard);

}



CopyAction::~CopyAction()
{

}


