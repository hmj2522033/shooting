#include "Explosion.h"
#include "DxLib.h"

Explosion* gExplosions[MAX_EXPLOSIONS];
int Explosion::img = -1;

Explosion::Explosion() {
    active = false;
    x = y = 0;
    frame = 0;
    counter = 0;

    if (img == -1) {
        img = LoadGraph("Resource/explosion.png");
    }
}

void Explosion::Start(float px, float py) {
    active = true;
    x = px;
    y = py;
    frame = 0;
    counter = 0;
}

void Explosion::Update() {
    if (!active) return;

    counter++;
    if (counter >= 4) {
        counter = 0;
        frame++;
        if (frame >= 7) {
            active = false;
        }
    }
}

void Explosion::Draw() {
    if (!active) return;

    const int frameW = 128;
    const int frameH = 128;

    int srcX = frame * frameW;

    DrawRectRotaGraph(
        (int)x, (int)y,
        srcX, 0,
        frameW, frameH,
        1.0, 0.0,
        img, TRUE
    );
}

void InitExplosions() {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        gExplosions[i] = new Explosion();
    }
}

void CreateExplosion(float x, float y) {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        if (!gExplosions[i]->active) {
            gExplosions[i]->Start(x, y);
            break;
        }
    }
}

void UpdateExplosions() {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        gExplosions[i]->Update();
    }
}

void DrawExplosions() {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        gExplosions[i]->Draw();
    }
}