#include "Temp.h"
#include "Ammo.h"
#include "Dxlib.h"

//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
// 暫定的な関数の定義
//////////////////////////////////////////////////////////////////////
//コンストラクタ
Meteor::Meteor() {
	for (int i = 0; i < METEOR_DATA_SIZE; ++i) {
		meteor_position_x[i] = 0;
		meteor_position_y[i] = 0;
		meteor_flag[i] = false;
	}
	meteor_radius = 25;
	do_meteor_summon = false;
}

HitJudge::HitJudge() {
	recieve_ammo_position_x = 0;
	recieve_ammo_position_y = 0;
	recieve_ammo_radius = 0;
	recieve_ammo_flag = false;
	recieve_meteor_position_x = 0;
	recieve_meteor_position_y = 0;
	recieve_meteor_radius = 0;
	delta_x = 0;
	delta_y = 0;
	powerd_distance = 0;
	radius = 0;
}

//////////////////////////////////////////////////////////////////////

void Meteor::InputMeteorSummon() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ptr_class_meteor->do_meteor_summon = true;
	}
}

void Meteor::UpdateMeteorSummon(){
	if (ptr_class_meteor->do_meteor_summon == true) {
		ptr_class_meteor->do_meteor_summon = false;
		for (int i = 0; i < METEOR_DATA_SIZE; ++i) {
			if (ptr_class_meteor->meteor_flag[i] == false) {
				int temp_x = 0;
				int temp_y = 0;
				int* x = &temp_x;
				int* y = &temp_y;
				GetMousePoint(x, y);
				ptr_class_meteor->meteor_flag[i] = true;
				ptr_class_meteor->meteor_position_x[i] = temp_x;
				ptr_class_meteor->meteor_position_y[i] = temp_y;
					break;

			}
		}
	}
}

void Meteor::RenderMeteor() {
	for (int i = 0; i < METEOR_DATA_SIZE; ++i) {
		if (ptr_class_meteor->meteor_flag[i] == true) {
			DrawCircle(ptr_class_meteor->meteor_position_x[i], ptr_class_meteor->meteor_position_y[i], ptr_class_meteor->meteor_radius,0xff0000, true);
		}
	}
}

void Meteor::GiveMeteorInfo(double* x, double* y, int ID,double * meteor_radius,bool* meteor_flag) {
	*x = ptr_class_meteor->meteor_position_x[ID];
	*y = ptr_class_meteor->meteor_position_y[ID];
	*meteor_radius = ptr_class_meteor->meteor_radius;
	*meteor_flag = ptr_class_meteor->meteor_flag[ID];
}

void Meteor::DestroyMeteor(int ID) {
	ptr_class_meteor->meteor_flag[ID] = false;
}

void HitJudge::UpdateHitJudge() {
	for (int i = 0; i < AMMO_DATA_SIZE; ++i) {
		ptr_class_ammo->GiveAmmoInfo(&ptr_class_hit_judge->recieve_ammo_position_x, &ptr_class_hit_judge->recieve_ammo_position_y, i,&ptr_class_hit_judge->recieve_ammo_radius,&ptr_class_hit_judge->recieve_ammo_flag);
		if (ptr_class_hit_judge->recieve_ammo_flag == false) {
			continue;
		}
		for (int j = 0; j < METEOR_DATA_SIZE; ++j) {
			ptr_class_meteor->GiveMeteorInfo(&ptr_class_hit_judge->recieve_meteor_position_x, &ptr_class_hit_judge->recieve_meteor_position_y, j, &ptr_class_hit_judge->recieve_meteor_radius,&ptr_class_hit_judge->recieve_meteor_flag);
			if (ptr_class_hit_judge->recieve_meteor_flag == false) {
				continue;
			}
			ptr_class_hit_judge->delta_x = ptr_class_hit_judge->recieve_ammo_position_x - ptr_class_hit_judge->recieve_meteor_position_x;
			ptr_class_hit_judge->delta_y = ptr_class_hit_judge->recieve_ammo_position_y - ptr_class_hit_judge->recieve_meteor_position_y;
			ptr_class_hit_judge->powerd_distance = ptr_class_hit_judge->delta_x * ptr_class_hit_judge->delta_x + ptr_class_hit_judge->delta_y * ptr_class_hit_judge->delta_y;
			ptr_class_hit_judge->radius = (ptr_class_hit_judge->recieve_ammo_radius + recieve_meteor_radius) * (ptr_class_hit_judge->recieve_ammo_radius + recieve_meteor_radius);
			if (ptr_class_hit_judge->radius > ptr_class_hit_judge->powerd_distance) {
				ptr_class_ammo->DestroyAmmo(i);
				ptr_class_meteor->DestroyMeteor(j);
			}
		}
	}
}

void Time::GetNowTime() {
	ptr_class_time->last_time = ptr_class_time->now_time;
	ptr_class_time->now_time = GetNowHiPerformanceCount();
}

double Time::DeltaTime() {
	ptr_class_time->delta_time = (ptr_class_time->now_time - ptr_class_time->last_time) / 1000000.0;
	DrawFormatString(0, 0, 0xffffff, "%d", ptr_class_time->last_time);
	DrawFormatString(0, 15, 0xffffff, "%d", ptr_class_time->now_time);
	DrawFormatString(0, 30, 0xffffff, "%f", ptr_class_time->delta_time);
	return ptr_class_time->delta_time;
}