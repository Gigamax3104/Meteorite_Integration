#pragma once
#include	"Player.h"

class StateBase {
public:
	virtual void Enter() = 0;
	virtual StateBase* Loop() = 0;
	virtual void Exit() = 0;

protected:
	Player m_player;
};