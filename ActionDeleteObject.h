#pragma once
#include "Action.h"


class ActionDeleteObject : public Action
{

	CellPosition objectCell;

public:

	ActionDeleteObject(ApplicationManager*);

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Ladder Object 
							// then Sets this Ladder object to the GameObject Pointer of its Cell

	virtual ~ActionDeleteObject();

};

