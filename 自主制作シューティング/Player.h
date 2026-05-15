#pragma once

class Player {
public:
    float x, y;
    int hp;

    bool invincible;
    int invincibleTimer;

    bool absorbPressed; // ‹zûƒ{ƒ^ƒ“ó‘ÔiAbsorbSystem ‚É“n‚·j

    Player();
    void Update();
    void Draw();
    void CheckHit(); // “G–{‘Ì‚Æ‚ÌÚG”»’è
};