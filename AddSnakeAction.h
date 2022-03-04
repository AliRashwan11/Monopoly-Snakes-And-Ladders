#pragma once
#include "Action.h"


class AddSnakeAction : public Action
{
	bool validation1;
	bool validation2;
	CellPosition startPos;
	CellPosition endPos;


public:

	AddSnakeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~AddSnakeAction();

};

