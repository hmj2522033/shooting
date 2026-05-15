#include "EnemyBullet.h"
#include "DxLib.h"

void EnemyBullet::Spawn(float x, float y, float vx, float vy, BulletColor c) {
    pos = { x, y };
    vel = { vx, vy };
    color = c;
    alive = true;
}

void EnemyBullet::Update() {
    if (!alive) return;
    pos.x += vel.x;
    pos.y += vel.y;
    if (pos.y > 620) alive = false;
}

void EnemyBullet::Draw() {
    if (!alive) return;

    int col = GetColor(255, 255, 255);
    switch (color) {
    case BulletColor::Red:    col = GetColor(255, 0, 0); break;
    case BulletColor::Blue:   col = GetColor(0, 128, 255); break;
    case BulletColor::Green:  col = GetColor(0, 255, 0); break;
    case BulletColor::Purple: col = GetColor(200, 0, 200); break;
    default: break;
    }

    DrawCircle((int)pos.x, (int)pos.y, 6, col, TRUE);
}