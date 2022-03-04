#pragma once

#include "Player.h"
#include "Grid.h"


class Grid;
class Player;

// Base Class for All Game Objects ( ladders, snakes and cards )
class GameObject
{

protected:

	CellPosition position; // The current cell position of the GameObject
	
public:

	GameObject(const CellPosition & pos); 
	
	CellPosition GetPosition() const;     

	void SetPosition(CellPosition);

	

	virtual void Draw(Output* pOut) const = 0;	 // Draws the game object in the window in his position cell 
											     // (drawing depends on GameObject Type, so virtual)

	virtual void Apply(Grid* pGrid, Player* pPlayer) = 0;  // Applys the effect of the GameObject on the passed Player
	                                                       // (The effect depends on the GameObject type, so virtual)
	                                                       // For example, applying a ladder is by moving player up, and so on




	
	//virtual void Save(ofstream &OutFile) = 0;	// Saves the GameObject parameters to the file  // to be done later
	//virtual void Load(ifstream &Infile) = 0;	// Loads and Reads the GameObject parameters from the file

	virtual ~GameObject(); // Virtual destructor
};

