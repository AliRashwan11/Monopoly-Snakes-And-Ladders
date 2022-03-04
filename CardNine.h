#pragma once

#include "Card.h"

class CardNine :  public Card
{

	Player* pOwner;
	int Price;
	int Fees;

public:

	CardNine(const CellPosition&);

	virtual void ReadCardParameters(Grid*);

	virtual void Apply(Grid*,Player*);

	void SetOwner(Player*);

	Player* GetOwner()const;

	virtual ~CardNine();

};

