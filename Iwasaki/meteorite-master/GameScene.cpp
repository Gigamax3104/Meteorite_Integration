#include "GameScene.h"
#include "Meteoroid.h"
#include <cstdlib>
#include <cmath> // 角度計算用（cos, sin）

void GameScene::Init(Vector2 pos, double size, int health) {
    // 初期化処理
}

void GameScene::Update() {
    // 画面の中心座標（例：幅640×高さ480の中央）
    Vector2 centerPos(320.0, 240.0);

    // 約2%の確率で、四方八方から隕石を生成する
    if (GetRand(100) < 2) {
        // 1. 周囲のどこから出すか（0〜360度をランダムに決める）
        double angle = (double)(GetRand(360)) * 3.14159265 / 180.0;
        double radius = 400.0; // 画面の中心から少し離れた外側から発生させる

        // 2. 角度と半径から、出現する座標（画面の外）を計算する
        Vector2 spawnPos(
            centerPos.x + cos(angle) * radius,
            centerPos.y + sin(angle) * radius
        );

        // 3. スピードを決める
        double speed = 1.5 + (double)(GetRand(2));

        // 4. 生成してリスト（meteors）に追加する（中心に向かうように centerPos を渡す）
        Meteorite* newMeteor = new Meteorite(spawnPos, speed, 30, centerPos);
        meteors.push_back(newMeteor);
    }

   

    // 隕石を描画する
    for (int i = 0; i < meteors.size(); i++) {
        meteors[i]->Draw();
    }
}

void GameScene::LoadStage() {
    // ステージ読み込み処理
}