#pragma once

#include "Card.h"

class CardFour : public Card
{
	// no special data members

public:


	CardFour(const CellPosition&);
	virtual void ReadCardParameters(Grid*);
	virtual void Apply(Grid*, Player*);
	virtual ~CardFour();

};

