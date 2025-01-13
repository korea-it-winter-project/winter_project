#pragma once
#include "Scene.h"

enum class sceneType {
    None,
    DevScene,
    GameScene,
    EditScene
};

class SceneManager {
    DECLARE_SINGLE(SceneManager);

private:
    Scene* _scene = nullptr;
    sceneType _sceneType = sceneType::None;

public:
    void Init(sceneType sc_type);  // 초기화 함수
    void UPdate();                // 업데이트 함수
    void Render(HDC hdc);         // 렌더링 함수
    void clear();                 // 씬 초기화 함수
    void ChScene(sceneType sc_type); // 씬 변경 함수
};