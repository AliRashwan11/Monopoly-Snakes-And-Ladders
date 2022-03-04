#include "Card.h"


Card::Card(const CellPosition & pos) : GameObject(pos),cardNumber(0) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = cnum; // needs validation
}

void Card::SetPosition(CellPosition pos)
{
	this->SetPosition(pos);
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	pOut->DrawCell(position,cardNumber);
}

CellPosition Card::GetPosition()
{
	return position;
}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

Card::~Card()
{
}
