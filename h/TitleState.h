#pragma once
#include	"StateBase.h"

class TitleState : public StateBase {
public:
	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;
};