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

    void Init(sceneType sc_type);  // 識情
    void Update();  // 識情
    void Render(HDC hdc);  // 識情
    void clear();  // 識情
    void ChScene(sceneType sc_type);  // 識情

    

};
