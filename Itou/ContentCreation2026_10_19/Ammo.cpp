#include "Ammo.h"
#include "Turret.h"
#include <cmath>
#include "Dxlib.h"
//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//弾に関するクラス定義

/////////////////////////////////////////////////////////////////////
//コンストラクタ
Ammo::Ammo() {
	for (int i = 0; i < AMMO_DATA_SIZE; ++i) {
		ammo_position_x[i] = 0;
		ammo_position_y[i] = 0;
		ammo_degree[i] = 0;
		ammo_flag[i] = false;
	}
	last_summon_ammo_id = 0;
	ammo_speed = 1;
	ammo_summon_span = 14;
	ammo_radius = 10;
}
/////////////////////////////////////////////////////////////////////

//弾の発射
void Ammo::SetAmmoSummon() {
	for (int i = 0; i < AMMO_DATA_SIZE; ++i) {
		if (ammo_flag[i] == false) {
			ammo_flag[i] = true;
			ammo_position_x[i] = ptr_class_turret->GiveTurretPositionX();
			ammo_position_y[i] = ptr_class_turret->GiveTurretPositionY();
			ammo_degree[i] = ptr_class_turret->GiveTurretDegree();
			break;
		}
	}
}

//弾の座標を更新する
void Ammo::SetAmmoPosition() {
	for (int i = 0; i < AMMO_DATA_SIZE; ++i) {
		if (ptr_class_ammo->ammo_flag[i]) {
			ptr_class_ammo->ammo_position_x[i] += (cos(ptr_class_ammo->ammo_degree[i] / 180 * 3.141592) * ptr_class_ammo->ammo_speed);
			ptr_class_ammo->ammo_position_y[i] -= (sin(ptr_class_ammo->ammo_degree[i] / 180 * 3.141592) * ptr_class_ammo->ammo_speed);
		}
	}
}

void Ammo::RenderAmmo() {
	//弾の描画
	for (int i = 0; i < AMMO_DATA_SIZE; ++i) {
		if (ptr_class_ammo->ammo_flag[i] == true) {
			DrawCircle(ptr_class_ammo->ammo_position_x[i], ptr_class_ammo->ammo_position_y[i], ptr_class_ammo->ammo_radius, 0x0000ff, false);
		}
	}
}

void Ammo::GiveAmmoInfo(double* x, double * y, int ID,double* ammo_radius,bool* ammo_flag) {
	*x = ptr_class_ammo->ammo_position_x[ID];
	*y = ptr_class_ammo->ammo_position_y[ID];
	*ammo_radius = ptr_class_ammo->ammo_radius;
	*ammo_flag = ptr_class_ammo->ammo_flag[ID];
}

void Ammo::DestroyAmmo(int ID) {
	ptr_class_ammo->ammo_flag[ID] = false;
}

double Ammo::Radius() const {
	return ptr_class_ammo->ammo_radius;
}

bool Ammo::Flag(int ID) const {
	return ptr_class_ammo->ammo_flag[ID];
}

Vector2 Ammo::Position(int ID) const {
	return Vector2(ptr_class_ammo->ammo_position_x[ID], ptr_class_ammo->ammo_position_y[ID]);
}