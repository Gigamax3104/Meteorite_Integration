#pragma once
//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//プレイヤーに関するクラス宣言

class Size {
protected:
	int window_size_x;
	int window_size_y;
	int color_depth;
public:
	//コンストラクタ
	Size();
	//画面サイズを取得
	void GetWindowSize();
	//画面のXサイズを渡す
	int GiveWindowSizeX();
	//画面のYサイズを渡す
	int GiveWindowSizeY();
};
//static Size size;
//static Size* ptr_class_size = &size;

class Turret {
private:
	double turret_position_x;
	double turret_position_y;
	double turret_center_position_x;
	double turret_center_position_y;
	double turret_move_radius;
	bool input_move_clockwise;
	bool input_move_counter_clockwise;
	//turret_degreeは度数法であって弧度法ではない
	double turret_degree;
	double turret_move_speed;
	bool input_turret_shoot;

public:
	//コンストラクタ
	Turret();
	//砲台の初期座標設定
	void InitTurretPosition();
	//プレイヤーのインプットを受け取る
	void InputTurretPosition();
	//プレイヤーの位置更新
	void UpdateTurretPosition();
	//プレイヤーのX座標情報を渡す
	double GiveTurretPositionX();
	//プレイヤーののY座標情報を渡す
	double GiveTurretPositionY();
	//プレイヤーの偏角を渡す
	double GiveTurretDegree();
	//プレイヤーの発射入力を検知する
	void InputTurretShoot();
	//プレイヤーとプレイヤーの移動の中心を表示する
	void RenderTurretAndTurretCenterPoint();
};