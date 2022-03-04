#include "CardOne.h"
#include <string>

CardOne::CardOne(const CellPosition & pos) : Card(pos) 
{
	cardNumber = 1; 
}


CardOne::~CardOne(void)
{
}


void CardOne::ReadCardParameters(Grid * pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter Value To Decrement From Wallet Of Players :");
	walletAmount = pIn->GetInteger(pOut);

	while (walletAmount > 999)
	{
		pOut->PrintMessage("Value Too High .. Please Re-Enter ...");
		walletAmount=pIn->GetInteger(pOut);
	}

	if   (walletAmount < 0)
		pGrid->PrintErrorMessage("Negative Value Entered .. So Card Will Add To Players Wallet .. Click To Continue ... ");

	pOut->DrawCell(this->GetPosition(),1);
	pGrid->PrintErrorMessage("Card One Added To Cell " + to_string(this->GetPosition().GetCellNum()) + " .. Click To Continue ...");


	pOut->ClearStatusBar();
	


}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	Card::Apply(pGrid,pPlayer);

	pPlayer->SetWallet(pPlayer->GetWallet()-walletAmount);

	if (walletAmount < 0)
		pGrid->PrintErrorMessage(to_string(walletAmount* -1) + " Coins Added To Player " + to_string(pPlayer->GetPlayerNum()) + " Wallet .. Click To Continue ...");
	else 
		pGrid->PrintErrorMessage(to_string(walletAmount) + " Coins Removed From Player " + to_string(pPlayer->GetPlayerNum()) + " Wallet .. Click To Continue ...");


}
