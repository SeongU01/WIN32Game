#pragma once
#include"TimeSystem.h"
#include"InputSystem.h"
#include<cstdio>
#define MAX_POOP 50

class Object
{
public:
	float x = 0;
	float y = 0;
	float speed = 0;
	int status = 0;

	virtual HBITMAP GetBitMap(int index) = 0;

};

class Poop: public Object
{
public:
	static HBITMAP bitmap;
	Poop()
	{
	}
	~Poop()
	{
	}
	HBITMAP GetBitMap(int index) override
	{
		return bitmap;
	}
};

class Player:public Object
{
	
public:
	static HBITMAP bitmap[10];

	Player() 
	{
	}
	~Player()
	{
	}
	
	void Stop();
	void MoveL();
	void MoveR();
	void Move(float x,float y);

	HBITMAP GetBitMap(int index) override
	{
		return bitmap[index];
	}
};