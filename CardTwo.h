#pragma once

#include "Card.h"


class CardTwo : public Card
{

	// no special data members

public:

	CardTwo(const CellPosition &);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*,Player*);

	virtual ~CardTwo();


};

