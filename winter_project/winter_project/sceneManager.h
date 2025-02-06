#pragma once
//#include "pch.h"
//#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "Leveleditor.h"
#include "object.h"
//class Oject;

enum class sceneType {
    DevScene,
    GameScene,
    Leveleditor,
    none
};

class SceneManager {
private:
    class Scene* _scene;
    sceneType _sceneType = sceneType::none;
    DECLARE_SINGLE(SceneManager);
public:
    void Init() {

    };  // ����
    void Update() {  // ���⼭�� �Լ� �̸� Ȯ��
        if (_scene) {
            _scene->Update();
        }
    };  // ����
    void Render(HDC hdc,Camera& camera) {
        if (_scene) {
            _scene->Render(hdc);
        }
    };  // ����

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
        }
        

        if (_scene) {
            delete _scene;
            _scene = nullptr;
        }

        _scene = newScene;
        _sceneType = sc_type;

        newScene->Init(nullptr);
    };  // ����
private:
    std::vector<Object*> objects;
};

