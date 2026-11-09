#pragma once
#include "Vector.h"
//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース

///////////////////////////////////////////////////////////////////////
//グローバル変数
const int AMMO_DATA_SIZE = 1000;

//////////////////////////////////////////////////////////////////////
//弾に関するクラス宣言
class Ammo {
private:
	double ammo_position_x[AMMO_DATA_SIZE];
	double ammo_position_y[AMMO_DATA_SIZE];
	double ammo_degree[AMMO_DATA_SIZE];
	double ammo_flag[AMMO_DATA_SIZE];
	double ammo_speed;
	double ammo_summon_span;
	double ammo_radius;
	int last_summon_ammo_id;
public:
	Ammo();
	//弾をスポーンさせる
	void SetAmmoSummon();
	//弾の座標を更新する
	void SetAmmoPosition();
	//弾の描画
	void RenderAmmo();
	//弾の諸元情報を渡す
	void GiveAmmoInfo(double* x, double* y, int ID,double* ammo_radius,bool* ammo_flag);
	//弾の消滅
	void DestroyAmmo(int ID);

	double Radius() const;
	bool Flag(int ID) const;
	Vector2 Position(int ID) const;
};

class DynamicAmmo {
private:
	Vector2 ammo_position;
	bool ammo_flag;
public:
};