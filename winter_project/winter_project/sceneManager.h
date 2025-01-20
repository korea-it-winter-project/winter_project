#pragma once
#include "pch.h"
#include "Scene.h"


enum class sceneType {
    DevScene,
    GameScene
};

class SceneManager {
    DECLARE_SINGLE(SceneManager);
public:
    //SceneManager() {}
    //~SceneManager() { clear(); }
    Scene* _scene;
    sceneType _sceneType;

    void Init(sceneType sc_type);  // ����
    void Update();  // ����
    void Render(HDC hdc);  // ����
    void clear();  // ����
    void ChScene(sceneType sc_type);  // ����

    

};
