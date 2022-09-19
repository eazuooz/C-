#ifndef __H__FUNC
#define __H__FUNC

/////////////////////////�Լ� ����

int GameGetPosition(const char *pnt); //�����Ͱ� ����Ű�� ���� �����͸� �ΰ� �о �װ��� ���ڷ� ��ȯ�ؼ� ��ȯ�Ѵ�.

void GamePlayerPositionSet(const char *pnt); //�� ��ġ�� ��ǥ�� �����ִ� �Լ�
void GameStageSizeSet(const char*pnt); //���������� �׷��� �������� ��������� ����
void GameStageToMap(const char *pnt); //1���� �迭�� 2�����迭�� �ٲٴ� �۾� ,2������ �ε����� �� ��ǥ�� �ȴ�.
void CursorView(char show); // ȭ���� Ŀ���� ���̰ų� ����� ,0�� �Ű������� �ָ� Ŀ���� �������


void gotoxy(int x, int y); // x, y ��ǥ�� Ŀ���� �����̴� �Լ� 

void SetColor(int color); //�ܼ� ������ �����ϴ� �Լ� 

void PlayerDraw(void); //�÷��̾ �׷��ִ� �Լ� 

void MapDraw(int x, int y); //x,y�� �������ָ� 2�����迭�� map�迭�� �� �ε����� �׷��ִ� �Լ�  
void GameDraw(void); //�� ��ü�� ����ϴ� �Լ� 

void PlayerErase(void); // �÷��̾ ����� �Լ���.

void PlayerMoveAction(void); //�÷��̾��� �������� �����ϰ� �÷��̾ �̵������ִ� �Լ�  
void GameStageInit(void); //���α׷����� �ʱ⿡ ȣ��Ǿ���ϴ� �Լ����� ����
int StageClearCheck(void); //�������� Ŭ����� 1��ȯ ���н� 0��ȯ
void GameStateDraw(void); // ������ ������ �����ʿ� ����� �ش�.
void PlayerMoveCountDraw(void); //�÷��̾��� ������ Ƚ���� ����Ѵ�.
void PlayerPushCountDraw(void); //�÷��̾��� Ǫ�� Ƚ���� ����Ѵ�.

void UndoSave(void); // ������Ұ� ��á���� ��ĭ�������� �о��ְ� ��� �����
void GameUndo(void); //���� �����͸� �׷��ش� 

void StageClearFileSave(void); //�������� Ŭ��� �� ������ ��� ������ ���Ϸ� ����

int StageClearFileLoad(void); //���������� ������� �������� ������ �о�鿩�� �˾Ƴ��� �� ���������� ��ȣ�� �ҷ��ش�.

void StageReplayLoad(void);	//char replay_buffer[PLAYER_MOVE_MAX]; �̹��ۿ� ���÷��� ������ ��� ����

char Getkey(void); //Ű�� �Է¹޾Ƽ� ��Ű�� ��ȯ�Ѵ�.
char GetkeyRePlay(void); //���÷����ϱ�

#endif