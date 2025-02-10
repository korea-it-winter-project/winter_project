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
	start_pos = { 500, 380 }; // 시작 버튼 중심 좌표
	opt_pos = { 360, 460 }; // 맵 수정 버튼 중심 좌표
	exit_pos = { 640, 460 }; // 종료 버튼 중심 좌표
	startRect = { (int)start_pos.x - 275, (int)start_pos.y - 35, (int)start_pos.x + 275, (int)start_pos.y + 35 }; // 시작 버튼 좌표
	mapEditRect = { (int)opt_pos.x - 135, (int)opt_pos.y - 35, (int)opt_pos.x + 135, (int)opt_pos.y + 35 }; // 맵 수정 버튼 좌표
	exitRect = { (int)exit_pos.x - 135, (int)exit_pos.y - 35, (int)exit_pos.x + 135, (int)exit_pos.y + 35 }; // 종료 버튼 좌표
	isTitle_ = true;
	isStart_ = false;
	isMapEdit_ = false;
}
void StartScene::Update() {
	if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) { // 좌클릭 인식
		if (GET_SINGLE(InputManager)->CheckMousePoint(startRect)) { // 시작 버튼을 누를 경우
			isTitle_ = false;
			isStart_ = true;
			isMapEdit_ = false;
			GET_SINGLE(SceneManager)->ChScene(sceneType::UiScene);
		}
		if (GET_SINGLE(InputManager)->CheckMousePoint(mapEditRect)) { // 맵 수정 버튼을 누를 경우
			isTitle_ = false;
			isStart_ = false;
			isMapEdit_ = true;
			GET_SINGLE(SceneManager)->ChScene(sceneType::Leveleditor);
		}
		if (GET_SINGLE(InputManager)->CheckMousePoint(exitRect)) { // 종료 버튼을 누를 경우
			isTitle_ = false;
		}
	}
}
void StartScene::Render(HDC hdc) {
	if (isTitle_) {
		Rectangle(hdc, startRect.left, startRect.top, startRect.right, startRect.bottom); // 시작 버튼
		Rectangle(hdc, mapEditRect.left, mapEditRect.top, mapEditRect.right, mapEditRect.bottom); // 맵 수정 버튼
		Rectangle(hdc, exitRect.left, exitRect.top, exitRect.right, exitRect.bottom); // 종료 버튼
		SetBkMode(hdc, TRANSPARENT); // 텍스트 배경 없앰
		wchar_t start[100]; // 게임 시작 표기
		swprintf(start, 100, L"GAME START");
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, start, -1, &startRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t mapEdit[100]; // 맵 수정 표기
		swprintf(mapEdit, 100, L"MAP EDIT");
		DrawText(hdc, mapEdit, -1, &mapEditRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t exit[100]; // 게임 종료 표기
		swprintf(exit, 100, L"EXIT");
		DrawText(hdc, exit, -1, &exitRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetBkMode(hdc, OPAQUE); // 텍스트 배경 복구
	}
}