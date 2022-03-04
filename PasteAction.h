#pragma once
#include "Action.h"



class PasteAction : public Action
{

protected:

	CellPosition clicked;

public:

	PasteAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~PasteAction();

};

