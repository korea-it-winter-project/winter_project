#pragma once
#include "pch.h"  // �׻� ���� ���� ����
#include "InputManager.h"
#include "TimeManager.h"
#include "object.h"
#include "utils.h"
#include "ResourceManager.h"
#include "MapData.h"
#include <time.h>

#define MR 10
#define MC 10

class Monster : public Object {
public:
    Monster(int* path, int pathLength)
        : Object(ObjectType::Monster)
        , num(1)
        , spriteDelay(0.5f)
        , currentPathIndex(0)
        , pathLength(pathLength)
        , lastMoveTime(0)
        , now(0)
        , direction{}
        , moveAmount(24)
        , moveInterval(1.f) {
        for (int i = pathLength; i > 0; i--) {
            this->path[i] = path[i];
        }
    }

    virtual ~Monster() {}

    virtual void Init() override {
        _stat.Hp = 100;
        _stat.MaxHP = 100;
        _stat.speed = 10.f;  // �ӵ��� ������ ����
        now = moveInterval;
        nextIndex = pathLength - 1;

        // �ʱ� ��ǥ ���� ����
        if (nextIndex >= 0) {
            SetNextTarget();
        }
    }

    virtual void Update(float dTime) override {
        if (pathLength <= 0) return;
        if (_stat.Hp <= 0) {
            GET_SINGLE(ObjectManager)->Remove(this);
            return;
        }

        float movementSpeed = _stat.speed * dTime; // ��ŸŸ�� ��� �̵� �ӵ� ����

        // ��ǥ ������ �����ߴ��� Ȯ��
        float fx = fabsf(to.x - _pos.x);
        float fy = fabsf(to.y - _pos.y);

        if (fx < 0.1f && fy < 0.1f) {
            _pos = to;  // ��Ȯ�� ��ǥ �������� ����
            if (nextIndex > 0) {
                nextIndex--;  // ���� ��η� �̵�
                SetNextTarget(); // ���ο� ��ǥ ����
            }
        }
        else {
            _pos.x += x * movementSpeed;
            _pos.y += y * movementSpeed;
        }
    }


    // 
    void SetNextTarget() {
        if (nextIndex < 0) return;

        direction = path[nextIndex] % MAP_COLS;
        x = y = 0;  // �̵��� �ʱ�ȭ
        step = 24;  // �̵��� �Ÿ� ����
        to = _pos;  // ���� ��ġ ������� ��ǥ ���� ����

        // ���⿡ ���� ��ǥ ���� ���� �� �̵� �ӵ� ����
        switch (direction) {
        case 1: to.y -= step; y = -_stat.speed; break;  // ��
        case 2: to.x += step; x = _stat.speed; break;   // ������
        case 3: to.y += step; y = _stat.speed; break;   // �Ʒ�
        case 4: to.x -= step; x = -_stat.speed; break;  // ����
        }
        printf("%d \n", direction);
    }


    virtual void Render(HDC hdc) override {
        Gdiplus::Graphics graphics(hdc);

        spriteDelay -= GET_SINGLE(TimeManager)->GetDeltaTime();
        if (spriteDelay <= 0) {
            num = (num < 2) ? num + 1 : 1;
            spriteDelay = 0.5f;
        }

        std::wstring fullFileName = L"monster_Slime_" + std::to_wstring(num) + L".png";
        GET_SINGLE(ResourceManager)->DrawRotatedImage(graphics,
            GET_SINGLE(ResourceManager)->FindImage(fullFileName), _pos.x, _pos.y, angle);
    }

private:
    int num; // ���Ͽ� ���� �ѹ�
    float angle;
    float spriteDelay;

    utils ut;
    int path[500];
    int sdir1[5] = { 0,-MC,1,MC,-1 }; // �� ���� �� ��

    int pathLength;
    int nextIndex;
    int currentPathIndex;
    int direction;

    float lastMoveTime;
    int moveAmount;
    float now;
    float step;
    float moveInterval;
    float x, y;
    Vector to;
};
