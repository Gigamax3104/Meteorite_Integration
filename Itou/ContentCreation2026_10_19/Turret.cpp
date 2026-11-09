#include <cmath>
#include "Turret.h"
#include "Ammo.h"
#include "Dxlib.h"
#include "Temp.h"
//関数名、クラス名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//プレイヤーに関するクラス定義

////////////////////////////////////////////////////////////////////
//コンストラクタ
Size::Size() {
	window_size_x = 0;
	window_size_y = 0;
	color_depth = 0;
}

Turret::Turret() {
	turret_position_x = 0;
	turret_position_y = 0;
	turret_center_position_x = 0;
	turret_center_position_y = 0;
	turret_move_radius = 100;
	input_move_clockwise = false;
	input_move_counter_clockwise = false;
	turret_degree = 0;
	turret_move_speed = 1;
	input_turret_shoot = false;

}

////////////////////////////////////////////////////////////////////

//画面サイズを獲得
void Size::GetWindowSize() {
	GetScreenState(&ptr_class_size->window_size_x, &ptr_class_size->window_size_y, &ptr_class_size->color_depth);
}

//画面のXサイズを渡す
int Size::GiveWindowSizeX() {
	return ptr_class_size->window_size_x;
}

//画面のYサイズを渡す
int Size::GiveWindowSizeY() {
	return ptr_class_size->window_size_y;
}

//タレットの初期座標設定
void Turret::InitTurretPosition() {
	ptr_class_turret->turret_center_position_x = ptr_class_size->GiveWindowSizeX() / 2;
	ptr_class_turret->turret_center_position_y = ptr_class_size->GiveWindowSizeY() / 2;
	ptr_class_turret->turret_position_x = ptr_class_turret->turret_center_position_x;
	ptr_class_turret->turret_position_y = ptr_class_turret->turret_center_position_y - ptr_class_turret->turret_move_radius;
	ptr_class_turret->turret_degree = 90;
}

//プレイヤーのインプットを受け取る
void Turret::InputTurretPosition() {
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		ptr_class_turret->input_move_clockwise = true;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		ptr_class_turret->input_move_counter_clockwise = true;
	}
}

void Turret::UpdateTurretPosition() {
	if (ptr_class_turret->input_move_clockwise) {
		ptr_class_turret->turret_degree -= 72 * ptr_class_time->DeltaTime();
		ptr_class_turret->input_move_clockwise = false;
	}
	if (ptr_class_turret->input_move_counter_clockwise) {
		ptr_class_turret->turret_degree += 72 * ptr_class_time->DeltaTime();
		ptr_class_turret->input_move_counter_clockwise = false;
	}
	ptr_class_turret->turret_position_x = (cos(ptr_class_turret->turret_degree / 180 * 3.141592 * ptr_class_turret->turret_move_speed) * ptr_class_turret->turret_move_radius + ptr_class_turret->turret_center_position_x);
	ptr_class_turret->turret_position_y = ( - 1 * sin(ptr_class_turret->turret_degree / 180 * 3.141592 * ptr_class_turret->turret_move_speed) * ptr_class_turret->turret_move_radius + ptr_class_turret->turret_center_position_y);
}

//プレイヤーのX座標情報を渡す
double Turret::GiveTurretPositionX() {
	return ptr_class_turret->turret_position_x;
}

//プレイヤーのY座標情報を渡す
double Turret::GiveTurretPositionY() {
	return ptr_class_turret->turret_position_y;
}

//プレイヤーの偏角を渡す
double Turret::GiveTurretDegree() {
	return ptr_class_turret->turret_degree;
}

void Turret::InputTurretShoot() {
	//プレイヤーの発射入力を検知する
	if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
		ptr_class_ammo->SetAmmoSummon();
	}
}

//temp
void Turret::RenderTurretAndTurretCenterPoint() {
	//プレイヤーとプレイヤーの移動の中心を描画
	DrawPixel(ptr_class_turret->turret_center_position_x, ptr_class_turret->turret_center_position_y, 0xffffff);
	DrawPixel(ptr_class_turret->turret_position_x, ptr_class_turret->turret_position_y, 0xffffff);
	DrawCircle(ptr_class_turret->turret_center_position_x, ptr_class_turret->turret_center_position_y, 3, 0xffffff, true);
	DrawCircle(ptr_class_turret->turret_position_x, ptr_class_turret->turret_position_y, 3, 0xffffff, true);
}
