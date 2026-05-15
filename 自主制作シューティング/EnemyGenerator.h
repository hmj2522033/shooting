#pragma once

class EnemyGenerator {
public:
    static int timer;

    static void Init();
    static void Update();

    static void TrySpawnBoss();   // ★ 追加：ボス出現処理
};