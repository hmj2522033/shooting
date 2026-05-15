#pragma once

void InitBossTimer();      // 初期化
void UpdateBossTimer();    // 毎フレーム更新
int  GetBossRemainSec();   // 残り秒数
bool IsBossTime();         // ボス戦突入判定

void DrawBossTimerUI();