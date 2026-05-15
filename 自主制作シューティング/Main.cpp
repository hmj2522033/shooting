#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    SetGraphMode(960, 540, 32);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager::Init();

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        SceneManager::Update();
        SceneManager::Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}