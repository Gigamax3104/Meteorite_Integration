#pragma once
#include	"StateBase.h"
#include	"GraphicData.h"

class ResultState : public StateBase {
public:
	ResultState() {}
	ResultState(bool flag) : m_resultFlag(flag){}

	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;

	void Draw(int index, Vector2 pos, Vector2 scale);
private:
	bool m_resultFlag = true;

	Image m_images[2];
};