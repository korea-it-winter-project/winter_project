#include "pch.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "Camera.h" // 카메라 헤더 추가

Game::Game() {
    // 생성자 구현
    int* p = new int();
    GET_SINGLE(SceneManager)->ChScene(sceneType::Leveleditor);

    // 카메라 초기화 (초기 화면 크기 설정)
    camera = Camera(0.0f,0.0f);
}

Game::~Game() {
    // 메모리 해제
}

void Game::SceneSzieCH(HWND hwnd) {
    _hwnd = hwnd;
    ::GetClientRect(hwnd, &_rect);
    _hdcBack = ::CreateCompatibleDC(_hdc);
    _tempBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _tempBack);
    ::DeleteObject(prev);

    // 윈도우 크기 변경 시 카메라 뷰포트 크기 갱신
    //camera.SetViewportSize((float)_rect.right, (float)_rect.bottom);
}

void Game::Init(HWND hwnd) {
    _hwnd = hwnd;
    _hdc = ::GetDC(hwnd);
    ::GetClientRect(hwnd, &_rect);
    _hdcBack = ::CreateCompatibleDC(_hdc);
    _tempBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _tempBack);
    ::DeleteObject(prev);

    GET_SINGLE(TimeManager)->Init();
    GET_SINGLE(InputManager)->Init(hwnd);
    GET_SINGLE(UiManager)->init();

    GET_SINGLE(SceneManager)->Init();

    // 카메라 초기화 (초기 뷰포트 크기 설정)
    //camera = Camera((float)_rect.right, (float)_rect.bottom);
}

void Game::Update() {
    // 클라이언트 영역 크기 갱신
    GetClientRect(_hwnd, &_rect);

    GET_SINGLE(TimeManager)->Update();
    GET_SINGLE(InputManager)->Update();
    GET_SINGLE(UiManager)->Update();
    GET_SINGLE(SceneManager)->Update();

    // 입력에 따른 카메라 이동 처리
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        camera.Move(Vector(-5.0f, 0.0f)); // 왼쪽 이동
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        camera.Move(Vector(5.0f, 0.0f)); // 오른쪽 이동
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        camera.Move(Vector(0.0f, -5.0f)); // 위로 이동
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        camera.Move(Vector(0.0f, 5.0f)); // 아래로 이동
    }
}

void Game::Render() {
    UINT32 fps = GET_SINGLE(TimeManager)->GetFps();
    float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    POINT m_pos = GET_SINGLE(InputManager)->GetMousePos();
    WCHAR str[1024];
    

    // 카메라 좌표를 기반으로 월드 좌표 → 화면 좌표 변환
    Vector worldPos(0,0); // 월드 좌표 예시
    Vector screenPos = camera.WorldToScreen(worldPos);

    WCHAR camInfo[1024];
    
    // 화면에 출력 (변환된 화면 좌표 기준)

    // UI 및 씬 렌더링
    GET_SINGLE(UiManager)->Render(_hdcBack);
    GET_SINGLE(SceneManager)->Render(_hdcBack);

    //::TextOut(_hdcBack, (int)screenPos.x, (int)screenPos.y, L"Camera Target", 13);
    wsprintfW(camInfo, L"Camera pos : [%04d, %04d]", (int)camera.GetPosition().x, (int)camera.GetPosition().y);
    ::TextOut(_hdcBack, (int)screenPos.x + 20, (int)screenPos.y + 30, camInfo, lstrlen(camInfo));
    wsprintfW(str, L"mouse pos : [%04d, %04d]", m_pos.x, m_pos.y);
    ::TextOut(_hdcBack, (int)screenPos.x + 20, (int)screenPos.y + 10, str, lstrlen(str));
    // 더블 버퍼링으로 화면 출력
    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, screenPos.x, screenPos.y, SRCCOPY);
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
