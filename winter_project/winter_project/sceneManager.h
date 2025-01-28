#pragma once
//#include "pch.h"
//#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "Leveleditor.h"


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
    };  // 선언
    void RenderWithCamera(HDC hdc, const Camera& camera) {
        // 모든 게임 오브젝트를 순회하면서, WorldToScreen으로 변환하여 그리기
        //for (auto& object : gameObjects) {
        //    Vector screenPos = camera.WorldToScreen(object.GetPosition());
        //    // 화면 좌표(screenPos)를 이용해 오브젝트를 그리기
        //    object.Render(hdc, screenPos);
        //}
    };
};

