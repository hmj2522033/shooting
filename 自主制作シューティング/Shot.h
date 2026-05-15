#pragma once
#include "DxLib.h"

enum ShotType {
    SHOT_BULLET,
    SHOT_FIRE,
    SHOT_SPECIAL
};

class Shot {
public:
    bool active;
    float x, y;
    float vx, vy;
    ShotType type;

    static int imgNormal;
    static int imgFire;
    static int imgSpecial;

    Shot();
    void Update();
    void Draw();
};

extern Shot* gShots[];
const int MAX_SHOTS = 200;

void InitShots();
void FireShotNormal(float x, float y);
void FireShotFire(float x, float y);
void FireShotSpecial(float x, float y);

void UpdateShots();
void DrawShots();