#include "TitleScene.h"


void TitleScene::PrintScene()
{
	gotoxy(13, 3);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	Sleep(100);
	gotoxy(13, 4);
	printf("早≠      ≠  ≠≠≠≠≠  ≠      ≠     ≠≠   早");
	Sleep(100);
	gotoxy(13, 5);
	printf("早≠      ≠  ≠            ≠  ≠     ≠    ≠ 早");
	Sleep(100);
	gotoxy(13, 6);
	printf("早≠≠≠≠≠  ≠≠≠≠≠      ≠      ≠≠≠≠≠早");
	Sleep(100);
	gotoxy(13, 7);
	printf("早≠      ≠  ≠            ≠  ≠    ≠      ≠早");
	Sleep(100);
	gotoxy(13, 8);
	printf("早≠      ≠  ≠≠≠≠≠  ≠      ≠  ≠      ≠早");
	Sleep(100);
	gotoxy(13, 9);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(13, 10);
	printf(" Ver 0.1                         ^__^ ");


	gotoxy(28, 20);
	printf("Please Press Any Key~!");

	int to_add = 0;
	int cur_color = 0;
	while (true)
	{
		gotoxy(20, 19);
		for (to_add = 0; to_add < 37; to_add++)
		{
			SetColor((cur_color + to_add) % 16 * 16);
			printf(" ");
		}
		if (cur_color > 0)
			cur_color--;
		else
			cur_color = 15;
		Sleep(100);

		if (_kbhit())
			break;
	}

	//_getche();
	SetColor(GRAY);
	system("cls");
}
