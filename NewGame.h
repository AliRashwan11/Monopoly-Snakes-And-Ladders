#pragma once
#include "Action.h"


class NewGame : public Action
{
	string acceptance;

public:

	NewGame(ApplicationManager*);

	void ReadActionParameters();

	void Execute();

	~NewGame();

};

