#pragma once
#include "Scene.h"

class DevScene : public Scene {
public:
    //DevScene() = default; // �⺻ ������
    //~DevScene() = default; // �⺻ �Ҹ���

    void Init() override;
    void Update() override;
    void Render(HDC hdc) override;
};
