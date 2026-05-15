#pragma once
#include "DxLib.h"

class Player;

class AbsorbSystem {
public:
    static void Init();
    static void Update(bool absorbPressed);
    static void CheckHit(float px, float py, int& hp);

    static void UseFire(const Player& player);
    static void UseSpecial(const Player& player);
    static void UseBarrier();

    static void DrawUI();
    static void DrawAnimation(float px, float py);
    static void DrawBarrier(float px, float py);

    static int absorbGauge;
    static bool absorbMode;
    static int absorbTimer;

    static int fireStock;
    static int specialStock;
    static bool hasBarrier;

    static int barrierTimer;

private:
    static int gaugeImg[6];
    static int animImg;
    static int animFrame;
    static int animTimer;

    static int barrierImg;
};