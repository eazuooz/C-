#include "StageScene.h"

void StageScene::PrintScene()
{
	gotoxy(77, 23);		//ȭ�� �ܻ��� ���ֱ� ����
	printf("  \b\b");

	int i = 0;
	SetColor(GRAY);
	gotoxy(10, 7);
	printf("����������<GAME KEY>������������");
	Sleep(10);
	gotoxy(10, 8);
	printf("�� UP   : Rotate Block        ��");
	Sleep(10);
	gotoxy(10, 9);
	printf("�� DOWN : Move One-Step Down  ��");
	Sleep(10);
	gotoxy(10, 10);
	printf("�� SPACE: Move Bottom Down    ��");
	Sleep(10);
	gotoxy(10, 11);
	printf("�� LEFT : Move Left           ��");
	Sleep(10);
	gotoxy(10, 12);
	printf("�� RIGHT: Move Right          ��");
	Sleep(10);
	gotoxy(10, 13);
	printf("��������������������������������");

	while (i < 1 || i>8)
	{
		gotoxy(10, 3);
		printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
		scanf_s("%d", &i);
	}

	SetLevel(i - 1);
	system("cls");
	
	return;
}
