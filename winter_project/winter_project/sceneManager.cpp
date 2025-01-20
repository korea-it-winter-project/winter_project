#include "sceneManager.h"
#include "DevScene.h"
#include "GameScene.h"

// 초기화
void SceneManager::Init(sceneType sc_type) {
    _scene = nullptr;
    _sceneType = sc_type;
}

void SceneManager::Update() {  // 여기서도 함수 이름 확인
    if (_scene) {
        _scene->Update();
    }
}

void SceneManager::Render(HDC hdc) {
    if (_scene) {
        _scene->Render(hdc);
    }
}

void SceneManager::ChScene(sceneType sc_type) {
    if (_sceneType == sc_type) return;

    Scene* newScene = nullptr;

    switch (sc_type) {
    case sceneType::DevScene:
        newScene = new DevScene();
        break;
    case sceneType::GameScene:
        newScene = new GameScene();
        break;
    }

    clear();
    _scene = newScene;
    _sceneType = sc_type;

    if (_scene) {
        _scene->Init();
    }
}

void SceneManager::clear() {
    if (_scene) {
        delete _scene;
        _scene = nullptr;
    }
}

