#include "GameScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Background.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "Explosion.h"
#include "HPUI.h"
#include "EnemyGenerator.h"
#include "AbsorbSystem.h"
#include "StockUI.h"
#include "Timer.h"
#include "Boss.h"
#include "SceneManager.h"
#include "ResultScene.h"

static Player player;

static int shotCooldown = 0;
static int oldKeySpace = 0;
static int oldKey1 = 0;
static int oldKey2 = 0;
static int oldKey3 = 0;
static int stageTimer = 0;
static int bgmGame = -1;



void UpdateInputGame(Player& player) {

    // --- 通常ショット ---
    if (shotCooldown > 0) shotCooldown--;

    int nowKeySpace = CheckHitKey(KEY_INPUT_SPACE);

    if (shotCooldown == 0) {
        if (nowKeySpace && !oldKeySpace) {
            FireShotNormal(player.x, player.y - 12);
            shotCooldown = 30;
        }
    }

    oldKeySpace = nowKeySpace;

    // --- 吸収 ---
    int keyAbsorb = CheckHitKey(KEY_INPUT_NUMPAD0);
    player.absorbPressed = (keyAbsorb);

    // --- 火の玉 ---
    int nowKey1 = CheckHitKey(KEY_INPUT_NUMPAD1);
    if (nowKey1 && !oldKey1) AbsorbSystem::UseFire(player);
    oldKey1 = nowKey1;

    // --- 特殊弾 ---
    int nowKey2 = CheckHitKey(KEY_INPUT_NUMPAD2);
    if (nowKey2 && !oldKey2) AbsorbSystem::UseSpecial(player);
    oldKey2 = nowKey2;

    // --- バリア ---
    int nowKey3 = CheckHitKey(KEY_INPUT_NUMPAD3);
    if (nowKey3 && !oldKey3) AbsorbSystem::UseBarrier();
    oldKey3 = nowKey3;
}

void InitGameScene() {

    if (bgmGame == -1) {
        bgmGame = LoadSoundMem("Resource/bgm.mp3");
    }
    PlaySoundMem(bgmGame, DX_PLAYTYPE_LOOP);


    Background::Init();
    player = Player();

    InitShots();
    InitEnemies();
    InitEnemyShots();
    InitExplosions();
    InitHPUI();
    InitStockUI();
    EnemyGenerator::Init();
    AbsorbSystem::Init();
    InitBossTimer();
    gBoss.active = false;
    gBoss.dead = false;
    gBoss.deathTimer = 0;



    shotCooldown = 0;
    oldKeySpace = oldKey1 = oldKey2 = oldKey3 = 0;
    stageTimer = 0;
}

void UpdateGameScene() {

    UpdateInputGame(player);

    Background::Update();
    player.Update();
    AbsorbSystem::Update(player.absorbPressed);

    UpdateShots();
    UpdateEnemies();
    EnemyGenerator::Update();
    UpdateEnemyShots();
    UpdateExplosions();

    player.CheckHit();
    CheckHitEnemies();
    AbsorbSystem::CheckHit(player.x, player.y, player.hp);
    // ★ プレイヤー弾 → ボス
    for (int i = 0; i < MAX_SHOTS; i++) {

        // ★ active でない弾は無視
        if (!gShots[i]->active) continue;

        if (gBoss.active && gBoss.CheckHit(gShots[i]->x, gShots[i]->y)) {

            switch (gShots[i]->type) {

            case SHOT_BULLET:
                gBoss.hp -= 1;
                break;

            case SHOT_SPECIAL:
                gBoss.hp -= 2;
                break;

            case SHOT_FIRE:
                gBoss.hp -= 3;
                break;

            default:
                gBoss.hp -= 1;
                break;
            }

            gShots[i]->active = false;
        }
    }

    // ★ プレイヤー本体 → ボス
    if (gBoss.active && gBoss.CheckHit(player.x, player.y)) {
        player.hp -= 1;   // ここはあなたのダメージ処理に合わせて変更
    }

    UpdateBossTimer();
    EnemyGenerator::Update();

    // ★ active でも dead でも Update() を呼ぶ
    if (gBoss.active || gBoss.dead) {
        gBoss.Update();
    }

    // ★ 爆発後の遷移
    if (gBoss.dead && gBoss.deathTimer <= 0) {
        StopSoundMem(bgmGame);
        SetResult(true, 0);
        SceneManager::ChangeScene(SCENE_RESULT);
        return;
    }




    if (player.hp <= 0) {
        StopSoundMem(bgmGame);
        int timeLeft = GetBossRemainSec();   // ボスまでの残り秒数
        SetResult(false, timeLeft);
        SceneManager::ChangeScene(SCENE_RESULT);
        return;
    }

    //if (CheckHitKey(KEY_INPUT_0))
    //{
    //    SceneManager::ChangeScene(SCENE_TITLE);
    //}
}

void DrawGameScene() {

    Background::Draw();

    AbsorbSystem::DrawAnimation(player.x, player.y);
    AbsorbSystem::DrawBarrier(player.x, player.y);

    player.Draw();
    DrawShots();
    DrawEnemies();
    DrawEnemyShots();
    DrawExplosions();

    DrawHPUI(player.hp);
    DrawStockUI();
    AbsorbSystem::DrawUI();
    DrawBossTimerUI();   // Timer.cpp の UI 関数

    if (gBoss.active) {
        gBoss.Draw();
    }
}