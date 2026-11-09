#include <iostream>
#include "Earth.h"

using namespace std;

// すべてAI使用

int main()
{
    // 地球オブジェクトを生成
    Earth earth;

    // 現在のHPを表示
    cout << "HP : " << earth.GetHp() << endl;

    // 地球に10ダメージを与える
    earth.Damage(10);

    // ダメージ後のHPを表示
    cout << "HP : " << earth.GetHp() << endl;

    // HPが0以下ならゲームオーバー
    if (earth.IsDead())
    {
        cout << "GAME OVER" << endl;
    }

    return 0;
}
