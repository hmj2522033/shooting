#include "Background.h"

int Background::img = -1;
float Background::scrollY = 0.0f;

void Background::Init() {
    if (img == -1) {
        img = LoadGraph("Resource/background.png");
    }
}

void Background::Update() {
    scrollY += 2.0f;   // スクロール速度

    // 1440 は背景画像の高さ
    if (scrollY >= 1440) {
        scrollY -= 1440;
    }
}

void Background::Draw() {
    // 1枚目
    DrawGraph(0, (int)scrollY, img, TRUE);

    // 2枚目（ループ用）
    DrawGraph(0, (int)scrollY - 1440, img, TRUE);
}                                                                       