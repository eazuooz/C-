#pragma once
#include "Common.h"




class Scene
{
public:
	static void SetLevel(int level) { mLevel = level; }
	static int GetLevel() { return mLevel; }

public:
	virtual void PrintScene() = 0;

protected:
	int gotoxy(int x, int y);
	void SetColor(int color);

private:
	static int mLevel;
};

