#include "EnemyGenerator.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Boss.h"
#include "Timer.h"   // ★ ボス時間を取得するため

int EnemyGenerator::timer = 0;

void EnemyGenerator::Init() {
    timer = 0;
}

void EnemyGenerator::TrySpawnBoss() {

    // ★ ボス時間になったら出現（1回だけ）
    if (IsBossTime() && !gBoss.active && !gBoss.dead) {
        gBoss.Init();
    }
}

void EnemyGenerator::Update() {

    // ★ ボス出現チェック
    TrySpawnBoss();

    // ★ ボスが出現したら雑魚生成を止める
    if (gBoss.active) {
        return;
    }

    timer++;

    // タイプA
    if (timer % 120 == 0) {
        float ex = rand() % 960;
        SpawnEnemy(ENEMY_A, ex, -50);
    }

    // タイプB
    if (timer % 200 == 0) {
        float ex = rand() % 960;
        SpawnEnemy(ENEMY_B, ex, -50);
    }

    // タイプC
    if (timer % 300 == 0) {
        float ex = rand() % 960;
        SpawnEnemy(ENEMY_C, ex, -50);
    }

    // タイプD
    if (timer % 450 == 0) {
        float ex = rand() % 960;
        SpawnEnemy(ENEMY_D, ex, -50);
    }

    // タイプE
    if (timer % 600 == 0) {
        float ex = rand() % 960;
        SpawnEnemy(ENEMY_E, ex, -50);
    }
}