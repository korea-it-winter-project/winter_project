#pragma once
#include "pch.h"
class utils {
public:
	static void DrawText(HDC hdc, Vector pos, const WCHAR str[1024]) {
		::TextOut(hdc, (int)pos.x, (int)pos.y, str, lstrlen(str));
	}
	static void DrawRect(HDC hdc, Vector pos, int w, int h) {
		::Rectangle(hdc, (int)(pos.x - w / 2), (int)(pos.y - h / 2), (int)(pos.x + w / 2), (int)(pos.y + h / 2));
	};
	static void DrawCircle(HDC hdc, Vector pos, int r) {
		::Ellipse(hdc, (int)(pos.x - r / 2), (int)(pos.y - r / 2), (int)(pos.x + r / 2), (int)(pos.y + r / 2));
	}
};