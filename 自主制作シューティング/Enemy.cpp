#include "Enemy.h"
#include "EnemyShot.h"
#include "Explosion.h"
#include "Shot.h"
#include <cmath>

Enemy* gEnemies[MAX_ENEMIES];

int Enemy::imgA = -1;
int Enemy::imgB = -1;
int Enemy::imgC = -1;
int Enemy::imgD = -1;
int Enemy::imgE = -1;

Enemy::Enemy() {
    active = false;
    x = y = 0;
    vx = vy = 0;
    hp = 1;
    shotTimer = 0;
}

void Enemy::Spawn(EnemyType t, float px, float py) {
    active = true;
    type = t;
    x = px;
    y = py;
    shotTimer = 0;

    switch (type) {
    case ENEMY_A:
        hp = 1;
        vx = 0;
        vy = 1.5f;
        hitR = 25.0f;
        break;

    case ENEMY_B:
        hp = 1;
        vx = 2.0f;
        vy = 1.5f;
        hitR = 25.0f;
        break;

    case ENEMY_C:
        hp = 5;
        vx = 1.0f;
        vy = 1.0f;
        hitR = 35.0f;
        break;

    case ENEMY_D:
        hp = 1;
        vx = 3.0f;
        vy = 1.5f;
        hitR = 30.0f;
        break;

    case ENEMY_E:
        hp = 1;
        vx = 2.0f;
        vy = 1.5f;
        hitR = 25.0f;
        break;
    }
}

void Enemy::Update() {
    if (!active) return;

    shotTimer++;

    switch (type) {

    case ENEMY_A:
        y += vy;
        break;

    case ENEMY_B:
        x += vx;
        if (x < 50 || x > 910) vx = -vx;
        y += vy;

        if (shotTimer % 90 == 0) {
            CreateEnemyShot(x, y + 20, 0, 4.0f, SHOT_RED);
        }
        break;

    case ENEMY_C:
        x += vx * 0.5f;
        if (x < 50 || x > 910) vx = -vx;
        y += vy;

        if (shotTimer % 120 == 0) {
            CreateEnemyShot(x, y + 20, 0, 3.0f, SHOT_BLUE);
        }
        if (shotTimer % 300 == 0) {
            CreateEnemyShot(x, y + 20, 0, 3.0f, SHOT_GREEN);
        }
        break;

    case ENEMY_D:
        x += vx;
        if (x < 50 || x > 910) vx = -vx;
        y += vy;

        if (shotTimer % 60 == 0) {
            CreateEnemyShot(x, y, -2.0f, 4.0f, SHOT_NORMAL);
            CreateEnemyShot(x, y, 0.0f, 4.5f, SHOT_NORMAL);
            CreateEnemyShot(x, y, 2.0f, 4.0f, SHOT_NORMAL);
        }
        break;

    case ENEMY_E:
        x += vx;
        if (x < 50 || x > 910) vx = -vx;
        y += vy;

        if (shotTimer % 60 == 0) {
            CreateEnemyShot(x, y + 20, 0, 4.0f, SHOT_PURPLE);
        }
        break;
    }

    if (y > 600) active = false;
}

void Enemy::Draw() {
    if (!active) return;

    int img = 0;
    switch (type) {
    case ENEMY_A: img = imgA; break;
    case ENEMY_B: img = imgB; break;
    case ENEMY_C: img = imgC; break;
    case ENEMY_D: img = imgD; break;
    case ENEMY_E: img = imgE; break;
    }

    DrawRotaGraph((int)x, (int)y, 1.0, 0.0, img, TRUE);
}

void InitEnemies() {

    if (Enemy::imgA == -1) {
        Enemy::imgA = LoadGraph("Resource/enemyA.png");
        Enemy::imgB = LoadGraph("Resource/enemyB.png");
        Enemy::imgC = LoadGraph("Resource/enemyC.png");
        Enemy::imgD = LoadGraph("Resource/enemyD.png");
        Enemy::imgE = LoadGraph("Resource/enemyE.png");
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        gEnemies[i] = new Enemy();
    }
}

void SpawnEnemy(EnemyType t, float x, float y) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!gEnemies[i]->active) {
            gEnemies[i]->Spawn(t, x, y);
            break;
        }
    }
}

void UpdateEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        gEnemies[i]->Update();
    }
}

void DrawEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        gEnemies[i]->Draw();
    }
}

void CheckHitEnemies() {
    const float SHOT_R = 8.0f;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!gEnemies[i]->active) continue;

        float enemyR = gEnemies[i]->hitR;
        float HIT = (SHOT_R + enemyR) * (SHOT_R + enemyR);

        for (int j = 0; j < MAX_SHOTS; j++) {
            if (!gShots[j]->active) continue;

            float dx = gEnemies[i]->x - gShots[j]->x;
            float dy = gEnemies[i]->y - gShots[j]->y;
            float dist = dx * dx + dy * dy;

            if (dist < HIT) {

                // D：特殊弾でしか倒せない
                if (gEnemies[i]->type == ENEMY_D) {
                    if (gShots[j]->type == SHOT_SPECIAL) {
                        gEnemies[i]->hp--;
                    }
                    gShots[j]->active = false;

                    if (gEnemies[i]->hp <= 0) {
                        CreateExplosion(gEnemies[i]->x, gEnemies[i]->y);
                        gEnemies[i]->active = false;
                    }
                    break;
                }

                // E：通常弾で回復、火の玉と特殊弾はダメージ
                if (gEnemies[i]->type == ENEMY_E) {

                    if (gShots[j]->type == SHOT_NORMAL) {
                        gEnemies[i]->hp++;
                    }
                    else if (gShots[j]->type == SHOT_FIRE) {
                        gEnemies[i]->hp -= 3;
                    }
                    else if (gShots[j]->type == SHOT_SPECIAL) {
                        gEnemies[i]->hp--;
                    }

                    gShots[j]->active = false;

                    if (gEnemies[i]->hp <= 0) {
                        CreateExplosion(gEnemies[i]->x, gEnemies[i]->y);
                        gEnemies[i]->active = false;
                    }
                    break;
                }

                // 通常の敵
                if (gShots[j]->type == SHOT_FIRE) {
                    gEnemies[i]->hp -= 3;
                }
                else {
                    gEnemies[i]->hp--;
                }

                gShots[j]->active = false;

                if (gEnemies[i]->hp <= 0) {
                    CreateExplosion(gEnemies[i]->x, gEnemies[i]->y);
                    gEnemies[i]->active = false;
                }
                break;
            }
        }
    }
}