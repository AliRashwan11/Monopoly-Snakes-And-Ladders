#include "Input.h"

#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}


void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);
}


string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


int Input::GetInteger(Output* pO) const
{
	string str = this->GetString(pO);
	int enteredNum = stoi(str);

	return enteredNum;
}


ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{

			int ClickedItemOrder = (x / UI.MenuItemWidth);


			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_EXIT_DESIGN_MODE: return EXIT_DESIGN_MODE;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;
			//case ITM_COPY_CARD: return COPY_CARD;
			//case ITM_PASTE_CARD: return PASTE_CARD;
			//case ITM_SAVE_GRID: return SAVE_GRID;
			//case ITM_OPEN_GRID: return OPEN_GRID;
			case ITM_DELETE_OBJECT: return DELETE_OBJECT;





			default: return EMPTY;
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}


	else
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_INPUT_DICE_NUMBER: return INPUT_DICE;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			case ITM_EXIT_PLAY_MODE: return EXIT_PLAY_MODE;
			default: return EMPTY;
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}
	}
}


CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);

	CellPosition cellPos;
	int v = -1;
	int h = -1;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{

			v = (y - UI.ToolBarHeight) / UI.CellHeight;                                                   // integer division leads to flooring
			h = x / UI.CellWidth;
		}
		else
		{
			v = -1;
			h = -1;
		}
	}

	cellPos.SetHCell(h);
	cellPos.SetVCell(v);

	return cellPos;
}

