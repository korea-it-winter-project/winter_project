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
        // hBitmap과 sharedMemDC 해제
        if (hBitmap) {
            DeleteObject(hBitmap);
        }

        // hBitmapCache에 저장된 비트맵들 해제
        for (auto& pair : hBitmapCache) {
            if (pair.second) {
                DeleteObject(pair.second);
            }
        }

        // sharedMemDC 해제
        if (sharedMemDC) {
            DeleteDC(sharedMemDC);
        }
    }

    // UI 오브젝트 초기화
    virtual void Init() override {
        isShow = true; // UI 요소 표시 여부
    }

    // 업데이트: UI 요소의 동작을 처리
    virtual void Update(float dTime) override {
        if (hBitmapCache.find(bitmap_name) == hBitmapCache.end()) {
            // 비트맵이 캐시되지 않았으면 새로운 비트맵을 캐시하고, hBitmap에 저장
            HBITMAP newBitmap = ConvertToHBITMAP(pBmp); // 예시: 이미지를 비트맵으로 변환
            hBitmapCache[bitmap_name] = newBitmap;
            hBitmap = newBitmap;

            // 비트맵 크기 업데이트
            BITMAP bmp;
            GetObject(hBitmap, sizeof(BITMAP), &bmp);
            width = bmp.bmWidth;
            height = bmp.bmHeight;
        }
       
    }

    // 렌더링: UI 오브젝트 그리기
    virtual void Render(HDC hdc) override {
        if (!isShow || !hBitmap) return;

        if (!sharedMemDC) {
            sharedMemDC = CreateCompatibleDC(hdc); // 메모리 DC는 한번만 생성
        }

        HBITMAP oldBitmap = (HBITMAP)SelectObject(sharedMemDC, hBitmap);

        // StretchBlt를 사용하여 UI 이미지를 그리기
        if(isA == false)
            StretchBlt(hdc, _pos.x, _pos.y, _size.x, _size.y,
                sharedMemDC, 0, 0, width, height, SRCCOPY);
        else {
            Gdiplus::Graphics graphics(hdc);
            GET_SINGLE(ResourceManager)->DrawImage(graphics,pBmp,_pos.x, _pos.y, _size.x,_size.y);
        }

        SelectObject(sharedMemDC, oldBitmap);
    }


    // UI 오브젝트의 이름 설정
    void setName(std::wstring _name) {
        bitmap_name = _name;
    }

    // UI 오브젝트의 표시 여부 설정
    void IsShow(bool _isShow) {
        isShow = _isShow;
    }

    // 클릭 시 실행할 메서드




    bool isA;

private:
    bool isShow;             // UI 오브젝트 표시 여부
    float width, height;     // 비트맵 크기
    HDC sharedMemDC;         // 공유 메모리 DC
    HBITMAP hBitmap;         // UI 오브젝트의 비트맵
    std::unordered_map<std::wstring, HBITMAP> hBitmapCache;  // 비트맵 캐시
    std::wstring bitmap_name; // 비트맵 이름
};
