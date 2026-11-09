#pragma once
#include "DxLib.h"
#include "Vector.h"

class Meteoroid {
public:
    Vector2 pos;       // 現在の座標
    Vector2 direction; // 進む方向（正規化されたベクトル）
    double speed;      // スピード

    // コンストラクタ（初期位置、ターゲット位置、スピードを受け取る）
    Meteoroid(Vector2 startPos, Vector2 targetPos, double s) {
        pos = startPos;
        speed = s;

        // 「ターゲットの位置 - 自分の位置」で向かうべき方向のベクトルを作り、
        // Normalized() で長さを「1」のきれいな向きデータにする
        direction = (targetPos - startPos).Normalized();
    }

    // 毎フレームの移動処理
    void Update() {
        // 方向 × スピード を足し算して、真ん中へ進ませる
        pos += direction * speed;
    }

    // 描画処理
    void Draw() {
        DrawCircle((int)pos.x, (int)pos.y, 20, GetColor(255, 100, 100), TRUE);
    }
};