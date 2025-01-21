#include "pch.h"

//#include "Game.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"

Game::Game() {
    // 생성자 구현
    int* p = new int();
}

Game::~Game() {

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

    //_player = new Player();

    GET_SINGLE(SceneManager)->Init();
    GET_SINGLE(SceneManager)->ChScene(sceneType::DevScene);
}

void Game::Update() {
    GET_SINGLE(TimeManager)->Update();
    GET_SINGLE(InputManager)->Update();
    GET_SINGLE(SceneManager)->Update();
    //float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


}

void Game::Render() {
    UINT32 fps = GET_SINGLE(TimeManager)->GetFps();
    float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    POINT m_pos = GET_SINGLE(InputManager)->GetMousePos();
    WCHAR str[1024];
    wsprintfW(str, L"mouse pos : [%04d, %04d]", m_pos.x, m_pos.y);
    ::TextOut(_hdcBack, 20, 10, str, lstrlen(str));

    Rectangle(_hdcBack, m_pos.x - 25, m_pos.y - 25, m_pos.x + 25, m_pos.y + 25);

    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack,0, 0, SRCCOPY);
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);

    GET_SINGLE(SceneManager)->Render(_hdc);
}
