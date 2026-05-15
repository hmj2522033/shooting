#pragma once

enum SceneType {
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT
};

class SceneManager {
public:
    static void Init();
    static void Update();
    static void Draw();
    static void ChangeScene(SceneType next);

private:
    static SceneType currentScene;
};