#pragma once
#include "pch.h"
#include "sceneManager.h"

class BackScene {
	DECLARE_SINGLE(BackScene);
private:
	bool isActive_;
	RECT rect;
	RECT s_ArrowRect;
	RECT b_ArrowRect;
	RECT backRect;
public:
	void Init() {
		isActive_ = false;
	}
	void Update(RECT _rect) {
		rect = _rect;
		s_ArrowRect = { rect.left - 5, rect.top + 10, rect.left +20, rect.top + 50 };
		backRect = { rect.left - 1, s_ArrowRect.top, rect.left + 70, s_ArrowRect.bottom };
		b_ArrowRect = { backRect.right - 5, backRect.top, backRect.right + 20, backRect.bottom };

		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) {
			if (!isActive_) {
				if (GET_SINGLE(InputManager)->CheckMousePoint(s_ArrowRect)) {
					isActive_ = !isActive_;
				}
			}
			if (isActive_) {
				if (GET_SINGLE(InputManager)->CheckMousePoint(b_ArrowRect)) {
					isActive_ = !isActive_;
				}
				if (GET_SINGLE(InputManager)->CheckMousePoint(backRect)) {
				}
			}
		}
	}
	void Render(HDC hdc) {
		if (!isActive_) {
			RoundRect(hdc, s_ArrowRect.left, s_ArrowRect.top, s_ArrowRect.right, s_ArrowRect.bottom, 10, 10);
			SetBkMode(hdc, TRANSPARENT);
			wchar_t s_Arrow[100];
			swprintf(s_Arrow, 100, L" ->");
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, s_Arrow, -1, &s_ArrowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SetBkMode(hdc, OPAQUE);
		}
		if (isActive_) {
			RoundRect(hdc, b_ArrowRect.left, b_ArrowRect.top, b_ArrowRect.right, b_ArrowRect.bottom, 10, 10);
			Rectangle(hdc, backRect.left, backRect.top, backRect.right, backRect.bottom);
			SetBkMode(hdc, TRANSPARENT);
			wchar_t b_Arrow[100];
			swprintf(b_Arrow, 100, L" <-");
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, b_Arrow, -1, &b_ArrowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t back[100];
			swprintf(back, 100, L"BACK");
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, back, -1, &backRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SetBkMode(hdc, OPAQUE);
		}
	}
};