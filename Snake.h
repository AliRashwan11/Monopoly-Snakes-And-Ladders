#pragma once


#include "GameObject.h"


class GameObject;
class Grid;
class Player;





class Snake : public GameObject 
{

	

	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid*, Player*); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual ~Snake(); // Virtual destructor

};


