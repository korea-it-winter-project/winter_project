#pragma once
//#include "pch.h"
//#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"


enum class sceneType {
    DevScene,
    GameScene,
    none
};

class SceneManager {
private:
    class Scene* _scene;
    sceneType _sceneType = sceneType::none;
    DECLARE_SINGLE(SceneManager);
public:
    void Init() {

    };  // 선언
    void Update() {  // 여기서도 함수 이름 확인
        if (_scene) {
            _scene->Update();
        }
    };  // 선언
    void Render(HDC hdc) {
        if (_scene) {
            _scene->Render(hdc);
        }
    };  // 선언

public :
    void ChScene(sceneType sc_type) {
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

        if (_scene) {
            delete _scene;
            _scene = nullptr;
        }

        _scene = newScene;
        _sceneType = sc_type;

        newScene->Init();
    };  // 선언
};

