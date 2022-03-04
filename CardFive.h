#pragma once

#include "Card.h"

class CardFive : public Card
{
	// no sepcial data members ...

public:


	CardFive(const CellPosition&);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*, Player*);

	~CardFive();

};

