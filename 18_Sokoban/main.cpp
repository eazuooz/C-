/*
 -���� �׸��� ���ڵ����ͷ� ��ġ�Ѵ�

0: �� ĭ
1: ������
2: ��
3: ������ �ڽ�
4: ä���� ������

-�÷��̾� ��ġ������ �������� ������ �Ǿ� ���ڸ� 

*/
#include "func.h"

#include <Windows.h>

extern int exit_flag;
extern int stage_clear_flag;
extern int stage;

int main() 
{

	stage_clear_flag = 1;
	stage = StageClearFileLoad();

	for (;;) {
		if (stage_clear_flag != 0) {
			system("cls"); //ȭ���������
			GameStageInit();
			GameStateDraw();
		}

		PlayerMoveAction();

		if (exit_flag != 0)break;
	}
	return 0;
}