#pragma once

// 地球クラス
class Earth {
private:
	// 地球の現在HP
	int m_hp;

public:
	// コンストラクタ
	// 地球生成時にHPを初期化する
	Earth();

	// ダメージ処理
	// 引数で受け取った分だけHPを減らす
	void Damage(int damage);

	// HP取得
	// 現在のHPを返す
	int GetHp() const;

	// 生存判定
	// HPが0以下ならtrueを返す
	bool IsDead() const;
};