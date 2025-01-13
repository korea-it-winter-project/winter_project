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
    void Init(sceneType sc_type);  // �ʱ�ȭ �Լ�
    void UPdate();                // ������Ʈ �Լ�
    void Render(HDC hdc);         // ������ �Լ�
    void clear();                 // �� �ʱ�ȭ �Լ�
    void ChScene(sceneType sc_type); // �� ���� �Լ�
};