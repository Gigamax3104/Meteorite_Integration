#pragma once
#include	"StateBase.h"
#include	"../Itou/ContentCreation2026_10_19/Turret.h"
#include	"../Itou/ContentCreation2026_10_19/Ammo.h"
#include	"../Kihara/earth-master/Earth.h"
#include	"../Iwasaki/meteorite-master/GameScene.h"

class GameState : public StateBase {
public:
	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;

private:
	Turret m_turret; //砲台

	Earth m_earth; //地球

	GameScene m_system; //システム

	Ammo m_ammo;
};