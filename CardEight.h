#pragma once

#include "Card.h"

class CardEight : public Card
{
	int PrisonFee;

public:

	CardEight(const CellPosition&);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*, Player*);

	virtual ~CardEight();

};

