#include "Cell.h"

#include "Grid.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Snake.h"
#include "Player.h"

Cell::Cell(const CellPosition & pos) : position(pos),IsCrowded(0),CrowdedFromSnake(0),CrowdedFromLadder(0),HasSnakeHead(0),HasSnakeEnd(0),HasLadderEnd(0),hascardnine(0),hascardten(0),hascardeleven(0)
{
	// initializes the data members (position & pGameObject)
	pGameObject = NULL;
	owner = NULL;
}

Cell::Cell(int v, int h) : position(v, h),IsCrowded(0)
{
	
	pGameObject = NULL;
}





CellPosition Cell::GetCellPosition() const
{
	return position;
}

bool Cell::SetGameObject(GameObject * pGObj)
{
	if (pGameObject != NULL && pGObj != NULL) // already contains one
		return false; // do NOT add it and return false

	pGameObject = pGObj;
	return true;
}

GameObject * Cell::GetGameObject() const
{
	return pGameObject;
}

void Cell::SetIsCrowded(bool b)
{
	IsCrowded = b;
}


void Cell::SetHasSnakeHead(bool a)
{
	HasSnakeHead = a;
}

void Cell ::SetHasSnakeEnd(bool a)
{
	HasSnakeEnd = a;
}

void Cell::SetHasLadderEnd(bool a)
{
	HasLadderEnd = a;
}

void Cell::SetHasCardNine(bool b)
{
	hascardnine = b;
}

void Cell::SetHasCardTen(bool b)
{
	hascardten = b;
}

void Cell::SetHasCardEleven(bool b)
{
	hascardeleven= b;
}

bool Cell::GetHasCardNine() const
{
	return hascardnine;
}

bool Cell::GetHasCardTen() const
{
	return hascardten;
}

bool Cell::GetHasCardEleven() const
{
	return hascardeleven;
}


bool Cell::GetIsCrowded()
{
	return IsCrowded;
}

Ladder * Cell::HasLadder() const
{
	return dynamic_cast<Ladder *>(pGameObject);
}

Snake* Cell::HasSnake() const
{

	return dynamic_cast<Snake*>(pGameObject);

}

Card * Cell::HasCard() const
{

	return dynamic_cast<Card*>(pGameObject);
}

void Cell::SetOwnership(Player* pPlayer)
{
	owner = pPlayer;
}


void Cell::SetCrowdedFromLadder(bool a)
{
	CrowdedFromLadder = a;
}

void Cell::SetCrowdedFromSnake(bool a)
{
	CrowdedFromSnake = a;
}


bool Cell::GetCrowdedFromSnake()
{
	return CrowdedFromSnake;
}

bool Cell::GetCrowdedFromLadder()
{
	return CrowdedFromLadder;
}





void Cell::DrawCellOrCard(Output* pOut) const
{
	
	if (HasCard()) 
		pGameObject->Draw(pOut); // draw the card then
	else
		pOut->DrawCell(position, -1); // draw empty cell (no card -1)
}


void Cell::DrawLadderOrSnake(Output* pOut) const
{
	if (HasLadder() || HasSnake())
		pGameObject->Draw(pOut); // draw it either ladder or snake

}
