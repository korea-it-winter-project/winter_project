#pragma once
#include "pch.h"  // 항상 가장 위에 포함
#include "InputManager.h"
#include "TimeManager.h"
#include "object.h"
#include "utils.h"
#include "ResourceManager.h"
#include "MapData.h"
#include <time.h>
#include <Windows.h>

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
        _stat.speed = 100.f;  // 속도를 적절히 조정
        now = moveInterval;
        nextIndex = pathLength - 1;
        direction = path[pathLength] % MAP_COLS;
        switch (direction) {
        case 1: moveD = { 0,-1 }; break;  // 위
        case 2: moveD = { 1,0 }; break;   // 오른쪽
        case 3: moveD = { 0,1 }; break;   // 아래
        case 4: moveD = { -1,0 }; break;  // 왼쪽
        }
        to = _pos + moveD * 24;
    }

    virtual void Update(float dTime) override {
        if (pathLength <= 0) return;
        if (_stat.Hp <= 0) {
            GET_SINGLE(ObjectManager)->Remove(this);
            return;
        }
        if (!((int)movePos.x + (int)movePos.y)) {
            direction = path[pathLength] % MAP_COLS;
            switch (direction) {
            case 1: moveD = { 0,-1 }; break;  // 위
            case 2: moveD = { 1,0 }; break;   // 오른쪽
            case 3: moveD = { 0,1 }; break;   // 아래
            case 4: moveD = { -1,0}; break;  // 왼쪽
            }
			to = _pos + moveD * 24;
            
        }
        float movementSpeed = _stat.speed * dTime; // 델타타임 기반 이동 속도 조절


        // 목표 지점에 도달했는지 확인
        

        if (0) {
            //printf("speed : %f\n", movementSpeed);
            //_pos = to;  // 정확한 목표 지점으로 설정
            pathLength--;
        }
        else {
			_pos += moveD * movementSpeed;  // 이동
        }
        movePos = _pos - to;

        printf(" D    : %d\n", direction);
        printf(" now  : %d %d\n", (int)_pos.x, (int)_pos.y);
        printf(" t o  : %d %d\n", (int)to.x, (int)to.y);
		printf(" MoP  : %d %d\n", (int)fabs(movePos.x), (int)fabs(movePos.y));
        printf(" MoD  : %d %d\n==========\n", (int)moveD.x, (int)moveD.y);
        //Sleep(200);
    }
    virtual void Render(HDC hdc) override {
        Gdiplus::Graphics graphics(hdc);

        spriteDelay -= GET_SINGLE(TimeManager)->GetDeltaTime();
        if (spriteDelay <= 0) {
            num = (num < 2) ? num + 1 : 1;
            spriteDelay = 0.2f;
        }

        std::wstring fullFileName = L"monster_Slime_" + std::to_wstring(num) + L".png";
        GET_SINGLE(ResourceManager)->DrawRotatedImage(graphics,
            GET_SINGLE(ResourceManager)->FindImage(fullFileName), _pos.x, _pos.y, angle);
    }

private:
    int num; // 파일에 들어가는 넘버
    float angle;
    float spriteDelay;

    utils ut;
    int path[500];
    int sdir1[5] = { 0,-MC,1,MC,-1 }; // 앞 오른 뒤 왼

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
    Vector moveD = {0,0};
    Vector movePos = { 0,0 };
};
