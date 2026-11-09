#pragma once
#include	"StateBase.h"

class GameState : public StateBase {
public:
	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;
};