#include "DxLib.h"
#include "SceneManager.h"

static bool bossDefeated = false;
static int remainingTime = 0;
static int bgmResult = -1;

void InitResultScene() {
    if (bgmResult == -1) {
        bgmResult = LoadSoundMem("Resource/Result.mp3");
    }
    PlaySoundMem(bgmResult, DX_PLAYTYPE_LOOP);
}


void SetResult(bool defeated, int timeLeft) {
    bossDefeated = defeated;
    remainingTime = timeLeft;
}

void UpdateResultScene() {
    static int oldSpace = 0;
    int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

    if (nowSpace && !oldSpace) {
        StopSoundMem(bgmResult);
        SceneManager::ChangeScene(SCENE_TITLE);
    }

    oldSpace = nowSpace;
}

void DrawResultScene() {

    DrawString(400, 200, "RESULT", GetColor(255, 255, 255));

    if (bossDefeated) {
        DrawString(350, 300, "ボス撃破！！", GetColor(255, 255, 0));
    }
    else {
        char buf[64];
        sprintf_s(buf, "ボスまであと %d 秒でした", remainingTime);
        DrawString(300, 300, buf, GetColor(255, 200, 200));
    }

    DrawString(350, 400, "Press SPACE to Return", GetColor(255, 255, 255));
}