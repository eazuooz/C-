#pragma once
#include "Scene.h"
#include "Stage.h"

#define MAP_Y 21
#define MAP_X 10

class GameScene : public Scene
{
public:
	void InitStage();
	void InitData();
	void PrintScene() override;
	void Update();

private:
	Stage mStage[8];


public:
	int cur_block[3];
	int next_block[3];
	int cur_x, cur_y;
	int blocks;
	int max_combo;
	double score;
	int total_block[MAP_Y][MAP_X];	//����:����:��� 

	int make_new_block(int* shape);


	int PrintMap();
	int PrintNextBlock(int* shape);
	int show_cur_block(int* shape, int x, int y);
	int PrintGameScore();
	int show_gameover();
	int find_fair(int combo);		//¦�� �´°��� ã��
	int move_down(int* x, int* y);
	int ani_del_block(int block_arr[21][10]);		//���� ���� ã������ �ִϸ��̼�
	int del_block(int block_arr[21][10], int combo);		//���� ���� ã������ �ִϸ��̼�
};

