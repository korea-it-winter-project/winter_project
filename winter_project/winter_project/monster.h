#pragma once
#include "pch.h"  // 항상 가장 위에 포함
#include "InputManager.h"
#include "TimeManager.h"
#include "object.h"
#include "utils.h"

class Monster : public Object {
public:
    Monster() : Object(ObjectType::Monster) {

    };
    virtual ~Monster() {

    };

    virtual void Init() override {
        _stat.Hp = 100;
        _stat.MaxHP = 100;
        _stat.speed = 100;
    };
    virtual void Update() override {

    };
    virtual void Render(HDC hdc) override {
        ut.DrawCircle(hdc, _pos, 50);
    };

public:
    utils ut;
};

