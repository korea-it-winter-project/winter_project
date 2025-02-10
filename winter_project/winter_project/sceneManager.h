#pragma once
//#include "pch.h"
//#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "Leveleditor.h"
#include "StartScene.h"
#include "UiScene.h"
#include "BackScene.h"


enum class sceneType {
    DevScene  = 0 ,
    GameScene,
    Leveleditor,
    StartScene,
    UiScene,
    none
};

class SceneManager {
private:
    class Scene* _scene = nullptr;
    sceneType _sceneType = sceneType::none;
    sceneType _lastSceneType = sceneType::none;
    DECLARE_SINGLE(SceneManager);
public:
    void Init() {

    };  // ����
    void Update() {  // ���⼭�� �Լ� �̸� Ȯ��
        if (_scene) {
            _scene->Update();
        }
    };  // ����
    void Render(HDC hdc) {
        if (_scene) {
            _scene->Render(hdc);
        }
    };  // ����
    sceneType GetNowScene() {
        return _sceneType;
    }

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
        case sceneType::Leveleditor:
            newScene = new Leveleditor();
            break;
        case sceneType::StartScene:
            newScene = new StartScene();
            break;
        case sceneType::UiScene:
            newScene = new UiScene();
            break;
        }

        if (_scene) {
            delete _scene;
            _scene = nullptr;
        }

        _lastSceneType = _sceneType;

        _scene = newScene;
        _sceneType = sc_type;

        newScene->Init();
    };  // ����
};

