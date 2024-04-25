#include "Object.h"

HBITMAP Poop::bitmap = nullptr;



//------------------------------------Player-------------------------------------------

HBITMAP Player::bitmap[]{ nullptr, };


void Player::Stop()
{
	this->status++;
	this->status %= 3;
}

void Player::MoveL()
{
	this->status++;
	this->status %= 3;
	this->status += 3;
}

void Player::MoveR()
{
	this->status++;
	this->status %= 3;
	this->status += 6;
}

void Player::Move(float x,float y)
{
	this->x += x;
	this->y += y;
}

