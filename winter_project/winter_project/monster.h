#pragma once
#include "pch.h"  // 항상 가장 위에 포함
#include "InputManager.h"
#include "TimeManager.h"
#include "object.h"
#include "utils.h"
#define MR 10
#define MC 10

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
        if (_collider) {
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간색 테두리
            HGDIOBJ oldPen = SelectObject(hdc, hPen);
            HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 내부 비우기
            HGDIOBJ oldBrush = SelectObject(hdc, hBrush);
            Rectangle(hdc, _pos.x - _collider->_size.x, _pos.y - _collider->_size.y,
                _pos.x + _collider->_size.x, _pos.y + _collider->_size.y);
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            SelectObject(hdc, oldBrush);
        }
        ut.DrawCircle(hdc, _pos, 50);
    };
    int smt(int n, int* dat) {  // smt는 디코로 다시 설명 함
        int i, j, * p, dir;
        do {
            j = 0;
            for (i = MC; i < (MR - 1) * MC; i++) if (*(dat + i) == n) {
                j++;
                for (dir = 1; dir < 5; dir++) {
                    p = (dat + i) + sdir1[dir];
                    if (!*p)*p = n + 1;
                    else if (*p == 999) {
                        if (!quit) quit = i + sdir1[dir];
                        if (quit && mptr == 0) quit2 = i; // 도착지-1
                        else if (quit && !quit2) quit2 = i + sdir1[dir]; // 도착지-1
                        path[mptr++] = dir;
                        *(dat + i) = 999;
                        return 1;
                    }
                }
            }
        } while (j && smt(n + 1, dat));
        return 0;
    }
public:
    utils ut;
    int path[50], mptr = 0, mptr2 = 0, quit = 0, quit2 = 0;
    int sdir1[5] = { 0,-MC,1,MC,-1 }; // 앞 오른 뒤 왼
};

