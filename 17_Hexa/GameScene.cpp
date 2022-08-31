#include "GameScene.h"

void GameScene::InitStage()
{
	mStage[0].SetSpeed(40);
	mStage[0].SetClearBlock(60);
	mStage[0].SetTripleRate(8);

	mStage[1].SetSpeed(37);
	mStage[1].SetClearBlock(70);
	mStage[1].SetTripleRate(7);

	mStage[2].SetSpeed(33);
	mStage[2].SetClearBlock(75);
	mStage[2].SetTripleRate(6);

	mStage[3].SetSpeed(30);
	mStage[3].SetClearBlock(80);
	mStage[3].SetTripleRate(4);

	mStage[4].SetSpeed(27);
	mStage[4].SetClearBlock(90);
	mStage[4].SetTripleRate(1);

	mStage[5].SetSpeed(22);
	mStage[5].SetClearBlock(100);
	mStage[5].SetTripleRate(1);

	mStage[6].SetSpeed(18);
	mStage[6].SetClearBlock(110);
	mStage[6].SetTripleRate(1);

	mStage[7].SetSpeed(10);
	mStage[7].SetClearBlock(999);
	mStage[7].SetTripleRate(1);
}

void GameScene::InitData()
{
	int i, j;
	cur_x = 4;
	cur_y = -2;
	blocks = 0;
	for (i = 0; i < 21; i++)
		for (j = 0; j < 10; j++)
			total_block[i][j] = 0;
	for (i = 0; i < 21; i++)
	{
		total_block[i][0] = 9;
		total_block[i][9] = 9;
	}
	for (i = 0; i < 10; i++)
	{
		total_block[20][i] = 9;
	}

	max_combo = 0;
	score = 0;
	//랜덤 seed값 넣기
	srand((unsigned)time(NULL));
		
	make_new_block(cur_block);
	make_new_block(next_block);
	PrintMap();
	PrintNextBlock(next_block);
	PrintGameScore();;
}

void GameScene::PrintScene()
{


}

void GameScene::Update()
{
	gotoxy(77, 23);		//화면 잔상을 없애기 위함
	printf(" \b");

	int frame = 0;
	char keytemp;
	int is_gameover = 0;
	int shape_tmp;
	int blank_block[3] = { 0,0,0 };
	int return_tmp;

	while (true)
	{
		if (_kbhit())
		{
			keytemp = _getch();
			if (keytemp == EXT_KEY)
			{
				keytemp = _getch();
				show_cur_block(blank_block, cur_x, cur_y);	//이동하기전 위치의 블럭 모양을지운다
				switch (keytemp)
				{
				case KEY_UP:		//회전하기
					shape_tmp = cur_block[2];
					cur_block[2] = cur_block[1];
					cur_block[1] = cur_block[0];
					cur_block[0] = shape_tmp;

					break;
				case KEY_LEFT:		//왼쪽으로 이동
					if (cur_x > 1)
					{
						if (total_block[cur_y + 2][cur_x - 1] == 0)
							cur_x--;
					}
					break;
				case KEY_RIGHT:		//오른쪽으로 이동
					if (cur_x < 8)
					{
						if (total_block[cur_y + 2][cur_x + 1] == 0)
							cur_x++;
					}
					break;
				case KEY_DOWN:		//아래로 이동
					return_tmp = move_down(&cur_x, &cur_y);
					if (return_tmp == 1)		//블럭이 바닥에 닿았을때
					{
						if ((cur_y < 0) && (total_block[cur_y + 3][cur_x] != 0))
						{
							is_gameover = 1;
						}
						else 
						{
							find_fair(0);
							PrintMap();
							PrintGameScore();
						}
					}
					break;
				}
			}
			if (keytemp == KEY_SPACE)	//스페이스바를 눌렀을때
			{
				return_tmp = 0;
				while (return_tmp == 0)
					return_tmp = move_down(&cur_x, &cur_y);

				if ((cur_y < 0) && (total_block[cur_y + 3][cur_x] != 0))
				{
					is_gameover = 1;
				}
				else 
				{
					find_fair(0);
					PrintMap();
					PrintGameScore();
				}
			}
			show_cur_block(cur_block, cur_x, cur_y);
		}

		if (frame % mStage[GetLevel()].GetSpeed() == 0)
		{
			if (blocks > mStage[GetLevel()].GetClearBlock())
				if (GetLevel() < 7)
				{
					int curLevel = GetLevel();
					SetLevel(curLevel + 1);
					
					blocks = 0;
				}
			show_cur_block(blank_block, cur_x, cur_y);	//이동하기전 위치의 블럭 모양을지운다
			return_tmp = move_down(&cur_x, &cur_y);		//블럭을 이동한다.

			if (return_tmp == 1)		//블럭이 바닥에 닿았을때	
			{
				if ((cur_y < 0) && (total_block[cur_y + 3][cur_x] != 0))
				{
					is_gameover = 1;
				}
				else {

					find_fair(0);
					PrintMap();
					PrintGameScore();
				}
			}
			show_cur_block(cur_block, cur_x, cur_y);
		}
		if (is_gameover == 1)
		{
			show_gameover();
			SetColor(GRAY);
			break;
		}
		Sleep(13);
		frame++;
	}
}

int GameScene::make_new_block(int* shape)
{
	int i;
	int rtn_tmp;
	rtn_tmp = rand() % 100;
	if (mStage[GetLevel()].GetTripleRate() > rtn_tmp)	//트리플 확률로 트리플이 나올때
	{
		rtn_tmp = rand() % 5 + 1;
		shape[0] = rtn_tmp;
		shape[1] = rtn_tmp;
		shape[2] = rtn_tmp;
		return 0;
	}
	for (i = 0; i < 3; i++)
	{
		shape[i] = rand() % 5 + 1;
	}
}

int GameScene::PrintMap()
{
	int y, x;
	for (y = 0; y < 21; y++)
	{
		for (x = 0; x < 10; x++)
		{
			gotoxy(x * 2 + ABS_X, y + ABS_Y);
			switch (total_block[y][x])
			{
			case 0:
				SetColor(GRAY | GRAY * 16);
				printf("  ");
				break;
			case 1:
				SetColor(BLUE | DARK_GRAY * 16);
				printf("●");
				break;
			case 2:
				SetColor(SKY_BLUE | DARK_GRAY * 16);
				printf("◆");
				break;
			case 3:
				SetColor(BLACK | DARK_GRAY * 16);
				printf("■");
				break;
			case 4:
				SetColor(GREEN | DARK_GRAY * 16);
				printf("♥");
				break;
			case 5:
				SetColor(RED | DARK_GRAY * 16);
				printf("★");
				break;
			case 9:
				SetColor(((GetLevel() % 6) + 1) * 16);
				printf("  ");
				break;
			}
		}
	}

	return 0;
}

int GameScene::PrintNextBlock(int* shape)
{
	int i, j;
	//SetColor(((GetLevel()+1)%6+1)|GRAY*16);
	for (i = 2; i < 7; i++)
	{
		gotoxy(28, i);
		for (j = 0; j < 5; j++)
		{
			if (i == 2 || i == 6 || j == 0 || j == 4)
			{
				SetColor(((GetLevel() + 1) % 6 + 1));
				printf("■");
			}
			else {
				SetColor(GRAY * 16);
				printf("  ");
			}

		}
	}
	show_cur_block(shape, 13, 1);
	return 0;
}

int GameScene::show_cur_block(int* shape, int x, int y)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (y + i < 0)		//화면 위쪽의 블럭은 보여주지 않음
			continue;

		gotoxy((x * 2) + ABS_X, y + i + ABS_Y);
		printf("  \b\b");
		switch (shape[i])
		{
		case 0:
			SetColor(GRAY * 16);
			printf("  ");
			break;
		case 1:
			SetColor(BLUE | WHITE * 16);
			printf("●");
			break;
		case 2:
			SetColor(SKY_BLUE | WHITE * 16);
			printf("◆");
			break;
		case 3:
			SetColor(BLACK | WHITE * 16);
			printf("■");
			break;
		case 4:
			SetColor(GREEN | WHITE * 16);
			printf("♥");
			break;
		case 5:
			SetColor(RED | WHITE * 16);
			printf("★");
			break;
		}
	}
	return 0;
}

int GameScene::PrintGameScore()
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(29, 7);
		printf("STAGE");

		gotoxy(29, 9);
		printf("SCORE");

		gotoxy(29, 12);
		printf("BLOCKS");

		gotoxy(29, 15);
		printf("MAX COMBO");

	}
	gotoxy(35, 7);
	printf("%d", GetLevel() + 1);
	gotoxy(29, 10);
	printf("%10d", (int)score);
	gotoxy(29, 13);
	printf("%10d", mStage[GetLevel()].GetClearBlock() - blocks);
	gotoxy(29, 16);
	printf("%10d", max_combo);
	return 0;
}

int GameScene::show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	printf("┏━━━━━━━━━━━━━┓");
	gotoxy(15, 9);
	printf("┃**************************┃");
	gotoxy(15, 10);
	printf("┃*        GAME OVER       *┃");
	gotoxy(15, 11);
	printf("┃**************************┃");
	gotoxy(15, 12);
	printf("┗━━━━━━━━━━━━━┛");
	fflush(stdin);
	Sleep(1000);

	_getche();
	system("cls");

	return 0;
}

int GameScene::find_fair(int combo)
{
	int fair_num = 0;
	int i = 0, j = 1, k = 0, l = 1;
	int tmp_shape;
	int tmp_x, tmp_y;
	int fair_arr[21][10];
	int is_del_block = 0;

	for (i = 0; i < 21; i++)		//fair_arr 초기화
		for (j = 0; j < 10; j++)
			fair_arr[i][j] = 0;

	for (i = 0; i < 20; i++)			//세로
	{
		for (j = 1; j < 9; j++)		//가로
		{
			tmp_shape = total_block[i][j];

			if (tmp_shape == 0)	//빈칸일경우 기준점을 다음칸으로 옮김
				continue;

			for (k = 0; k < 4; k++)	//방향
			{
				tmp_y = i;
				tmp_x = j;
				fair_num = 0;
				for (l = 1; l < 5; l++)	//깊이
				{
					switch (k)
					{
					case 0:		//기준점에서 왼쪽 아래 대각선 방향을
						tmp_y++;
						tmp_x--;
						break;
					case 1:		//기준점에서 아래 방향
						tmp_y++;
						break;
					case 2:		//기준점에서 오른쪽 아래 대각선 방향
						tmp_y++;
						tmp_x++;
						break;
					case 3:		//기준점에서 오른쪽 방향
						tmp_x++;
						break;
					}
					if (tmp_x < 1 || tmp_x >12 || tmp_y > 20)
						break;
					if (total_block[tmp_y][tmp_x] == tmp_shape)
						fair_num++;
					else
						break;
				}
				if (fair_num >= 2)
				{
					is_del_block = 1;
					tmp_y = i;
					tmp_x = j;
					for (l = 0; l <= fair_num; l++)
					{
						fair_arr[tmp_y][tmp_x] = 1;
						switch (k)
						{
						case 0:		//기준점에서 왼쪽 아래 대각선 방향을
							tmp_y++;
							tmp_x--;
							break;
						case 1:		//기준점에서 아래 방향
							tmp_y++;
							break;
						case 2:		//기준점에서 오른쪽 아래 대각선 방향
							tmp_y++;
							tmp_x++;
							break;
						case 3:		//기준점에서 오른쪽 방향
							tmp_x++;
							break;
						}
					}
				}

			}
		}
	}
	if (is_del_block == 1)	//3개이상이 연달아 있을때
	{
		combo++;
		ani_del_block(fair_arr);
		del_block(fair_arr, combo);
		PrintMap();

		if (combo > max_combo)
			max_combo = combo;

		find_fair(combo);
		return 1;
	}
	return 0;
}

int GameScene::move_down(int* x, int* y)
{
	int j;
	if (total_block[*y + 3][*x] != 0)		//블럭이 바닥에 닿았을때
	{
		for (j = 0; j < 3; j++)
			total_block[*y + j][*x] = cur_block[j];
		cur_block[0] = next_block[0];
		cur_block[1] = next_block[1];
		cur_block[2] = next_block[2];
		make_new_block(next_block);
		PrintMap();
		PrintNextBlock(next_block);
		*x = 4;
		*y = -2;
		return 1;
	}
	else {
		(*y)++;
		return 0;
	}

}

int GameScene::ani_del_block(int block_arr[21][10])
{
	int i, j, k;

	for (k = 0; k < 6; k++)
	{
		for (i = 0; i < 21; i++)
		{
			for (j = 1; j < 9; j++)
			{
				if (block_arr[i][j] == 0)
					continue;

				gotoxy(j * 2 + ABS_X, i + ABS_Y);
				switch (total_block[i][j])
				{
				case 1:
					SetColor(BLUE | (DARK_GRAY + (k % 2)) * 16);
					printf("●");
					break;
				case 2:
					SetColor(SKY_BLUE | (DARK_GRAY + (k % 2)) * 16);
					printf("◆");
					break;
				case 3:
					SetColor(BLACK | (DARK_GRAY + (k % 2)) * 16);
					printf("■");
					break;
				case 4:
					SetColor(GREEN | (DARK_GRAY + (k % 2)) * 16);
					printf("♥");
					break;
				case 5:
					SetColor(RED | (DARK_GRAY + (k % 2)) * 16);
					printf("★");
					break;
				}


				Sleep(24);
			}

		}

	}
	return 0;
}

int GameScene::del_block(int block_arr[21][10], int combo)
{
	int i, j, k;
	int block_num = 0;		//없애는 블럭의 개수
	for (i = 19; i >= 0; i--)
	{
		for (j = 1; j < 9; j++)
		{

			if (block_arr[i][j] == 1)
			{
				total_block[i][j] = 0;
				block_num++;
				blocks++;

			}

		}
	}
	for (i = 0; i < 20; i++)
	{
		for (j = 1; j < 9; j++)
		{
			if (total_block[i][j] != 0)
				continue;

			for (k = i; k >= 0; k--)	//블럭을비운 빈공간을 위에 있는 블럭으로 채운다.
			{
				if (k == 0)
				{
					total_block[k][j] = 0;

				}
				else {
					total_block[k][j] = total_block[k - 1][j];

				}
			}

		}
	}

	//점수 계산
	score += combo * 1.3 * (block_num * 12);
	return 0;
}