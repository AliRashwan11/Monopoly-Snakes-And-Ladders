#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum), justRolledDiceNum(0),Card4Penalty(0),Card4PenaltyCounter(0),Imprisoned(0),ImprisonedCounter(0),HasCardNine(0),HasCardTen(0),HasCardEleven(0)
{
	this->pCell = pCell;
	this->turnCount = 0;

	
}


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

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}