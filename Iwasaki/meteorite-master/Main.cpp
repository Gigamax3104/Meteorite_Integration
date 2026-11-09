#include "DxLib.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) {
        return -1;
    }

    GameScene gameScene;
    gameScene.LoadStage();
    gameScene.Init(Vector2(0, 0), 1.0, 100);

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        gameScene.Update();
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}