#pragma once
#include "DxLib.h"

class Background {
public:
    static int img;
    static float scrollY;

    static void Init();
    static void Update();
    static void Draw();
};