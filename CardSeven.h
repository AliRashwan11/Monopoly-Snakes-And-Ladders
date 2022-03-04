#pragma once

#include "Card.h"

class CardSeven : public Card
{
	// no exclusive data members for this card

public:

	CardSeven(const CellPosition&);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*, Player*);

	virtual ~CardSeven();

};

