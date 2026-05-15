#pragma once
#include "Player.h"
#include "EnemyBullet.h"

class Game {
public:
    void Init();
    bool Update();
    void Draw();

private:
    Player player;
    EnemyBullet enemyBullets[256];

    void SpawnEnemyBullet();
    void UpdateEnemyBullets();
    void CheckAbsorb();
    void CheckPlayerHit();
};