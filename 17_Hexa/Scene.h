#pragma once
#include "Common.h"




class Scene
{
public:
	virtual void PrintScene() = 0;

public:
	int gotoxy(int x, int y);
	void SetColor(int color);
};

