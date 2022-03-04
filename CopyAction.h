#pragma once
#include "Action.h"


class CopyAction : public Action
{

protected:


	Card* CopiedCard;


public:

	CopyAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~CopyAction();

};

