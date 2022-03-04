#pragma once

#include "Action.h"

class AddLadderAction : public Action
{

	CellPosition startPos; // The start position of the ladder
	CellPosition endPos;   // The end position of the ladder
	bool validation1;      // validation for verticality
	bool validation2;      // validation for overlapping



public:

	AddLadderAction(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (startPos, endPos)
	
	virtual void Execute(); // Creates a new Ladder Object 
	                        // then Sets this Ladder object to the GameObject Pointer of its Cell
	

	virtual ~AddLadderAction(); // Virtual Destructor

};

