#include "pch.h"
#include "UiScene.h"
#include "StartScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "sceneManager.h"
#include "ResourceManager.h"
#include "Leveleditor.h"

POINT start_pos;
Vector opt_pos;
Vector exit_pos;
RECT startRect;
RECT mapEditRect;
RECT exitRect;
bool isTitle_;
bool isStart_;
bool isMapEdit_;
std::shared_ptr<Gdiplus::Bitmap> StartIma;
std::shared_ptr<Gdiplus::Bitmap> MapEditIma;
std::shared_ptr<Gdiplus::Bitmap> ExitIma;
std::shared_ptr<Gdiplus::Bitmap> BackGroundIma;

StartScene::StartScene() {

}
StartScene::~StartScene() {

}
void StartScene::Init() {
	start_pos = { 500, 450 }; // ���� ��ư �߽� ��ǥ
	opt_pos = { 360, 530 }; // �� ���� ��ư �߽� ��ǥ
	exit_pos = { 640, 530 }; // ���� ��ư �߽� ��ǥ
	startRect = { (int)start_pos.x - 275, (int)start_pos.y - 35, (int)start_pos.x + 275, (int)start_pos.y + 35 }; // ���� ��ư ��ǥ
	mapEditRect = { (int)opt_pos.x - 135, (int)opt_pos.y - 35, (int)opt_pos.x + 135, (int)opt_pos.y + 35 }; // �� ���� ��ư ��ǥ
	exitRect = { (int)exit_pos.x - 135, (int)exit_pos.y - 35, (int)exit_pos.x + 135, (int)exit_pos.y + 35 }; // ���� ��ư ��ǥ
	StartIma = GET_SINGLE(ResourceManager)->FindImage(L"start_start_button.png");
	MapEditIma = GET_SINGLE(ResourceManager)->FindImage(L"start_map_edit_button.png");
	ExitIma = GET_SINGLE(ResourceManager)->FindImage(L"start_exit_button.png");
	BackGroundIma = GET_SINGLE(ResourceManager)->FindImage(L"start_main_background.png");
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
			isStart_ = false;
			isMapEdit_ = false;
		}
	}
}
void StartScene::Render(HDC hdc) {
	Gdiplus::Graphics graphics(hdc);
	if (isTitle_) {
		if (BackGroundIma) { // �⺻ ���
			GET_SINGLE(ResourceManager)->DrawImage(graphics, BackGroundIma, 0, 0, 1000.0, 600.0);
			//GET_SINGLE(ResourceManager)->DrawImage2(hdc, BackGroundIma, 0, 0, 1000.0, 600.0);
		}
		if (StartIma) { // ���� ���� ��ư
			//GET_SINGLE(ResourceManager)->DrawImage2(hdc, StartIma, startRect.left, startRect.top, 550.0, 70.0);
			GET_SINGLE(ResourceManager)->DrawImage(graphics, StartIma, startRect.left, startRect.top, 550.0, 70.0);
		}
		if (MapEditIma) { // �� ���� ��ư
			GET_SINGLE(ResourceManager)->DrawImage(graphics, MapEditIma, mapEditRect.left, mapEditRect.top, 270.0, 70.0);
			//GET_SINGLE(ResourceManager)->DrawImage2(hdc, MapEditIma, mapEditRect.left, mapEditRect.top, 270.0, 70.0);
		}
		if (ExitIma) { // ���� ��ư
			GET_SINGLE(ResourceManager)->DrawImage(graphics, ExitIma, exitRect.left, exitRect.top, 270.0, 70.0);
			//GET_SINGLE(ResourceManager)->DrawImage2(hdc, ExitIma, exitRect.left, exitRect.top, 270.0, 70.0);
		}
	}
}