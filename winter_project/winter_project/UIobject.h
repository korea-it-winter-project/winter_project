#pragma once
#include "Object.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "utils.h"
#include "Collider.h"
#include "pch.h"
#include "ResourceManager.h"


static class UiObject : public Object {
public:
    UiObject() : Object(ObjectType::Ui), hBitmap(nullptr), sharedMemDC(nullptr), isShow(true), width(0), height(0) {}

    virtual ~UiObject() {
        // hBitmap�� sharedMemDC ����
        if (hBitmap) {
            DeleteObject(hBitmap);
        }

        // hBitmapCache�� ����� ��Ʈ�ʵ� ����
        for (auto& pair : hBitmapCache) {
            if (pair.second) {
                DeleteObject(pair.second);
            }
        }

        // sharedMemDC ����
        if (sharedMemDC) {
            DeleteDC(sharedMemDC);
        }
    }

    // UI ������Ʈ �ʱ�ȭ
    virtual void Init() override {
        isShow = true; // UI ��� ǥ�� ����
    }

    // ������Ʈ: UI ����� ������ ó��
    virtual void Update(float dTime) override {
        if (hBitmapCache.find(bitmap_name) == hBitmapCache.end()) {
            // ��Ʈ���� ĳ�õ��� �ʾ����� ���ο� ��Ʈ���� ĳ���ϰ�, hBitmap�� ����
            HBITMAP newBitmap = ConvertToHBITMAP(pBmp); // ����: �̹����� ��Ʈ������ ��ȯ
            hBitmapCache[bitmap_name] = newBitmap;
            hBitmap = newBitmap;

            // ��Ʈ�� ũ�� ������Ʈ
            BITMAP bmp;
            GetObject(hBitmap, sizeof(BITMAP), &bmp);
            width = bmp.bmWidth;
            height = bmp.bmHeight;
        }
       
    }

    // ������: UI ������Ʈ �׸���
    virtual void Render(HDC hdc) override {
        if (!isShow || !hBitmap) return;

        if (!sharedMemDC) {
            sharedMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �ѹ��� ����
        }

        HBITMAP oldBitmap = (HBITMAP)SelectObject(sharedMemDC, hBitmap);

        // StretchBlt�� ����Ͽ� UI �̹����� �׸���
        if(isA == false)
            StretchBlt(hdc, _pos.x, _pos.y, _size.x, _size.y,
                sharedMemDC, 0, 0, width, height, SRCCOPY);
        else {
            Gdiplus::Graphics graphics(hdc);
            GET_SINGLE(ResourceManager)->DrawImage(graphics,pBmp,_pos.x, _pos.y, _size.x,_size.y);
        }

        SelectObject(sharedMemDC, oldBitmap);
    }


    // UI ������Ʈ�� �̸� ����
    void setName(std::wstring _name) {
        bitmap_name = _name;
    }

    // UI ������Ʈ�� ǥ�� ���� ����
    void IsShow(bool _isShow) {
        isShow = _isShow;
    }

    // Ŭ�� �� ������ �޼���




    bool isA;

private:
    bool isShow;             // UI ������Ʈ ǥ�� ����
    float width, height;     // ��Ʈ�� ũ��
    HDC sharedMemDC;         // ���� �޸� DC
    HBITMAP hBitmap;         // UI ������Ʈ�� ��Ʈ��
    std::unordered_map<std::wstring, HBITMAP> hBitmapCache;  // ��Ʈ�� ĳ��
    std::wstring bitmap_name; // ��Ʈ�� �̸�
};
