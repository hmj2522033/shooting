#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "GameScene.h"

static int imgBackground = -1;
static int imgLogo = -1;
static int imgPress = -1;
static int bgmTitle = -1;

static int blinkTimer = 0;   // 点滅用カウンタ

void InitTitleScene() {

    imgBackground = LoadGraph("Resource/title_bg.png");
    imgLogo = LoadGraph("Resource/title_logo.png");
    imgPress = LoadGraph("Resource/press_any_key.png");

    if (bgmTitle == -1) {
        bgmTitle = LoadSoundMem("Resource/bgm.mp3");
    }
    PlaySoundMem(bgmTitle, DX_PLAYTYPE_LOOP);


    blinkTimer = 0;  // 初期化
}

void UpdateTitleScene() {

    blinkTimer++;  // 毎フレーム増える

    char keys[256];

    static char oldKeys[256] = { 0 };
    GetHitKeyStateAll(keys);

    bool anyKeyPressed = false;
    for (int i = 0; i < 256; i++) {
        if (keys[i] && !oldKeys[i]) {   // 押した瞬間だけ
            anyKeyPressed = true;
            break;
        }
    }

    if (anyKeyPressed) {
        StopSoundMem(bgmTitle);
        InitGameScene();
        SceneManager::ChangeScene(SCENE_GAME);
    }

    memcpy(oldKeys, keys, 256);
}

void DrawTitleScene() {

    DrawGraph(0, 0, imgBackground, TRUE);

    int w, h;

    //ロゴ
    GetGraphSize(imgLogo, &w, &h);
    DrawGraph((960 - w) / 2, 120, imgLogo, TRUE);

    //Press Any Key
    if ((blinkTimer / 30) % 2 == 0) {
        GetGraphSize(imgPress, &w, &h);
        DrawGraph((960 - w) / 2, 340, imgPress, TRUE);
    }
}