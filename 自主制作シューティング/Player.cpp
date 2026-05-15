#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Shot.h"
#include "AbsorbSystem.h"

extern Enemy* gEnemies[];

static int playerImg = -1;

Player::Player() {
    x = 480;
    y = 450;
    hp = 3;

    invincible = false;
    invincibleTimer = 0;

    absorbPressed = false; // 吸収ボタン状態

    if (playerImg == -1) {
        playerImg = LoadGraph("Resource/player.png");
    }
}

void Player::Update() {

    // 無敵時間処理
    if (invincible) {
        invincibleTimer++;
        if (invincibleTimer >= 120) { // 2秒
            invincible = false;
            invincibleTimer = 0;
        }
    }

    // 移動
    const float speed = 5.0f;

    if (CheckHitKey(KEY_INPUT_W)) y -= speed;
    if (CheckHitKey(KEY_INPUT_S)) y += speed;
    if (CheckHitKey(KEY_INPUT_A)) x -= speed;
    if (CheckHitKey(KEY_INPUT_D)) x += speed;

    if (CheckHitKey(KEY_INPUT_1)) AbsorbSystem::UseFire(*this);
    if (CheckHitKey(KEY_INPUT_2)) AbsorbSystem::UseSpecial(*this);
    if (CheckHitKey(KEY_INPUT_3)) AbsorbSystem::UseBarrier();

    // 画面外に出ないようにする
    if (x < 0) x = 0;
    if (x > 960) x = 960;
    if (y < 0) y = 0;
    if (y > 540) y = 540;
}

void Player::Draw() {

    // 無敵中は点滅
    if (invincible) {
        if ((invincibleTimer / 4) % 2 == 0) {
            DrawRotaGraph((int)x, (int)y, 1.0, 0.0, playerImg, TRUE);
        }
    }
    else {
        DrawRotaGraph((int)x, (int)y, 1.0, 0.0, playerImg, TRUE);
    }
}

void Player::CheckHit() {

    if (invincible) return;

    const float PLAYER_RADIUS = 20.0f;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!gEnemies[i]->active) continue;

        float dx = x - gEnemies[i]->x;
        float dy = y - gEnemies[i]->y;
        float dist = dx * dx + dy * dy;

        float hitDist = (PLAYER_RADIUS + gEnemies[i]->hitR);
        hitDist *= hitDist;

        if (dist < hitDist) {

            // ★ プレイヤーに1ダメージ
            hp--;
            invincible = true;
            invincibleTimer = 0;

            // ★ 敵にも1ダメージ
            gEnemies[i]->hp--;

            // ★ 敵のHPが0なら消滅
            if (gEnemies[i]->hp <= 0) {
                gEnemies[i]->active = false;
                CreateExplosion(gEnemies[i]->x, gEnemies[i]->y);
            }

            break;
        }
    }
}