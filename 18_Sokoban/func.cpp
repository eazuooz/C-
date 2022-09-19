#include "func.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define SIZE_MAP_X 30
#define SIZE_MAP_Y 24 
#define test 1
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define DELAY	300 // 0.3�� , 1000�ϸ� 1��
#define STAGE_MAX 10

#define UNDO_MAX 10 //�ִ� �������� ��Ұ���, �� ������ �޸𸮰��� �ʹ����� ������
#define BACK_SPACE 8 //�齺���̽��� �ƽ�Ű�ڵ�� 8 ,Ȯ��Ű���ƴ�,�ΰ����� ���

#define RESTART 114

#define PLAYER_MOVE_MAX 1000

#define PAGE_UP 73
#define PAGE_DOWN 81
#define REPLAY 'h'


typedef struct {
	char map[SIZE_MAP_Y][SIZE_MAP_X];
	int player_x;
	int player_y;
	int player_move_count;
	int player_push_count;
}UNDO;

enum { HIDDEN, SHOW };

enum {
	BLACK, /* 0 : ��� */
	DARK_BLUE, /* 1 : ��ο� �Ķ� */
	DARK_GREEN, /* 2 : ��ο� �ʷ� */
	DARK_SKY_BLUE, /* 3 : ��ο� �ϴ� */
	DARK_RED, /* 4 : ��ο� ���� */
	DARK_VIOLET, /* 5 : ��ο� ���� */
	DARK_YELLOW, /* 6 : ��ο� ��� */
	GRAY, /* 7 : ȸ�� */
	DARK_GRAY, /* 8 : ��ο� ȸ�� */
	BLUE, /* 9 : �Ķ� */
	GREEN, /* 10 : �ʷ� */
	SKY_BLUE, /* 11 : �ϴ� */
	RED, /* 12 : ���� */
	VIOLET, /* 13 : ���� */
	YELLOW, /* 14 : ��� */
	WHITE, /* 15 : �Ͼ� */
};

char* Stage_clear1 = " S T A G E  C L R A R";
char* Stage_clear2 = "press space key to next stage";

char map[SIZE_MAP_Y][SIZE_MAP_X];  //��ǥ��� �迭�� INDEX�� �ݴ��ڸ��� �����Ƿ� 

int stage_x;
int stage_y;

int player_x;
int player_y;

int exit_flag = 0;

int stage;
int stage_clear_flag;

int player_move_count;
int player_push_count;

UNDO Undo[UNDO_MAX];
int undo_count;

char Player_move[PLAYER_MOVE_MAX];

int Stage_clear[STAGE_MAX];

int Push_count[STAGE_MAX];
int Move_count[STAGE_MAX];

int replay_flag; //0�̾��ٰ� <H>�� ���� ���÷��̸��ϸ� 1�� �ٲ����
int replay_count;  //pps0000 4010MKKHPPKMMP �ڿ� ����Ű �ε���(��ġ) ������ �ϳ��� �ްԵ� 


char replay_buffer[PLAYER_MOVE_MAX];

const char *stage_table[] = {
	"040300222n00212n00232222n22200312n21300222n222232n000212n000222n",
	"010122222n20002n203320222n203020212n222022212n022000012n020002002n020002222n022222n",
	"020302222222n0200000222n2232220002n2000300302n2011203022n221120002n022222222n",
	"010202222n22002n20302n223022n220302n213002n211412n222222n",
	"0201022222n0200022n0203002n22202022n21202002n21300202n21000302n22222222n",
	"08010002222222n0022002002n0020002002n0023030302n0020322002n2220302022n211111002n2222222222",
	"0803000222222n022200002n2210322022n2113030002n2110303022n222222002n000002222",
	"08070222222222n0200220002n0200030002n0230222032n0202111202n22021112022n20300300302n20000020002n22222222222n",
	"010300222222n00200002n22233302n20031102n20311122n2222002n0002222n",
	"0804022220022222n220020020002n203022223002n200311110302n220000200022n02222222222n",
};

int GameGetPosition(const char *pnt) {
	int ret;
	char data;

	data = *pnt++;
	ret = data - '0';
	ret *= 10;
	data = *pnt++;
	ret += data - '0';

	return ret;
}

void GamePlayerPositionSet(const char *pnt) {
	player_x = GameGetPosition(pnt);
	player_y = GameGetPosition(pnt + 2);
} 
void GameStageSizeSet(const char*pnt) {
	int max_x = 0; /*���� ū ���� ã��*/
	int x = 0;	/*���������� ���� ũ��*/
	int y = 0;	/*���������� ����ũ��*/
	char data;
	for (;;) {
		data = *pnt++;
		if (data == 0)break; /*�������� �������� ���� üũ*/
		if (data == 'n') {	/*�ٹٲ� ó��*/
			if (x > max_x) max_x = x;
			x = 0; //�ٹٲ�
			y++;
			continue;
		}
		x++;
	}
	stage_x = (SIZE_MAP_X - max_x) / 2;
	stage_y = (SIZE_MAP_Y - y) / 2;
}
void GameStageToMap(const char *pnt) {
	int x = stage_x;
	int y = stage_y;
	char data;

	for (;;) {
		data = *pnt++;
		if (data == 0)break;
		if (data == 'n') {
			x = stage_x;
			y++;
			continue;
		}
		map[y][x] = data;
		x++;
	}
}

/* ȭ���� Ŀ���� ���̰ų� ����� */
/*0�� �Ű������� �ָ� Ŀ���� �������*/
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

/* x, y ��ǥ�� Ŀ���� �����̴� �Լ� */
void gotoxy(int x, int y) /*Ŀ���̵� �Լ� �κ�*/
{
	COORD XY = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

/* �ܼ� ������ �����ϴ� �Լ� */
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PlayerDraw(void) { //Ư�����ڰ� 2�� �����ϱ⶧���� *2�� ��
	gotoxy(player_x * 2, player_y);
	SetColor(VIOLET);
	printf("��");
}

void MapDraw(int x, int y) {
	char data;
	gotoxy(x * 2, y);
	data = map[y][x];
	switch (data) {
	case    '0':    SetColor(BLACK);    printf("  ");   break;  /* ����� */
	case    '3':    SetColor(RED);      printf("��");   break;  /* ������ �ڽ� */
	case    '2':    SetColor(GREEN);    printf("��");   break;  /* ��ó�� */
	case    '1':    SetColor(YELLOW);   printf("��");   break;  /* ������ */
	case    '4':    SetColor(RED);      printf("��");   break;  /* �ϼ��� ������ */
	}
}

void GameDraw(void) {

	int loopx, loopy;

	for (loopy = 0; loopy<SIZE_MAP_Y; loopy++) {
		for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
			MapDraw(loopx, loopy);
		}
	}
}

void PlayerErase(void) {
	MapDraw(player_x, player_y);
}

void PlayerMoveAction(void) {
	int move_flag = 0;
	int dx = 0, dy = 0;
	char key;
	char data;
	char data2;

	if (replay_flag == 0) {	//���÷��̰� �������� �ƴҶ�
		key = Getkey();  //������Է��� ���� ���
		if (key == PAGE_UP) {
			if (++stage >= STAGE_MAX) {
				stage = 0;
			}
			stage_clear_flag = 1;
			return;
		}
		else if (key == PAGE_DOWN) {
			if (--stage < 0) {
				stage = STAGE_MAX - 1;
			}
			stage_clear_flag = 1;
			return;
		}

	}
	
	else {					  //���÷��̰� �������ϰ��
		key = GetkeyRePlay(); //���Ϸ� ���� �о ���÷��̸� �ϴ°�
	}
	
	switch (key) {
	case UP:dx = 0; dy = -1; break;
	case DOWN: dx = 0; dy = +1; break;
	case LEFT: dx = -1; dy = 0; break;
	case RIGHT:dx = 1; dy = 0; break;
	}
	if (dx == 0 && dy == 0)return; //����Ű,ESCŰ ���� �ٸ�Űó��, �׷��� ó���� dx,dy��0���� �ʱ�ȭ �Ѱ�

	data = map[player_y + dy][player_x + dx];
	data2 = map[player_y + dy + dy][player_x + dx + dx];

	if (data == '3') {
		if (data2 == '0') {
			UndoSave();
			map[player_y + dy][player_x + dx] = '0';
			map[player_y + dy + dy][player_x + dx + dx] = '3';
			MapDraw(player_x + dx + dx, player_y + dy + dy);
			move_flag = 1;
			player_push_count++;
			PlayerPushCountDraw();
		}
		else if (data2 == '1') {
			UndoSave();
			map[player_y + dy][player_x + dx] = '0';
			map[player_y + dy + dy][player_x + dx + dx] = '4';
			MapDraw(player_x + dx + dx, player_y + dy + dy);
			move_flag = 1;
			player_push_count++;
			PlayerPushCountDraw();
		}

	}
	else if (data == '4') {
		if (data2 == '0') {
			UndoSave();
			map[player_y + dy][player_x + dx] = '1';
			map[player_y + dy + dy][player_x + dx + dx] = '3';
			MapDraw(player_x + dx + dx, player_y + dy + dy);
			move_flag = 1;
			player_push_count++;
			PlayerPushCountDraw();
		}
		else if (data2 == '1') {
			UndoSave();
			map[player_y + dy][player_x + dx] = '1';
			map[player_y + dy + dy][player_x + dx + dx] = '4';
			MapDraw(player_x + dx + dx, player_y + dy + dy);
			move_flag = 1;
			player_push_count++;
			PlayerPushCountDraw();
		}
	}

		else {
			if (data != '2') {
				UndoSave();
				move_flag = 1;
			}
		}

		if (move_flag != 0){ // �÷��̾ �����δٴ� ��Ȳ
			Player_move[player_move_count] = key;
			PlayerErase();
			player_x += dx;
			player_y += dy;
			player_move_count++;
			PlayerMoveCountDraw();
			PlayerDraw();
			if (StageClearCheck() != 0) { //�������� ����
				StageClearFileSave();
				SetColor(YELLOW);
				gotoxy((SIZE_MAP_X * 2 - strlen(Stage_clear1)) / 2, 3);
				printf("%s", Stage_clear1);
				gotoxy((SIZE_MAP_X * 2 - strlen(Stage_clear2)) / 2, 5);
				printf("%s", Stage_clear2);
				for (;;) {
					key = getch();
					if (key == ' ')break;
				}
				stage += 1;
				if (stage >= STAGE_MAX)
					stage = 0;
				stage_clear_flag = 1;
			}
			
		}
}

void GameStageInit(void) {
	StageClearFileLoad();
	int loopx, loopy;
	for (loopy = 0; loopy < SIZE_MAP_Y; loopy++) {
		for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
			map[loopy][loopx] = '0';
		}
	}
	const char *pnt = stage_table[stage];

	CursorView(HIDDEN);
	SetConsoleTitle("PushPush made by onyou");
	GamePlayerPositionSet(pnt); // 1. ���� �÷��̾��� x, y ��ǥ�� stage�� ���ؼ� ��´�.
	pnt += 4; //���� ���ڸ��� �÷��̾��̹Ƿ� �ѱ�
	GameStageSizeSet(pnt); // 2. ���� ���������� ���ؼ� ����� �� �����Ѵ�.

	player_x += stage_x;
	player_y += stage_y;

	GameStageToMap(pnt); // 3. ������ ȭ��� map 2���� �迭�� 1:1�� ��Ī ��Ų��.
	GameDraw(); // 4. map 2���� �迭�� ���ؼ� ���� ȭ�鿡 �׷��ش�
	PlayerDraw(); // 5. �÷��̾� ������ ȭ�鿡 �׷��ش�.
	stage_clear_flag = 0;
	player_move_count = 0;
	player_push_count = 0;

	undo_count = 0;
}


int StageClearCheck(void) {
	char data;
	int loopx, loopy;
	for(loopy=0;loopy<SIZE_MAP_Y;loopy++)
		for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
			data = map[loopy][loopx];
			if (data == '3') return 0; 
		}
	return 1;
}

void TitleDraw(void) {
	int x = SIZE_MAP_X * 2;
	int y = 0;
	SetColor(DARK_YELLOW);
	gotoxy(x, y + 2);   printf("��������������������");
	gotoxy(x, y + 3);   printf("��P U S H  P U S H��");
	gotoxy(x, y + 4);   printf("�� made by ONYOU  ��");
	gotoxy(x, y + 5);   printf("��������������������");
	SetColor(YELLOW);
	gotoxy(x + 2, y + 1);   printf("P U S H  P U S H");
}

void StageDraw(void) {
	int x = SIZE_MAP_X * 2;
	int y = 6;
	SetColor(RED);
	gotoxy(x + 2, y);	printf("Stage : %d", stage + 1);
}

void PlayerMoveCountDraw(void) {
	int x = SIZE_MAP_X * 2;
	int y = 8;
	SetColor(VIOLET);
	gotoxy(x + 2, y);   printf("Move: %d", player_move_count);
	if (Stage_clear[stage] != 0) {
		SetColor(RED);
		printf("/%d", Move_count[stage]);
	}
}

void PlayerPushCountDraw(void){
	int x = SIZE_MAP_X * 2;
	int y = 9;
	SetColor(VIOLET);
	gotoxy(x + 2, y);   printf("Push: %d", player_push_count);
	if (Stage_clear[stage] != 0) {
		SetColor(RED);
		printf("/%d", Push_count[stage]);
	}
}

void GameHelpDraw(void)
{
	int x = SIZE_MAP_X * 2;
	int y = 11;
	SetColor(DARK_GREEN);
	gotoxy(x + 2, y++); printf("[ Backspace ] : undo\n");
	gotoxy(x + 2, y++); printf("[ Reset ] : R \n");
	gotoxy(x + 2, y++); printf("[ Esc ] : Exit \n");
	SetColor(BLUE);
	y++;
	gotoxy(x + 2, y++); printf("[ H ] : Replay\n");
	SetColor(GRAY);
	y++;
	y++;
	gotoxy(x + 2, y++); printf("       UP");
	gotoxy(x + 2, y++); printf("       ��");
	gotoxy(x + 2, y++); printf("LEFT ��  �� RIGHT");
	gotoxy(x + 2, y++); printf("       ��");
	gotoxy(x + 2, y++); printf("      DOWN");
	y++;
	y++;
	SetColor(DARK_BLUE);
	gotoxy(x + 2, y++); printf("[ PAGE_UP ] : Next stage");
	gotoxy(x + 2, y++); printf("[ PAGE_DOWN ] : Previous");
}

void GameStateDraw(void) {
	TitleDraw();
	StageDraw();
	PlayerMoveCountDraw();
	PlayerPushCountDraw();
	GameHelpDraw();
}

void UndoSave(void) {
	int loop, loopx, loopy;
	//-
	if (undo_count >= UNDO_MAX) { //���� ������Ұ� ��á����
		//----
		for (loop = 1; loop < UNDO_MAX; loop++) {  //�ϳ��� ������ �о��ش�
			for (loopy = 0; loopy < SIZE_MAP_Y; loopy++) {
				for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
					Undo[loop - 1].map[loopy][loopx] = Undo[loop].map[loopy][loopx];
				}
			}
			Undo[loop - 1].player_x = Undo[loop].player_x;
			Undo[loop - 1].player_y = Undo[loop].player_y;
			Undo[loop - 1].player_move_count = Undo[loop].player_move_count;
			Undo[loop - 1].player_push_count = Undo[loop].player_push_count;
		}
		//---
		undo_count--;
	}
	//-
	for (loopy = 0; loopy < SIZE_MAP_Y; loopy++) {  //���� ��Ұ� �˾�á����
		for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
			Undo[undo_count].map[loopy][loopx] = map[loopy][loopx];
		}
	}
	Undo[undo_count].player_x = player_x;
	Undo[undo_count].player_y = player_y;
	Undo[undo_count].player_move_count = player_move_count;
	Undo[undo_count].player_push_count = player_push_count;
	undo_count++;
}

void GameUndo(void) {
	int loopx, loopy;
	undo_count--;
	for (loopy = 0; loopy < SIZE_MAP_Y; loopy++) {
		for (loopx = 0; loopx < SIZE_MAP_X; loopx++) {
			map[loopy][loopx] = Undo[undo_count].map[loopy][loopx];
			MapDraw(loopx, loopy);
		}
	}
	player_x = Undo[undo_count].player_x;
	player_y = Undo[undo_count].player_y;
	PlayerDraw();
	player_move_count = Undo[undo_count].player_move_count;
	PlayerMoveCountDraw();
	player_push_count = Undo[undo_count].player_push_count;
	PlayerPushCountDraw();
}

void StageClearFileSave(void) {
	char filename[10];
	FILE*fp;
	int temp;
	char c;
	int loop;
	sprintf(filename, "stage%02d.pps", stage);
	fp = fopen(filename, "wt");
	
	if (fp == 0) { //������ ����� ������ ������� ����ְ� ���ư���.
		printf("\a");
		return;
	}
	/*00*/	fputc('p', fp);
	/*01*/	fputc('p', fp);
	/*02*/	fputc('s', fp);
		
	/*03*/	temp = stage;
			c = temp / 10;
			fputc(c + '0', fp); 

	/*04*/	temp -= c * 10;
			fputc(temp + '0', fp); 

	/* 05. push count �� 100�� �ڸ� */
			temp = player_push_count;
			c = temp / 100;
			fputc(c + '0', fp); 

	/*06. push count �� 10�� �ڸ� */
			temp -= c * 100; c = temp / 10;
			fputc(c + '0', fp); 
			
	/*07*/	temp -= c * 10;
			fputc(temp + '0', fp);
		
	/*08*/	temp = player_move_count;
			c = temp / 100;
			fputc(c + '0', fp); 
			
	/*09*/	temp -= c * 100;
			c = temp / 10;
			fputc(c + '0', fp); 
			
	/*10*/	temp -= c * 10;
			fputc(temp + '0', fp);
	/*11*/
	for (loop = 0; loop < player_move_count; loop++) {
		fputc(Player_move[loop], fp);
		}
	fclose(fp);
}

int StageClearFileLoad(void) {
	char buffer[12];
	int ret;
	char filename[10];
	FILE*fp;
	int loop;
	for (loop = 0; loop < STAGE_MAX; loop++) {
		sprintf(filename, "stage%02d.pps", loop);
		fp = fopen(filename, "rt");
		if (fp == 0) {
			Stage_clear[loop] = 0;
		}
		else {
			Stage_clear[loop] = 1;
			fgets(buffer, 12, fp);
			Push_count[loop] = (buffer[5] - '0') * 100 + (buffer[6] - '0') * 10 + (buffer[7] - '0');
			Move_count[loop] = (buffer[8] - '0') * 100 + (buffer[9] - '0') * 10 + (buffer[10] - '0');
			fclose(fp);
		}
	}
	for (loop = 0; loop < STAGE_MAX; loop++) {
		sprintf(filename, "stage%02d.pps", loop);
		fp = fopen(filename, "rt");
		if (fp == 0) {  //���� ������ ������ �� ������������ �����Ѵ�
			ret = loop;
			break;
		}
		else {
			fclose(fp);
		}
	}
	return (ret);
}

void StageReplayLoad(void) {
	char buffer[12]; 
	char filename[10];
	FILE*fp;
	sprintf(filename, "stage%02d.pps", stage);
	fp = fopen(filename, "rt");
	fgets(buffer, 12, fp); // Ű�ޱ��� ���� ������ �о� Ŀ���� �ű�
	fgets(replay_buffer, Move_count[stage] + 1, fp);//���ڿ������ִ� �α��� ���� ����
	fclose(fp);
}

char Getkey(void){
	char key;
	key = getch();

	if (key == ESC) {	//ESC�� ������ ������ ��������
		exit_flag = 1;
	}
	else if (key == BACK_SPACE) {
		if (undo_count > 0) {
			GameUndo();
		}
	}
	else if (key == RESTART) {
		stage_clear_flag = 1;
	}
	else if (key == REPLAY) {  //'h'Ű�� �޾�����
		if (replay_flag == 0  && Stage_clear[stage]==1) {	//���÷������� �ƴϰ� ���������� Ŭ���� �������
			replay_flag = 1;   //���÷��̸� ���� 
			replay_count = 0;
			StageReplayLoad();
		}
	}

	else if (key == -32) key = getch(); //Ȯ��Ű����� �ѹ��� �о�����Ѵ�.'Ȯ��Ű����'�� -32�� ǥ��
	else {
		// ...
	}

	return key;
}

char GetkeyRePlay(void) {
	char key = 0;

	key = replay_buffer[replay_count];
	if (++replay_count >= Move_count[stage]) 
		replay_flag = 0;

	Sleep(DELAY);

	return key;
}

