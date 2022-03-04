#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum);
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v <= 8)
	{
		this->vCell = v;
		return true;
	}
	else
	{
		this->vCell = -1;
		return false;
	}


}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h <= 10)
	{
		this->hCell = h;
		return true;
	}
	else
	{
		this->hCell = -1;
		return false;
	}
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::isVvalid() const
{
	if (this->vCell >= 0 && this->vCell <= 8)
		return true;
	return false;
}

bool CellPosition::isHvalid() const
{
	if (this->hCell >= 0 && this->hCell <= 10)
		return true;
	return false;
}

bool CellPosition::IsValidCell() const
{
	bool vIsValid = this->isHvalid();
	bool hIsValid = this->isVvalid();

	if (vIsValid == 1 && hIsValid == 1)
		return true;
	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this);
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	int v = cellPosition.VCell();
	int h = cellPosition.HCell();

	int step = 8 - v;
	int cellnum = (step * 10) + h + step + 1;

	if (cellnum > 0 && cellnum < 100)
		return cellnum;

	return 0;
}


CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	if (cellNum > 99 || cellNum < 1)
	{
		CellPosition position2(-1, -1);
		return position2;
	}
	else
	{
		int a = 8;                                                                                     //a is vCell           b is hCell
		int b = 0;

		for (int i = 0; i < cellNum; i++)
		{


			if (b == 11)
			{
				b = 0;
				a--;
			}
			b++;

		}
		b--;
		CellPosition position(a, b);
		return position;
	}
}

void CellPosition::SetCell(CellPosition& position)
{
	int v = position.VCell();
	int h = position.HCell();
	this->SetVCell(v);
	this->SetHCell(h);
}

void CellPosition::AddCellNum(int addedNum)
{
	int finalcell = this->GetCellNum() + addedNum;
	CellPosition position;
	if (finalcell >= 100)
	{
		position.SetHCell(10);
		position.SetVCell(8);
	}
	else if (finalcell < 1)
	{
		position.SetHCell(0);
		position.SetVCell(8);
	}
	else
	{
		position = this->GetCellPositionFromNum(finalcell);
	}

	this->SetCell(position);
}