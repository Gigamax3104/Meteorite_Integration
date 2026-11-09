#include "main.h"
#include "Turret.h"
#include "Ammo.h"
#include "Temp.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE); // ウィンドウモードに設定
    DxLib_Init();   // DXライブラリ初期化処理
    SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に指定
    SetWindowSizeChangeEnableFlag(FALSE, FALSE);//ウィンドウサイズに合わせて拡大縮小しないようにする
    //SetWindowSize(1920, 1080);//1920 × 1080のサイズに変更
    SetWindowSizeChangeEnableFlag(TRUE);//自由にサイズ変更できるようにする
    //初期化
    Initialize();

    //画面のクリアと裏画面と表画面の切り替えとメッセージの処理
    while (ClearDrawScreen() == 0 && ProcessMessage() == 0) {
        //Escを押すと退出する
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
            break;
        }
        Input();
        Update();
        Render();
        ScreenFlip();

    }
    DxLib_End();    // DXライブラリ終了処理
    return 0;
}

void Initialize() {
    ptr_class_time->GetNowTime();
    ptr_class_size->GetWindowSize();
    ptr_class_turret->InitTurretPosition();
}

void Input() {
    ptr_class_turret->InputTurretPosition();
    ptr_class_turret->InputTurretShoot();

    //暫定的な関数
    ptr_class_meteor->InputMeteorSummon();
}

void Update() {
    //暫定的な関数
    ptr_class_time->GetNowTime();
    ptr_class_time->DeltaTime();

    //恒久的な関数
    ptr_class_turret->UpdateTurretPosition();
    ptr_class_ammo->SetAmmoPosition();
    ptr_class_turret->RenderTurretAndTurretCenterPoint();

    //暫定的な関数
    ptr_class_meteor->UpdateMeteorSummon();
    ptr_class_hit_judge->UpdateHitJudge();
 
}

void Render() {
    ptr_class_ammo->RenderAmmo();

    //暫定的な関数
    ptr_class_meteor->RenderMeteor();
}
