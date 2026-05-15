#pragma once
#include "DxLib.h"

class Boss {
public:
    static int img;

    float x, y;
    float vx;
    int hp;
    int maxHp;

    int phase;
    int timer;
    int shotTimer;
    int deathTimer;
    bool dead;

    bool active;

    Boss();

    void Init();
    void Update();
    void UpdatePhase1();
    void UpdatePhase2();
    void UpdatePhase3();
    void Draw();
    bool CheckHit(float px, float py);
};

extern Boss gBoss;
