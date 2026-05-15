#pragma once
#include "DxLib.h"

const int MAX_EXPLOSIONS = 64;

class Explosion {
public:
    bool active;
    float x, y;

    int frame;
    int counter;

    Explosion();
    void Start(float px, float py);
    void Update();
    void Draw();

    static int img;
    static void LoadImage();   // Åö í«â¡
};

void InitExplosions();
void CreateExplosion(float x, float y);
void UpdateExplosions();
void DrawExplosions();