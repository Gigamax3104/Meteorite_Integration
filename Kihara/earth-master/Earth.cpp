#include "Earth.h"

// コンストラクタ
// 地球生成時にHPを100で初期化する
Earth::Earth() {
	m_hp = 100;
}

// ダメージ処理
// 引数で受け取った値だけHPを減らす
void Earth::Damage(int damage) {
	// HPを減少させる
	m_hp -= damage;

	// HPが0未満にならないようにする
	if (m_hp < 0) {
		m_hp = 0;
	}
}

// 現在のHPを取得する
int Earth::GetHp() const {
	return m_hp;
}

// 地球が破壊されたか判定する
// HPが0以下ならtrueを返す
bool Earth::IsDead() const {
	return m_hp <= 0;
}