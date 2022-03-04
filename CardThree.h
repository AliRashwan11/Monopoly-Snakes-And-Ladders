#pragma once

#include "Card.h"

class CardThree : public Card
{


public:


	CardThree(const CellPosition&);

	virtual void Apply(Grid*,Player*);

	virtual void ReadCardParameters(Grid*);

	virtual ~CardThree();

};

