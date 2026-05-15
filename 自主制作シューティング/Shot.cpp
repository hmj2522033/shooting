#include "Shot.h"

Shot* gShots[MAX_SHOTS];

int Shot::imgNormal = -1;
int Shot::imgFire = -1;
int Shot::imgSpecial = -1;

Shot::Shot() {
    active = false;
    x = y = 0;
    vx = 0;
    vy = -10.0f;
    type = SHOT_BULLET;

    if (imgNormal == -1) {
        imgNormal = LoadGraph("Resource/shot.png");
        imgFire = LoadGraph("Resource/fire_shot.png");
        imgSpecial = LoadGraph("Resource/special_shot.png");
    }
}

void Shot::Update() {
    if (!active) return;

    x += vx;
    y += vy;

    if (y < -20) active = false;
}

void Shot::Draw() {
    if (!active) return;

    int img = imgNormal;
    if (type == SHOT_FIRE) img = imgFire;
    if (type == SHOT_SPECIAL) img = imgSpecial;

    DrawRotaGraph((int)x, (int)y, 1.0, 0.0, img, TRUE);
}

void InitShots() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        gShots[i] = new Shot();
    }
}

void FireShotNormal(float x, float y) {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (!gShots[i]->active) {
            gShots[i]->active = true;
            gShots[i]->x = x;
            gShots[i]->y = y;
            gShots[i]->vy = -10.0f;
            gShots[i]->type = SHOT_BULLET;
            break;
        }
    }
}

void FireShotFire(float x, float y) {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (!gShots[i]->active) {
            gShots[i]->active = true;
            gShots[i]->x = x;
            gShots[i]->y = y;
            gShots[i]->vy = -8.0f;
            gShots[i]->type = SHOT_FIRE;
            break;
        }
    }
}

void FireShotSpecial(float x, float y) {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (!gShots[i]->active) {
            gShots[i]->active = true;
            gShots[i]->x = x;
            gShots[i]->y = y;
            gShots[i]->vy = -7.0f;
            gShots[i]->type = SHOT_SPECIAL;
            break;
        }
    }
}

void UpdateShots() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        gShots[i]->Update();
    }
}

void DrawShots() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        gShots[i]->Draw();
    }
}