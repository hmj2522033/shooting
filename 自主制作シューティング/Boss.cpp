#include "Boss.h"
#include "EnemyShot.h"
#include "Explosion.h"
#include "Shot.h"
#include <cmath>

Boss gBoss;
int Boss::img = -1;

Boss::Boss() {
}

void Boss::Init() {
    if (img == -1) {
        img = LoadGraph("Resource/boss.png");
    }

    active = true;
    x = 480;
    y = -100;
    vx = 2.0f;
    hp = maxHp = 70;
    phase = 1;
    timer = 0;
    shotTimer = 0;
    dead = false;
    deathTimer = 0;
}

void Boss::Update() {

    // ★ active でなくても dead のときは Update を続行する
    if (!active && !dead) return;

    // ★ 撃破後の処理（deathTimer を減らす）
    if (dead) {
        if (deathTimer > 0) {
            deathTimer--;
        }
        return; // 撃破後はここで終了（弾幕などは動かさない）
    }
    // ★★★ 撃破判定はここに置く（最初） ★★★
    if (hp <= 0) {
        dead = true;
        active = false;
        CreateExplosion(x, y);
        deathTimer = 60;
        return;
    }


    // --- ここから通常のボス処理 ---
    timer++;
    shotTimer++;

    // 入場演出
    if (y < 120) {
        y += 1.0f;
        return;
    }

    // フェーズ切り替え
    if (hp > maxHp * 0.66f) phase = 1;
    else if (hp > maxHp * 0.33f) phase = 2;
    else phase = 3;

    switch (phase) {
    case 1: UpdatePhase1(); break;
    case 2: UpdatePhase2(); break;
    case 3: UpdatePhase3(); break;
    }
}

//
// -----------------------------
// ★ パターン1：赤 or 青 or 紫弾
// -----------------------------
//
void Boss::UpdatePhase1() {

    x += sin(timer * 0.03f) * 2.0f;

    if (shotTimer % 40 == 0) {

        EnemyShotType shotType;

        int r = rand() % 3;
        if (r == 0) shotType = SHOT_RED;
        else if (r == 1) shotType = SHOT_BLUE;
        else shotType = SHOT_PURPLE;

        CreateEnemyShot(x, y + 40, 0, 4.0f, shotType);
    }
}
//
// -----------------------------
// パターン2：高速移動＋3WAY
// -----------------------------
//
void Boss::UpdatePhase2() {

    x += vx;
    if (x < 100 || x > 860) vx = -vx;

    if (shotTimer % 30 == 0) {
        CreateEnemyShot(x, y, -2.0f, 4.0f, SHOT_NORMAL);
        CreateEnemyShot(x, y, 0.0f, 5.0f, SHOT_NORMAL);
        CreateEnemyShot(x, y, 2.0f, 4.0f, SHOT_NORMAL);
    }
}

//
// -----------------------------
// パターン3：怒りモード（渦巻き弾）
// -----------------------------
//
void Boss::UpdatePhase3() {

    // 中央に寄る
    if (x < 480) x += 1.5f;
    if (x > 480) x -= 1.5f;

    // 渦巻き弾
    if (shotTimer % 10 == 0) {
        float angle = (timer % 360) * 3.14f / 180.0f;

        float vx = cos(angle) * 3.0f;
        float vy = sin(angle) * 3.0f;

        CreateEnemyShot(x, y, vx, vy, SHOT_BLUE);
    }
}

void Boss::Draw() {
    if (!active) return;
    DrawRotaGraph((int)x, (int)y, 1.0, 0.0, img, TRUE);
}

bool Boss::CheckHit(float px, float py) {

    // コア中心の 70×70 判定
    const float HIT_W = 70.0f;
    const float HIT_H = 70.0f;

    float left = x - HIT_W / 2;
    float right = x + HIT_W / 2;
    float top = y - HIT_H / 2;
    float bottom = y + HIT_H / 2;

    return (px > left && px < right && py > top && py < bottom);
}
