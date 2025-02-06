#include "pch.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "Camera.h" // 카메라 헤더 추가
#include "ObjectManager.h"

Game::Game() {
    GET_SINGLE(SceneManager)->ChScene(sceneType::GameScene);

    // 카메라 초기화 (초기 화면 크기 설정)
    camera = Camera(0.0f, 0.0f);
}

Game::~Game() {
    // 백 버퍼와 DC 해제
    if (_tempBack) {
        ::DeleteObject(_tempBack);
        _tempBack = nullptr;
    }
    if (_hdcBack) {
        ::DeleteDC(_hdcBack);
        _hdcBack = nullptr;
    }
    if (_hdc) {
        ::ReleaseDC(_hwnd, _hdc);
        _hdc = nullptr;
    }
}

void Game::SceneSzieCH(HWND hwnd) {
    
    _hwnd = hwnd;
    ::GetClientRect(hwnd, &_rect);

    // 기존 백 버퍼 삭제
    if (_tempBack) {
        ::DeleteObject(_tempBack);
    }
    if (_hdcBack) {
        ::DeleteDC(_hdcBack);
    }

    // 백 버퍼 및 호환 DC 재생성
    _hdcBack = ::CreateCompatibleDC(_hdc);
    _tempBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _tempBack);
    ::DeleteObject(prev);
}

void Game::Init(HWND hwnd) {
    _hwnd = hwnd;
    _hdc = ::GetDC(hwnd);
    ::GetClientRect(hwnd, &_rect);

    

    // 백 버퍼 생성
    _hdcBack = ::CreateCompatibleDC(_hdc);
    _tempBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _tempBack);
    ::DeleteObject(prev);

    GET_SINGLE(TimeManager)->Init();
    GET_SINGLE(InputManager)->Init(hwnd);
    GET_SINGLE(UiManager)->init();
    GET_SINGLE(SceneManager)->Init();

}

void Game::Update() {
    // 클라이언트 영역 크기 갱신
    GetClientRect(_hwnd, &_rect);

    GET_SINGLE(TimeManager)->Update();
    GET_SINGLE(InputManager)->Update();
    GET_SINGLE(UiManager)->Update();
    GET_SINGLE(SceneManager)->Update();
    GET_SINGLE(ObjectManager)->CheckCollisions();

    const std::vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
    for (Object* object : objects)
        object->Update();

}

void Game::Render() {
    UINT32 fps = GET_SINGLE(TimeManager)->GetFps();
    float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    POINT m_pos = GET_SINGLE(InputManager)->GetMousePos();
    WCHAR str[1024];

    // 백 버퍼 초기화
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);

    wsprintfW(str, L"fps[%03d]/dtime[%03d]", fps, (int)(deltaTime*1000));
    ::TextOut(_hdcBack, 10, 10, str, lstrlen(str));


    wsprintfW(str, L"mouse pos : [%04d, %04d]", m_pos.x, m_pos.y);
    ::TextOut(_hdcBack, 10, 30, str, lstrlen(str));

    // UI 및 씬 렌더링
    GET_SINGLE(UiManager)->Render(_hdcBack);
    GET_SINGLE(SceneManager)->Render(_hdcBack,camera);

    const std::vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
    for (Object* object : objects)
        object->Render(_hdcBack);
    // 화면 출력
    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
}
