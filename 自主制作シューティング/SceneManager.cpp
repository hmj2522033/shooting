#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

SceneType SceneManager::currentScene = SCENE_TITLE;

void SceneManager::Init() {
    InitTitleScene();
    currentScene = SCENE_TITLE;
}

void SceneManager::ChangeScene(SceneType next) {
    currentScene = next;
}

void SceneManager::Update() {
    switch (currentScene) {
    case SCENE_TITLE:  UpdateTitleScene();  break;
    case SCENE_GAME:   UpdateGameScene();   break;
    case SCENE_RESULT: UpdateResultScene(); break;
    }
}

void SceneManager::Draw() {
    switch (currentScene) {
    case SCENE_TITLE:  DrawTitleScene();  break;
    case SCENE_GAME:   DrawGameScene();   break;
    case SCENE_RESULT: DrawResultScene(); break;
    }
}