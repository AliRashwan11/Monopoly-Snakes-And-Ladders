#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum), justRolledDiceNum(0),Card4Penalty(0),Card4PenaltyCounter(0),Imprisoned(0),ImprisonedCounter(0),HasCardNine(0),HasCardTen(0),HasCardEleven(0)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetHasCardNine(bool b)
{
	HasCardNine = b;
}

void Player::SetHasCardTen(bool b)
{
	HasCardTen = b;
}

void Player::SetHasCardEleven(bool b)
{
	HasCardEleven = b;
}

bool Player::GetHasCardNine() const
{
	return HasCardNine;
}

bool Player::GetHasCardTen() const
{
	return HasCardTen;
}

bool Player::GetHasCardEleven() const
{
	return HasCardEleven;
}



int Player::GetJustRolledDiceNum() const
{
	return justRolledDiceNum;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

void Player::SetTurnCount(int a)
{
	if (a >= 0 && a <= 2)
		turnCount = a;
	else
		turnCount = 0;

}

void Player::SetCard4Penalty(bool a)
{
	this->Card4Penalty = a;
}

void Player::SetImprisoned(bool b)
{
	this->Imprisoned = b;
}

int Player::GetWallet() const
{
	return wallet;
}

bool Player::GetImprisoned() const
{
	return Imprisoned;
}

int Player::GetPlayerNum() const
{
	return playerNum;
}

int Player::GetImprisonedCounter() const
{
	return ImprisonedCounter;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

// ====== Drawing Functions ======
 
void Player::Draw(Output* pOut) const                                                              // draws player on the cell it is on
{
	CellPosition CurrentPos = pCell->GetCellPosition();
	pOut->DrawPlayer(CurrentPos,playerNum,UI.PlayerColors[playerNum]);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}



// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)                                                 // responsible for all movement in game
{

	Output* pOut = pGrid->GetOutput();
	bool turnToRecharge = 0;                                                                     // prevents motion when turnCount=3
	bool HasReachedCell99 = 0;                                                                   // recognizes reaching player to final cell


	turnCount++;

	justRolledDiceNum = diceNumber;




	if (turnCount == 3 )
	{
		turnCount = 0;
		turnToRecharge = 1;


		if ((Card4Penalty == 0 || (Card4Penalty == 1 && Card4PenaltyCounter == 1)))
		{
			if (Imprisoned==0)
			{
				wallet += justRolledDiceNum * 10;
			}
		}


	}



	if (turnToRecharge == 0 )
	{
		if ((Card4Penalty == 0 || Card4PenaltyCounter==1 ) )
		{
			if (Imprisoned == 0)
			{
				CellPosition CurrentPos = pCell->GetCellPosition();
				int CurrentCellNum = CurrentPos.GetCellNum();

				CurrentCellNum = justRolledDiceNum + CurrentCellNum;

				if (CurrentCellNum > 99)
				{
					CurrentCellNum = 99;
					HasReachedCell99 = 1;
				}

				stepCount = CurrentCellNum;

				const CellPosition UpdatedPos(CurrentCellNum);
				pGrid->UpdatePlayerCell(this, UpdatedPos);

				if (pCell->HasCard() || pCell->HasLadder() || pCell->HasSnake())                            // checks for game objects and applies if found 
				{
					pCell->GetGameObject()->Apply(pGrid, this);
				}

				Card4PenaltyCounter = 0;
			}
			else
			{
				if (ImprisonedCounter != 2)
					pOut->PrintMessage("Player " + to_string(this->GetPlayerNum()) + " Imprisoned .. Has " + to_string(3 - ImprisonedCounter) + " Rounds Left In Prison ..");
				else
					pOut->PrintMessage("Player " +to_string(this->GetPlayerNum()) + " Imprisoned .. Has " +to_string(1) + " Round Left In Prison");

				ImprisonedCounter++;
				if (ImprisonedCounter == 3)
					Imprisoned = 0;
			}
		}
		else
		{
			Card4PenaltyCounter = 1;
			Card4Penalty = 0;
			pOut->PrintMessage("Player " + to_string(this->GetPlayerNum()) + " Prohibited From Rolling Dice");
		}

	}
	else
	{
		if (Imprisoned == 1)
			ImprisonedCounter++;
	}
	   
	if (HasReachedCell99 == 1)                                                                     // checks if a player has won .. sets end game if so ..
	{
		pGrid->SetEndGame(1);
	}
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once  
	
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	
	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	// 6- Apply() the game object of the reached cell (if any)

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}