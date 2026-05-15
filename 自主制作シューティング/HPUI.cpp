#include "HPUI.h"
#include "DxLib.h"

static int hpFullImg = -1;
static int hpEmptyImg = -1;

void InitHPUI() {
    hpFullImg = LoadGraph("Resource/hp_full.png");   // Ç†ÇË
    hpEmptyImg = LoadGraph("Resource/hp_empty.png");  // Ç»Çµ
}

void DrawHPUI(int hp) {
    int baseX = 20;      // ç∂Ç©ÇÁ20px
    int baseY = 10;  // âÊñ è„Ç©ÇÁ20pxè„

    for (int i = 0; i < 3; i++) {
        int x = baseX + i * 90;
        int y = baseY;

        if (i < hp) {
            DrawGraph(x, y, hpFullImg, TRUE);
        }
        else {
            DrawGraph(x, y, hpEmptyImg, TRUE);
        }
    }
}