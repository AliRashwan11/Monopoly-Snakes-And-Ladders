#pragma once

#include "Card.h"

class CardSix :  public Card
{
	CellPosition ToMoveTo;

public:

	CardSix::CardSix(const CellPosition&);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*, Player*);

	virtual ~CardSix();


};

