#pragma once
#include "DxLib.h"
#include "Vector.h"
#include "../../Matsunaga/Meteorite/Meteorite.h"

#include <vector>

class Meteoroid;
class Bullet;

class GameScene {
private:
    std::vector<Meteorite*>/*型を「Meteorite」に変更*/ meteors;  // 隕石の保管
    std::vector<Bullet*> bullets;     // 弾の保管

public:
    void Init(Vector2 pos, double size, int health); // 初期化
    void Update();                                   // アップデート
    void LoadStage();                                // ステージ読み込み

    std::vector<Meteorite*> GetMeteorite() { return meteors; }
};