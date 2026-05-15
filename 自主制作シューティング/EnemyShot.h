#pragma once
#include "DxLib.h"

enum EnemyShotType {
    SHOT_NORMAL,
    SHOT_RED,
    SHOT_BLUE,
    SHOT_GREEN,
    SHOT_PURPLE
};

class EnemyShot {
public:
    bool active;
    float x, y;
    float vx, vy;
    EnemyShotType type;

    static int imgNormal;
    static int imgRed;
    static int imgBlue;
    static int imgGreen;
    static int imgPurple;

    EnemyShot();
    void Fire(float px, float py, float vx, float vy, EnemyShotType t);
    void Update();
    void Draw();
};

const int MAX_ENEMY_SHOTS = 256;
extern EnemyShot* gEnemyShots[MAX_ENEMY_SHOTS];

void InitEnemyShots();
void CreateEnemyShot(float x, float y, float vx, float vy, EnemyShotType t);
void UpdateEnemyShots();
void DrawEnemyShots();