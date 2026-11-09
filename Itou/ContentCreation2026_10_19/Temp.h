#pragma once
#include "Dxlib.h"

//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//以下、暫定的な関数
const int METEOR_DATA_SIZE = 1000;

class Meteor {
private:
	double meteor_position_x[METEOR_DATA_SIZE];
	double meteor_position_y[METEOR_DATA_SIZE];
	bool meteor_flag[METEOR_DATA_SIZE];
	double meteor_radius;
	bool do_meteor_summon;
public:
	Meteor();
	void InputMeteorSummon();
	void UpdateMeteorSummon();
	void RenderMeteor();
	void GiveMeteorInfo(double * x, double * y, int ID, double* meteor_radius,bool* meteor_flag);
	void DestroyMeteor(int ID);
};

class HitJudge {
private:
	double recieve_ammo_position_x;
	double recieve_ammo_position_y;
	double recieve_ammo_radius;
	bool recieve_ammo_flag;
	double recieve_meteor_position_x;
	double recieve_meteor_position_y;
	double recieve_meteor_radius;
	bool recieve_meteor_flag;
	double delta_x;
	double delta_y;
	double powerd_distance;
	double radius;
public:
	HitJudge();
	void UpdateHitJudge();
};

class Time {
private:
	long long now_time;
	long long last_time;
	double delta_time;
public:
	void GetNowTime(); //GameStateのEnter・Loopで呼び出す
	double DeltaTime();
};