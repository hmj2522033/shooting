#include "EnemyShot.h"
#include "DxLib.h"

EnemyShot* gEnemyShots[MAX_ENEMY_SHOTS];

int EnemyShot::imgNormal = -1;
int EnemyShot::imgRed = -1;
int EnemyShot::imgBlue = -1;
int EnemyShot::imgGreen = -1;
int EnemyShot::imgPurple = -1;

EnemyShot::EnemyShot() {
    active = false;
    x = y = 0;
    vx = vy = 0;
    type = SHOT_NORMAL;
}

void EnemyShot::Fire(float px, float py, float vx_, float vy_, EnemyShotType t) {
    active = true;
    x = px;
    y = py;
    vx = vx_;
    vy = vy_;
    type = t;
}

void EnemyShot::Update() {
    if (!active) return;

    x += vx;
    y += vy;

    if (x < -50 || x > 1010 || y < -50 || y > 600) {
        active = false;
    }
}

void EnemyShot::Draw() {
    if (!active) return;

    int img = 0;
    switch (type) {
    case SHOT_NORMAL: img = imgNormal; break;
    case SHOT_RED:    img = imgRed;    break;
    case SHOT_BLUE:   img = imgBlue;   break;
    case SHOT_GREEN:  img = imgGreen;  break;
    case SHOT_PURPLE: img = imgPurple; break;
    }

    DrawRotaGraph((int)x, (int)y, 1.0, 0.0, img, TRUE);
}

void InitEnemyShots() {

    if (EnemyShot::imgNormal == -1) {
        EnemyShot::imgNormal = LoadGraph("Resource/shot.png");
        EnemyShot::imgRed = LoadGraph("Resource/bulletRed.png");
        EnemyShot::imgBlue = LoadGraph("Resource/bulletBlue.png");
        EnemyShot::imgGreen = LoadGraph("Resource/bulletGreen.png");
        EnemyShot::imgPurple = LoadGraph("Resource/bulletPurple.png");
    }

    for (int i = 0; i < MAX_ENEMY_SHOTS; i++) {
        gEnemyShots[i] = new EnemyShot();
    }
}

void CreateEnemyShot(float x, float y, float vx, float vy, EnemyShotType t) {
    for (int i = 0; i < MAX_ENEMY_SHOTS; i++) {
        if (!gEnemyShots[i]->active) {
            gEnemyShots[i]->Fire(x, y, vx, vy, t);
            break;
        }
    }
}

void UpdateEnemyShots() {
    for (int i = 0; i < MAX_ENEMY_SHOTS; i++) {
        gEnemyShots[i]->Update();
    }
}

void DrawEnemyShots() {
    for (int i = 0; i < MAX_ENEMY_SHOTS; i++) {
        gEnemyShots[i]->Draw();
    }
}