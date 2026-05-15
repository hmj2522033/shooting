#include "AbsorbSystem.h"
#include "EnemyShot.h"
#include "Shot.h"
#include "Player.h"

int AbsorbSystem::absorbGauge = 5;
bool AbsorbSystem::absorbMode = false;
int AbsorbSystem::absorbTimer = 0;

int AbsorbSystem::fireStock = 0;
int AbsorbSystem::specialStock = 0;
bool AbsorbSystem::hasBarrier = false;

int AbsorbSystem::gaugeImg[6];
int AbsorbSystem::animImg = -1;
int AbsorbSystem::animFrame = 0;
int AbsorbSystem::animTimer = 0;

int AbsorbSystem::barrierTimer = 0;
int AbsorbSystem::barrierImg = -1;

void AbsorbSystem::Init() {

    gaugeImg[5] = LoadGraph("Resource/gauge_1.png");
    gaugeImg[4] = LoadGraph("Resource/gauge_2.png");
    gaugeImg[3] = LoadGraph("Resource/gauge_3.png");
    gaugeImg[2] = LoadGraph("Resource/gauge_4.png");
    gaugeImg[1] = LoadGraph("Resource/gauge_5.png");
    gaugeImg[0] = LoadGraph("Resource/gauge_6.png");

    animImg = LoadGraph("Resource/absorb_anim.png");

    // バリア画像（あなたが渡した黄色い菱形）
    barrierImg = LoadGraph("Resource/Barrier.png");

    absorbGauge = 5;
    absorbMode = false;
    absorbTimer = 0;

    fireStock = 0;
    specialStock = 0;
    hasBarrier = false;

    barrierTimer = 0;
}

void AbsorbSystem::Update(bool absorbPressed) {

    // ★ バリア時間
    if (barrierTimer > 0) {
        barrierTimer--;
    }

    // 吸収開始
    if (absorbPressed && absorbGauge > 0 && !absorbMode) {
        absorbGauge--;
        absorbMode = true;
        absorbTimer = 60; // 1秒
    }

    // 吸収中
    if (absorbMode) {
        absorbTimer--;
        if (absorbTimer <= 0) absorbMode = false;

        // アニメ更新
        animTimer++;
        if (animTimer >= 10) {
            animTimer = 0;
            animFrame++;
            if (animFrame >= 6) animFrame = 0;
        }
    }

    // デバッグ
    char keys[256];
    GetHitKeyStateAll(keys);

    if (keys[KEY_INPUT_Y]) {
        fireStock++;
    }

    if (keys[KEY_INPUT_U]) {
        specialStock++;
    }

    if (keys[KEY_INPUT_I]) {
        hasBarrier = true;
    }
}

void AbsorbSystem::UseFire(const Player& player) {
    if (fireStock > 0) {
        fireStock--;
        FireShotFire(player.x, player.y - 12);
    }
}

void AbsorbSystem::UseSpecial(const Player& player) {
    if (specialStock > 0) {
        specialStock--;
        FireShotSpecial(player.x, player.y - 12);
    }
}

void AbsorbSystem::UseBarrier() {
    if (hasBarrier) {
        hasBarrier = false;
        barrierTimer = 300; // 5秒
    }
}

void AbsorbSystem::CheckHit(float px, float py, int& hp) {

    const float SHOT_R = 8.0f;
    const float ABSORB_R = 50.0f;
    const float PLAYER_R = 12.0f;

    for (int i = 0; i < MAX_ENEMY_SHOTS; i++) {
        if (!gEnemyShots[i]->active) continue;

        float dx = px - gEnemyShots[i]->x;
        float dy = py - gEnemyShots[i]->y;
        float dist = dx * dx + dy * dy;

        float hitR = absorbMode ? ABSORB_R : PLAYER_R;
        float hitDist = (hitR + SHOT_R) * (hitR + SHOT_R);

        if (dist < hitDist) {

            // 吸収モード中
            if (absorbMode && absorbGauge >= 0) {

                switch (gEnemyShots[i]->type) {
                case SHOT_RED:    fireStock += 2; break;
                case SHOT_BLUE:   specialStock += 1; break;
                case SHOT_GREEN:  hasBarrier = true; break;
                case SHOT_PURPLE:
                    absorbGauge += 2;
                    if (absorbGauge > 5) absorbGauge = 5;
                    break;
                }

                gEnemyShots[i]->active = false;
                continue;
            }

            // バリア中は無敵
            if (barrierTimer > 0) {
                gEnemyShots[i]->active = false;
                continue;
            }

            // 通常ダメージ
            if (hasBarrier) {
                hasBarrier = false;
            }
            else {
                hp--;
            }

            gEnemyShots[i]->active = false;
        }
    }
}

void AbsorbSystem::DrawUI() {
    int g = absorbGauge;
    if (g < 0) g = 0;
    if (g > 5) g = 5;

    DrawGraph(20, 460, gaugeImg[g], TRUE);
}

void AbsorbSystem::DrawAnimation(float px, float py) {
    if (!absorbMode) return;

    int sx = (animFrame % 3) * 100;
    int sy = (animFrame / 3) * 100;

    DrawRectGraph(px - 50, py - 50, sx, sy, 100, 100, animImg, TRUE);
}

void AbsorbSystem::DrawBarrier(float px, float py) {
    if (barrierTimer > 0) {

        // 回転角度（毎フレーム少しずつ回す）
        static float angle = 0.0f;
        angle += 0.05f;   // 回転速度（調整可）

        // 点滅（5フレームごとにON/OFF）
        if ((barrierTimer / 3) % 2 == 0) {

            DrawRotaGraph(
                (int)px,
                (int)py,
                1.0,
                angle,
                barrierImg,
                TRUE
            );
        }
    }
}