#include "Timer.h"
#include "DxLib.h"
#include "Boss.h"
#include "StockUI.h"

static int bossTimer = 0;
static const int BOSS_TIME = 60 * 60;   // 60秒
static int bossUiImg = -1;

void InitBossTimer() {
    bossTimer = 0;
    if (bossUiImg == -1) {
        bossUiImg = LoadGraph("Resource/boss_timer_ui.png");
    }
}

void UpdateBossTimer() {

    // デバッグ：Bキーで即ボス戦開始
    if (CheckHitKey(KEY_INPUT_B)) {
        bossTimer = BOSS_TIME;  
    }

    bossTimer++;
}

int GetBossRemainSec() {
    int remain = (BOSS_TIME - bossTimer) / 60;
    if (remain < 0) remain = 0;
    return remain;
}

bool IsBossTime() {
    return bossTimer >= BOSS_TIME;
}

void DrawBossTimerUI() {

    if (gBoss.active) return;

    int remain = GetBossRemainSec();

    // 背景画像（あなたのボスUI画像）
    DrawGraph(290, 460, bossUiImg, TRUE);

    DrawNumber(570, 454, remain);
}