#pragma once
class Stage
{
public:
	int GetSpeed() { return mSpeed; }
	int GetTripleRate() { return mTripleRate; }
	int GetClearBlock() { return mClearBlock; }
	
	void SetSpeed(int speed) { mSpeed = speed; }
	void SetTripleRate(int rate) { mTripleRate = rate; }
	void SetClearBlock(int clearBlock) { mClearBlock = clearBlock; }

private:
	int	mSpeed;				//���ڰ� �������� �ӵ��� ������
	int mTripleRate;		//3���� ���� ����� ������ Ȯ�� 0~99  , 99�� 100%�� ����, �Ϲ����� Ȯ���� 3��
	int mClearBlock;
};

