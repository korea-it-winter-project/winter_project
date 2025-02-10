#pragma once
#include "object.h"
#include "Leveleditor.h"
#include <fstream> // ofstream, ifstream µî
#include "ResourceManager.h"
#include "ToolUi.h"

class Tile:public Object
{

public:
	Tile() :Object( ObjectType::Block ){
		
	};
	virtual ~Tile() {

	};

	virtual void Init() override {
		
	};
	virtual void Update() override {
		std::wstring baseName = L"";
		switch (GET_SINGLE(MapData)->GetTile(_pos.x, _pos.y)) {
		case -9: baseName = L"dirt_"; break;  // Èë(º®)
		case 2: baseName = L"stone_"; break; // µ¹(±æ)
		default: break;
		}

		int autoIndex = GET_SINGLE(MapData)->GetAutoTileIndex(_pos.x, _pos.y);
		std::wstring fullFileName = baseName + std::to_wstring(autoIndex) + L".png";

		std::shared_ptr<Gdiplus::Bitmap> pBmp = GET_SINGLE(ResourceManager)->FindImage(fullFileName);
		SetBmp(pBmp);
	};
	virtual void Render( HDC hdc ) {
		Gdiplus::Graphics graphics(hdc);
		if (pBmp) {
			graphics.DrawImage(pBmp.get(),
				static_cast<int>(_pos.x * (int)_size.x),
				static_cast<int>(_pos.y * (int)_size.x),
				static_cast<int>(_rect.left + (int)_size.x),
				static_cast<int>(_rect.top + (int)_size.x));
		}
	};

private:
	RECT _rect;
};

