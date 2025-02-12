#pragma once
#include "object.h"
#include "Leveleditor.h"
#include <fstream> // ofstream, ifstream 등
#include "ResourceManager.h"
#include "ToolUi.h"
//#include "glew.h"

class Tile:public Object
{

public:
	Tile() :Object( ObjectType::Block ){
		
	};
	virtual ~Tile() {

	};
	void SetBaseName(std::wstring _baseName) { baseName = _baseName; }


	virtual void Init() override {
		
	};
	virtual void Update() override {
		
		int autoIndex = GET_SINGLE(MapData)->GetAutoTileIndex(_pos.x, _pos.y);
		std::wstring fullFileName = baseName + std::to_wstring(autoIndex) + L".png";

		pBmp = GET_SINGLE(ResourceManager)->FindImage(fullFileName);
	};
	virtual void Render( HDC hdc ) {
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ConvertToHBITMAP(GetBmp());

		//if (!hBitmap) return; // 변환 실패 시 렌더링 중단

		HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
		BITMAP bmp;

		GetObject(hBitmap, sizeof(BITMAP), &bmp);  // HBITMAP 크기 가져오기
		int width = bmp.bmWidth;
		int height = bmp.bmHeight;
		// BitBlt의 크기 오류 수정
		StretchBlt(hdc, _pos.x* TILE_SIZE, _pos.y* TILE_SIZE, TILE_SIZE, TILE_SIZE,
			memDC, 0, 0, width, height, SRCCOPY);

		// 원래 비트맵으로 복원 후 삭제
		SelectObject(memDC, oldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(memDC);
		
		
		//Gdiplus::Graphics graphics(hdc);
		/*if (pBmp) {
			graphics.DrawImage(pBmp.get(),
				static_cast<int>(_pos.x * (int)_size.x),
				static_cast<int>(_pos.y * (int)_size.x),
				static_cast<int>(_rect.left + (int)_size.x),
				static_cast<int>(_rect.top + (int)_size.x));
		}*/
	};

private:
	std::wstring baseName = L"";
	RECT _rect;
};

