#pragma once
#include "Scene.h"

class DevScene : public Scene {
public:
    DevScene(); // 기본 생성자
    virtual ~DevScene() override; // 기본 소멸자

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
private:
    class Player* _player = nullptr;
};
