#include "CardNine.h"


CardNine::CardNine(const CellPosition& pos) :Card(pos)
{
	cardNumber = 9;
	pOwner = NULL;
	Price = 0;
	Fees = 0;
}


void CardNine::ReadCardParameters(Grid* pGrid)
{

	pGrid->GetOutput()->DrawCell(this->GetPosition(), 8);


	if (pGrid->GetHasACardNine()==0)
	{
		pGrid->PrintErrorMessage("Card Nine (Fire) Added To Cell " + to_string(position.GetCellNum()) + " .. Click To Continue ...");
		pGrid->GetOutput()->PrintMessage("Input Price Of One Cell Of Fire ..");
		Price = pGrid->GetInput()->GetInteger(pGrid->GetOutput());

		while (Price <= 0)
		{
			pGrid->GetOutput()->PrintMessage("Price Of Fire Cell Must Be A Positive Value .. Please Re-Enter ...");
			Price = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		}

		pGrid->GetOutput()->ClearStatusBar();
		pGrid->GetOutput()->PrintMessage("Input Fees For ByPassers Of Any Fire Cell ..");
		Fees = pGrid->GetInput()->GetInteger(pGrid->GetOutput());

		while (Fees <= 0)
		{
			pGrid->GetOutput()->PrintMessage("Fees Of ByPassing A Fire Cell Must Be A Positive Value .. Please Re-Enter ...");
			Fees = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
		}

		pGrid->SetHasACardNine(1);
	}
	else
		pGrid->PrintErrorMessage("Another Card Nine (Fire) Added To Cell " + to_string(position.GetCellNum()) + " .. Click To Continue ...");

	pGrid->SetCellWithCardNine(position,1);
}



void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	if (pOwner == NULL)
	{

		if (pPlayer->GetWallet() >= ((pGrid->CardNinesInGrid()) * Price))
		{
			pGrid->GetOutput()->PrintMessage("Do You Want To Own All Fire Cells (Card Nine Cells) ? .. (y/n)");
			string approval = pGrid->GetInput()->GetString(pGrid->GetOutput());
			pGrid->GetOutput()->ClearStatusBar();
			while (approval != "y" && approval != "n" && approval != "Y" && approval != "N")
			{
				pGrid->GetOutput()->PrintMessage("Invalid Answer .. Do You Want To Own All Fire Cell (Card Nine Cells) ?  (y/n)");
				string approval = pGrid->GetInput()->GetString(pGrid->GetOutput());
				pGrid->GetOutput()->ClearStatusBar();
			}

			if (approval == "y" || approval == "Y")
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - Price);
				pOwner = pPlayer;
				pGrid->SetOwnershipNine(pPlayer);
				pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " Now Owns All Fire Cells .. Click To Continue ...");
			}
			else
			{
				// nothing
			}

		}
		else
		{
			pGrid->GetOutput()->PrintMessage("Insufficient Funds .. Player " + to_string(pPlayer->GetPlayerNum()) + " Cannot Buy Fire Cells ...");
		}

	}
	else
	{
		pGrid->PrintErrorMessage("Fire Cell .. Player " + to_string(pPlayer->GetPlayerNum()) + " Has To Pay The Fee : " + to_string(Fees) + " ...");
		pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
		pOwner->SetWallet(pOwner->GetWallet() + Fees);
	}

	return;
}

void CardNine::SetOwner(Player* pPlayer)
{
	pOwner = pPlayer;
}

Player* CardNine::GetOwner() const
{
	return pOwner;
}


CardNine::~CardNine()
{
	// to avoid being abstract .. and avoid unexpected behaviour on deletion of base class pointer to derived class objects 
}