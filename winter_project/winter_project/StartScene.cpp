#include "pch.h"
#include "UiScene.h"
#include "StartScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "sceneManager.h"

Vector start_pos;
Vector opt_pos;
Vector exit_pos;
RECT startRect;
RECT mapEditRect;
RECT exitRect;
bool isTitle_;
bool isStart_;
bool isMapEdit_;

StartScene::StartScene() {

}
StartScene::~StartScene() {

}
void StartScene::Init() {
	start_pos = { 500, 380 }; // ���� ��ư �߽� ��ǥ
	opt_pos = { 360, 460 }; // �� ���� ��ư �߽� ��ǥ
	exit_pos = { 640, 460 }; // ���� ��ư �߽� ��ǥ
	startRect = { (int)start_pos.x - 275, (int)start_pos.y - 35, (int)start_pos.x + 275, (int)start_pos.y + 35 }; // ���� ��ư ��ǥ
	mapEditRect = { (int)opt_pos.x - 135, (int)opt_pos.y - 35, (int)opt_pos.x + 135, (int)opt_pos.y + 35 }; // �� ���� ��ư ��ǥ
	exitRect = { (int)exit_pos.x - 135, (int)exit_pos.y - 35, (int)exit_pos.x + 135, (int)exit_pos.y + 35 }; // ���� ��ư ��ǥ
	isTitle_ = true;
	isStart_ = false;
	isMapEdit_ = false;
}
void StartScene::Update() {
	if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) { // ��Ŭ�� �ν�
		if (GET_SINGLE(InputManager)->CheckMousePoint(startRect)) { // ���� ��ư�� ���� ���
			isTitle_ = false;
			isStart_ = true;
			isMapEdit_ = false;
			GET_SINGLE(SceneManager)->ChScene(sceneType::UiScene);
		}
		if (GET_SINGLE(InputManager)->CheckMousePoint(mapEditRect)) { // �� ���� ��ư�� ���� ���
			isTitle_ = false;
			isStart_ = false;
			isMapEdit_ = true;
			GET_SINGLE(SceneManager)->ChScene(sceneType::Leveleditor);
		}
		if (GET_SINGLE(InputManager)->CheckMousePoint(exitRect)) { // ���� ��ư�� ���� ���
			isTitle_ = false;
		}
	}
}
void StartScene::Render(HDC hdc) {
	if (isTitle_) {
		Rectangle(hdc, startRect.left, startRect.top, startRect.right, startRect.bottom); // ���� ��ư
		Rectangle(hdc, mapEditRect.left, mapEditRect.top, mapEditRect.right, mapEditRect.bottom); // �� ���� ��ư
		Rectangle(hdc, exitRect.left, exitRect.top, exitRect.right, exitRect.bottom); // ���� ��ư
		SetBkMode(hdc, TRANSPARENT); // �ؽ�Ʈ ��� ����
		wchar_t start[100]; // ���� ���� ǥ��
		swprintf(start, 100, L"GAME START");
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, start, -1, &startRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t mapEdit[100]; // �� ���� ǥ��
		swprintf(mapEdit, 100, L"MAP EDIT");
		DrawText(hdc, mapEdit, -1, &mapEditRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t exit[100]; // ���� ���� ǥ��
		swprintf(exit, 100, L"EXIT");
		DrawText(hdc, exit, -1, &exitRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetBkMode(hdc, OPAQUE); // �ؽ�Ʈ ��� ����
	}
}