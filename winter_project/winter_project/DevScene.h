#pragma once
#include "Scene.h"

class DevScene : public Scene {
public:
    //DevScene() = default; // 기본 생성자
    //~DevScene() = default; // 기본 소멸자

    void Init() override;
    void Update() override;
    void Render(HDC hdc) override;
};
