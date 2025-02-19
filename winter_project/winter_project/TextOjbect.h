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
        textRect = { 0, 0, 200, 50 }; // �⺻ ��ġ�� ũ�� ����
        wcsncpy_s(str, L"", 1024); // ���ڿ� �ʱ�ȭ
    }

    virtual ~TextObject() {}

    // UI ������Ʈ �ʱ�ȭ
    virtual void Init() override {
        isShow = true; // UI ��� ǥ�� ����
    }

    // ������Ʈ (����� �ʿ� ����)
    virtual void Update(float dTime) override {}

    // ������: UI ������Ʈ �׸���
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

    // �ؽ�Ʈ ����
    void showText(const wchar_t* text, int num) {
        swprintf_s(str, L"%s%d", text, num); 
		//printf("%s\n", text);
    }

    // ��ġ �� ũ�� ����
    void SetRECT(RECT _rect) {
        textRect = _rect;
    }

private:
    bool isShow;      // UI ������Ʈ ǥ�� ����
    RECT textRect;    // �ؽ�Ʈ�� ��ġ�� ũ��
    wchar_t str[1024]; // �ؽ�Ʈ ���� ����
};
