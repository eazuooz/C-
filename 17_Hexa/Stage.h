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
	int	mSpeed;				//숫자가 낮을수록 속도가 빠르다
	int mTripleRate;		//3개가 같은 모양이 나오는 확률 0~99  , 99는 100%로 나옴, 일반적인 확률은 3임
	int mClearBlock;
};

