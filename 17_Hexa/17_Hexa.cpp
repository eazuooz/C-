#include "TitleScene.h"
#include "GameScene.h"
#include "StageScene.h"


int main()
{

	TitleScene title;
	title.PrintScene();

	StageScene stage;
	stage.PrintScene();

	GameScene game;
	game.InitStage();
	game.InitData();

	while (true)
	{
		game.Update();
	}

	

	return 0;
}
