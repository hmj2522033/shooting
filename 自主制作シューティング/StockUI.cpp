#include "StockUI.h"
#include "DxLib.h"
#include "AbsorbSystem.h"

static int imgRed = -1;
static int imgBlue = -1;
static int imgBarrier = -1;
static int imgNum = -1;

static const int NUM_W = 53;
static const int NUM_H = 54;

void InitStockUI() {

    imgRed = LoadGraph("Resource/red_icon.png");
    imgBlue = LoadGraph("Resource/blue_icon.png");
    imgBarrier = LoadGraph("Resource/barrier_icon.png");

    imgNum = LoadGraph("Resource/NumFont.png");
}

// font描画
void DrawNumber(int x, int y, int num) {

    char buf[16];
    sprintf_s(buf, "%d", num);

    int mapIndex[10] = {
        9,0,1,2,3,4,5,6,7,8
    };

    const int DIGIT_SPACING = 30;
    // ★ ここを調整する（例：25?wyyywaas35）
    //    NUM_W=53 より小さくすることで間隔が詰まる

    for (int i = 0; buf[i] != '\0'; i++) {

        int digit = buf[i] - '0';
        int idx = mapIndex[digit];

        int sx = (idx % 5) * NUM_W;
        int sy = (idx / 5) * NUM_H;

        DrawRectGraph(
            x + i * DIGIT_SPACING,  // ★ ここがポイント
            y,
            sx, sy,
            NUM_W, NUM_H,
            imgNum,
            TRUE
        );
    }
}

void DrawStockUI() {

    int baseX = 860;
    int baseY = 200;

    // 赤弾ストック
    DrawGraph(baseX, baseY, imgRed, TRUE);
    DrawNumber(baseX + 40, baseY + 10, AbsorbSystem::fireStock);

    // 青弾ストック
    DrawGraph(baseX, baseY + 70, imgBlue, TRUE);
    DrawNumber(baseX + 40, baseY + 80, AbsorbSystem::specialStock);

    // バリアストック
    DrawGraph(baseX, baseY + 140, imgBarrier, TRUE);
    DrawNumber(baseX + 40, baseY + 150, AbsorbSystem::hasBarrier ? 1 : 0);
}