#pragma once
#include "DxLib.h"

enum EnemyType {
    ENEMY_A,
    ENEMY_B,
    ENEMY_C,
    ENEMY_D,
    ENEMY_E
};

class Enemy {
public:
    bool active;
    EnemyType type;

    float x, y;
    float vx, vy;
    float hitR;   // “–‚½‚è”»’è”¼Œa

    int hp;
    int shotTimer;

    static int imgA;
    static int imgB;
    static int imgC;
    static int imgD;
    static int imgE;

    Enemy();
    void Spawn(EnemyType t, float px, float py);
    void Update();
    void Draw();
};

const int MAX_ENEMIES = 128;
extern Enemy* gEnemies[MAX_ENEMIES];

void InitEnemies();
void SpawnEnemy(EnemyType t, float x, float y);
void UpdateEnemies();
void DrawEnemies();
void CheckHitEnemies();