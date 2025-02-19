#pragma once
#include "Object.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "utils.h"
#include "Collider.h"
#include "pch.h"
#include "ResourceManager.h"
#include <string>

static class TextObject : public Object {
public:
    TextObject() : Object(ObjectType::Ui) {
        isShow = true;
        textRect = { 0, 0, 200, 50 }; // 기본 위치와 크기 설정
        wcsncpy_s(str, L"", 1024); // 문자열 초기화
    }

    virtual ~TextObject() {}

    // UI 오브젝트 초기화
    virtual void Init() override {
        isShow = true; // UI 요소 표시 여부
    }

    // 업데이트 (현재는 필요 없음)
    virtual void Update(float dTime) override {}

    // 렌더링: UI 오브젝트 그리기
    virtual void Render(HDC hdc) override {
        if (!isShow) return;

        HPEN pen, oldPen;
        pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
        oldPen = (HPEN)SelectObject(hdc, pen);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0));

        DrawText(hdc, str, -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        SetBkMode(hdc, OPAQUE);
        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }

    // 텍스트 설정
    void showText(const wchar_t* text, int num) {
        swprintf_s(str, L"%s%d", text, num); 
		//printf("%s\n", text);
    }

    // 위치 및 크기 설정
    void SetRECT(RECT _rect) {
        textRect = _rect;
    }

private:
    bool isShow;      // UI 오브젝트 표시 여부
    RECT textRect;    // 텍스트의 위치와 크기
    wchar_t str[1024]; // 텍스트 저장 버퍼
};
