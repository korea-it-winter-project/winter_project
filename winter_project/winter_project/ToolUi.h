#pragma once
#include "pch.h"

class ToolUi {
	DECLARE_SINGLE(ToolUi);
private:
	int slotNum;
	RECT rect;
	RECT toolRect;
	RECT slotOneRect;
	RECT slotTwoRect;
	RECT slotThreeRect;
	RECT slotFourRect;
	RECT slotFiveRect;
	RECT slotSixRect;
	RECT slotSevenRect;
	RECT slotEightRect;
	RECT slotNineRect;
	RECT eraserRect;
	RECT resetRect;
	bool isActive_;
public:
	int GetNum() { return slotNum; }
	RECT GetRect() { return toolRect; }

	void Init() {
		slotNum = 0;
		isActive_ = false;
	}
	void Update(RECT _rect) {
		rect = _rect;
		toolRect = { rect.left + 20, rect.top + 50, rect.left + 240, rect.bottom - 80 }; // ���� �� �׵θ� ��ǥ
		slotOneRect = { toolRect.left + 10, toolRect.top + 10, toolRect.left + 70, toolRect.top + 70 }; // 1�� ���� ��ǥ
		slotTwoRect = { slotOneRect.right + 10, slotOneRect.top, slotOneRect.right + 70, slotOneRect.bottom }; // 2�� ���� ��ǥ
		slotThreeRect = { slotTwoRect.right + 10, slotTwoRect.top, slotTwoRect.right + 70, slotTwoRect.bottom }; // 3�� ���� ��ǥ
		slotFourRect = { slotOneRect.left, slotOneRect.bottom + 10, slotOneRect.right, slotOneRect.bottom + 70 }; // 4�� ���� ��ǥ
		slotFiveRect = { slotTwoRect.left, slotFourRect.top, slotTwoRect.right, slotFourRect.bottom }; // 5�� ���� ��ǥ
		slotSixRect = { slotThreeRect.left, slotFourRect.top, slotThreeRect.right, slotFourRect.bottom }; // 6�� ���� ��ǥ
		slotSevenRect = { slotOneRect.left, slotFourRect.bottom + 10, slotOneRect.right, slotFourRect.bottom + 70 }; // 7�� ���� ��ǥ
		slotEightRect = { slotTwoRect.left, slotSevenRect.top, slotTwoRect.right, slotSevenRect.bottom }; // 8�� ���� ��ǥ
		slotNineRect = { slotThreeRect.left, slotSevenRect.top, slotThreeRect.right, slotSevenRect.bottom }; // 9�� ���� ��ǥ
		eraserRect = { slotSevenRect.left, toolRect.bottom - 70, slotSevenRect.right, toolRect.bottom - 10 }; // ���찳 ���� ��ǥ
		resetRect = { slotNineRect.left, eraserRect.top, slotNineRect.right, eraserRect.bottom }; // �ʱ�ȭ ���� ��ǥ

		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_Ctrl)) isActive_ = !isActive_; // ���� ��Ʈ���� ���� ��
		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) { // ��Ŭ�� �ν�
			if (isActive_) {
				if (GET_SINGLE(InputManager)->CheckMousePoint(slotOneRect)) { // 1�� ������ ���� ��
					slotNum = 1;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotTwoRect)) { // 2�� ������ ���� ��
					slotNum = 2;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotThreeRect)) { // 3�� ������ ���� ��
					slotNum = 3;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotFourRect)) { // 4�� ������ ���� ��
					slotNum = 4;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotFiveRect)) { // 5�� ������ ���� ��
					slotNum = 5;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotSixRect)) { // 6�� ������ ���� ��
					slotNum = 6;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotSevenRect)) { // 7�� ������ ���� ��
					slotNum = 7;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotEightRect)) { // 8�� ������ ���� ��
					slotNum = 8;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(slotNineRect)) { // 9�� ������ ���� ��
					slotNum = 9;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(eraserRect)) { // ���찳 ������ ���� ��
					slotNum = 10;
				}
				else if (GET_SINGLE(InputManager)->CheckMousePoint(resetRect)) { // �ʱ�ȭ ������ ���� ��
					slotNum = 11;
				}
			}
			wchar_t debugMsg[100];
			swprintf(debugMsg, 100, L"SlotNum: %d\n", slotNum);
			OutputDebugString(debugMsg);
		}
	}
	void Render(HDC hdc) {
		if (isActive_) {
			Rectangle(hdc, toolRect.left, toolRect.top, toolRect.right, toolRect.bottom); // ���� �� �׵θ� �׸���
			Rectangle(hdc, slotOneRect.left, slotOneRect.top, slotOneRect.right, slotOneRect.bottom); // 1�� ���� �׸���
			Rectangle(hdc, slotTwoRect.left, slotTwoRect.top, slotTwoRect.right, slotTwoRect.bottom); // 2�� ���� �׸���
			Rectangle(hdc, slotThreeRect.left, slotThreeRect.top, slotThreeRect.right, slotThreeRect.bottom); // 3�� ���� �׸���
			Rectangle(hdc, slotFourRect.left, slotFourRect.top, slotFourRect.right, slotFourRect.bottom); // 4�� ���� �׸���
			Rectangle(hdc, slotFiveRect.left, slotFiveRect.top, slotFiveRect.right, slotFiveRect.bottom); // 5�� ���� �׸���
			Rectangle(hdc, slotSixRect.left, slotSixRect.top, slotSixRect.right, slotSixRect.bottom); // 6�� ���� �׸���
			Rectangle(hdc, slotSevenRect.left, slotSevenRect.top, slotSevenRect.right, slotSevenRect.bottom); // 7�� ���� �׸���
			Rectangle(hdc, slotEightRect.left, slotEightRect.top, slotEightRect.right, slotEightRect.bottom); // 8�� ���� �׸���
			Rectangle(hdc, slotNineRect.left, slotNineRect.top, slotNineRect.right, slotNineRect.bottom); // 9�� ���� �׸���
			Rectangle(hdc, eraserRect.left, eraserRect.top, eraserRect.right, eraserRect.bottom); // ���찳 ���� �׸���
			Rectangle(hdc, resetRect.left, resetRect.top, resetRect.right, resetRect.bottom); // �ʱ�ȭ ���� �׸���
			SetBkMode(hdc, TRANSPARENT); // �ؽ�Ʈ ��� ����
			wchar_t one[100]; // 1�� ���� ǥ��
			swprintf(one, 100, L"1");
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, one, -1, &slotOneRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t two[100]; // 2�� ���� ǥ��
			swprintf(two, 100, L"2");
			DrawText(hdc, two, -1, &slotTwoRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t thr[100]; // 3�� ���� ǥ��
			swprintf(thr, 100, L"3");
			DrawText(hdc, thr, -1, &slotThreeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t four[100]; // 4�� ���� ǥ��
			swprintf(four, 100, L"4");
			DrawText(hdc, four, -1, &slotFourRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t five[100]; // 5�� ���� ǥ��
			swprintf(five, 100, L"5");
			DrawText(hdc, five, -1, &slotFiveRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t six[100]; // 6�� ���� ǥ��
			swprintf(six, 100, L"6");
			DrawText(hdc, six, -1, &slotSixRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t seven[100]; // 7�� ���� ǥ��
			swprintf(seven, 100, L"7");
			DrawText(hdc, seven, -1, &slotSevenRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t eight[100]; // 8�� ���� ǥ��
			swprintf(eight, 100, L"8");
			DrawText(hdc, eight, -1, &slotEightRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t nine[100]; // 9�� ���� ǥ��
			swprintf(nine, 100, L"9");
			DrawText(hdc, nine, -1, &slotNineRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t eraser[100]; // ���찳 ���� ǥ��
			swprintf(eraser, 100, L"Eraser");
			DrawText(hdc, eraser, -1, &eraserRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wchar_t reset[100]; // �ʱ�ȭ ���� ǥ��
			swprintf(reset, 100, L"Reset");
			DrawText(hdc, reset, -1, &resetRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SetBkMode(hdc, OPAQUE); // �ؽ�Ʈ ��� ����
		}
	}
};