#include "DevScene.h"
#include "GameScene.h"
#include "SceneManager.h"


// 초기화
inline void SceneManager::Init(sceneType sc_type) {
    _scene = nullptr;
    _sceneType = sc_type;
}

// 업데이트
inline void SceneManager::UPdate() {
    if (_scene) {
        _scene->UPdate();
    }
}

// 렌더링
inline void SceneManager::Render(HDC hdc) {
    if (_scene) {
        _scene->Render(hdc);
    }
}

// 씬 변경
inline void SceneManager::ChScene(sceneType sc_type) {
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

// 씬 초기화
inline void SceneManager::clear() {
    if (_scene) {
        delete _scene;
        _scene = nullptr;
    }
}
