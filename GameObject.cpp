#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; 
}

void GameObject::SetPosition(CellPosition pos)
{
	position = pos;
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

GameObject::~GameObject()
{
}