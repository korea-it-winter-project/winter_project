#include "pch.h"

//#include "Game.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "ToolUi.h"
#include "StartScene.h"
#include "BackScene.h"

Game::Game() {
    // 생성자 구현
    int* p = new int();
    GET_SINGLE(SceneManager)->ChScene(sceneType::StartScene);
}

Game::~Game() {
    GET_SINGLE(ObjectManager)->~ObjectManager();
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
    //_player = new Player();

    GET_SINGLE(SceneManager)->Init();
    GET_SINGLE(ResourceManager)->LoadImagesIntoManager(L"..\\winter_project\\Dirt"); // png불러오기
    GET_SINGLE(ResourceManager)->LoadImagesIntoManager(L"..\\winter_project\\projectile");
    GET_SINGLE(ResourceManager)->LoadImagesIntoManager(L"..\\winter_project\\Stone");

    GET_SINGLE(ToolUi)->Init();
    GET_SINGLE(BackScene)->Init();
}

void Game::Update() {
    GET_SINGLE(TimeManager)->Update();
    GET_SINGLE(InputManager)->Update(_rect);
    GET_SINGLE(UiManager)->Update();
    GET_SINGLE(SceneManager)->Update();
    //float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::ESC))
    {
        GET_SINGLE(SceneManager)->ChScene(sceneType::Leveleditor);
    }
    const std::vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
    for (Object* object : objects)
        object->Update();

    GET_SINGLE(ToolUi)->Update(_rect);
    GET_SINGLE(BackScene)->Update(_rect);
}

void Game::Render() {
    Gdiplus::Graphics graphics(_hdcBack);

    UINT32 fps = GET_SINGLE(TimeManager)->GetFps();
    float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    // 마우스 좌표
    POINT m_pos = GET_SINGLE(InputManager)->GetMousePos();
    /*WCHAR str[1024];
    wsprintfW(str, L"mouse pos : [%04d, %04d]", m_pos.x, m_pos.y);
    ::TextOut(_hdcBack, 20, 10, str, lstrlen(str));*/

    //Rectangle(_hdcBack, m_pos.x - 25, m_pos.y - 25, m_pos.x + 25, m_pos.y + 25);

    // UI, 씬 렌더링
    GET_SINGLE(UiManager)->Render(_hdcBack);
    GET_SINGLE(SceneManager)->Render(_hdcBack);

    std::shared_ptr<Gdiplus::Bitmap> image = GET_SINGLE(ResourceManager)->FindImage(L"dirt_3.png");
    //std::wstring fileName;
    int tileX = m_pos.x / TILE_SIZE;
    int tileY = m_pos.y / TILE_SIZE;
    int drawX = tileX * TILE_SIZE;
    int drawY = tileY * TILE_SIZE;
    if (GET_SINGLE(MapData)->GetTile(tileX, tileY) != 1) {
        GET_SINGLE(ResourceManager)->DrawImageWithAlpha(graphics, image, drawX, drawY, TILE_SIZE, TILE_SIZE, 0.5f);
    }

    const std::vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
    for (Object* object : objects)
        object->Render(_hdcBack);
    GET_SINGLE(ToolUi)->Render(_hdcBack);
    GET_SINGLE(BackScene)->Render(_hdcBack);

    WCHAR str[1024];
    wsprintfW(str, L"fps : [%04d]", fps);
    ::TextOut(_hdcBack, 10, 10, str, lstrlen(str));

    // 백버퍼 -> 화면
    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
    // 백버퍼 지우기
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
