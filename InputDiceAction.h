#pragma once
#include "Action.h"



class InputDiceAction : public Action
{
	int InputDice;

public:

	InputDiceAction(ApplicationManager* pApp);

	virtual void Execute();

	virtual void ReadActionParameters();

	virtual ~InputDiceAction();


};

