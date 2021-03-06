#pragma once 

#include "UI_Info.h"
#include "CellPosition.h"


// Class forward declarations (their #include is in the .cpp file)
class Grid;
class Output;
class GameObject;
class Ladder;
class Snake;
class Card;
class Player;
class CardNine;
class CardTen;
class CardEleven;

class Cell
{
	const CellPosition position;	// the cell position (vCell and hCell) --> will not change after the Cell is constructed

	GameObject * pGameObject;       // a pointer to the GameObject existing in the Cell (if any)
	                                // if no GameObject in this Cell, pGameObject should be NULL

	bool IsCrowded;

	bool CrowdedFromSnake;
	bool CrowdedFromLadder;

	bool HasLadderEnd;
	bool HasSnakeEnd;
	bool HasSnakeHead;

	bool hascardnine;
	bool hascardten;
	bool hascardeleven;

	Player* owner;

public:

	Cell(const CellPosition & pos); // A constructor initializes the cell position with the passed CellPosition
	Cell(int v, int h);		        // A constructor initializes the cell position with the passed vCell and hCell

	
	CellPosition GetCellPosition() const;   
	
	bool SetGameObject(GameObject * pGObj);	
	                                        
	GameObject * GetGameObject() const;    

	void SetIsCrowded(bool);
	bool GetIsCrowded();

	void SetHasLadderEnd(bool);
	void SetHasSnakeHead(bool);
	void SetHasSnakeEnd(bool);

	bool GetHasCardNine() const;
	bool GetHasCardTen() const;
	bool GetHasCardEleven() const;

	void SetCrowdedFromLadder(bool);
	bool GetCrowdedFromLadder();

	void SetHasCardNine(bool);
	void SetHasCardTen(bool);
	void SetHasCardEleven(bool);

	void SetOwnership(Player*);

	void SetCrowdedFromSnake(bool);
	bool GetCrowdedFromSnake();
		
	Ladder * HasLadder() const;	// Checks if pGameObject is a Ladder Then returns it if a ladder or returns NULL if not ladder
	Snake * HasSnake() const;	// Checks if pGameObject is a Snake Then returns it if a snake or returns NULL if not snake
	Card * HasCard() const;	    // Checks if pGameObject is a Card Then returns it if a card or returns NULL if not card
	

	
	// ======= Drawing Functions ======= 

	void DrawCellOrCard(Output* pOut) const;	// Draws the Cell either has Card or No Card (No ladders/snakes are drawn here)
	void DrawLadderOrSnake(Output* pOut) const;	// Draws the Ladder/Snake of the Cell if found
	                                            // The two Draw functions are separated because we should draw all cells first
	                                            // then draw all ladders/snake, in order to avoid overlapping 
	                                            // or drawing cell's background over existing ladders/snakes
};

