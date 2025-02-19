#pragma once
#include "object.h"
#include "Leveleditor.h"
#include <fstream> // ofstream, ifstream ��
#include "ResourceManager.h"
#include "ToolUi.h"
//#include "glew.h"

#include <unordered_map>

static class Tile : public Object {
public:
    Tile() : Object(ObjectType::Block), hBitmap(nullptr), width(0), height(0) {}

    virtual ~Tile() {
        if (hBitmap) DeleteObject(hBitmap);
    }

    void SetBaseName(std::wstring _baseName) {
        baseName = _baseName;
    }

    virtual void Update(float dTime){
        //if (time > 0.5f) {
            time = 0;
            int autoIndex = GET_SINGLE(MapData)->GetAutoTileIndex(_pos.x, _pos.y);
            std::wstring fullFileName = baseName + std::to_wstring(autoIndex) + L".png";

            if (hBitmapCache.find(fullFileName) == hBitmapCache.end()) {
                HBITMAP newBitmap = ConvertToHBITMAP(GET_SINGLE(ResourceManager)->FindImage(fullFileName));
                hBitmapCache[fullFileName] = newBitmap;
            }

            hBitmap = hBitmapCache[fullFileName];

            if (hBitmap) {
                BITMAP bmp;
                GetObject(hBitmap, sizeof(BITMAP), &bmp);
                width = bmp.bmWidth;
                height = bmp.bmHeight;
            }
        //}
        //time += GET_SINGLE(TimeManager)->GetDeltaTime();
    }

    virtual void Render(HDC hdc) override {
        if (!hBitmap) return;

        if (!sharedMemDC) {
            sharedMemDC = CreateCompatibleDC(hdc);
        }

        HBITMAP oldBitmap = (HBITMAP)SelectObject(sharedMemDC, hBitmap);

  
            if (width == TILE_SIZE && height == TILE_SIZE) {
                // ũ�Ⱑ ���ٸ� BitBlt ��� (�� ����)
                BitBlt(hdc, _pos.x * TILE_SIZE, _pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, sharedMemDC, 0, 0, SRCCOPY);
            }
            else {
                // ũ�Ⱑ �ٸ��� StretchBlt ���
                StretchBlt(hdc, _pos.x * TILE_SIZE, _pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                    sharedMemDC, 0, 0, width, height, SRCCOPY);
            }
        

        SelectObject(sharedMemDC, oldBitmap);
    }

private:
    std::wstring baseName;
    HBITMAP hBitmap;
    int width, height;
    HDC sharedMemDC;  // ��� Tile�� �����ϴ� DC
    std::unordered_map<std::wstring, HBITMAP> hBitmapCache;  // ��Ʈ�� ĳ��
    float time;
};


