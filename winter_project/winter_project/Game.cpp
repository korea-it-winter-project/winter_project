#include "pch.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "Camera.h" // ī�޶� ��� �߰�

Game::Game() {
    // ������ ����
    int* p = new int();
    GET_SINGLE(SceneManager)->ChScene(sceneType::Leveleditor);

    // ī�޶� �ʱ�ȭ (�ʱ� ȭ�� ũ�� ����)
    camera = Camera(0.0f,0.0f);
}

Game::~Game() {
    // �޸� ����
}

void Game::SceneSzieCH(HWND hwnd) {
    _hwnd = hwnd;
    ::GetClientRect(hwnd, &_rect);
    _hdcBack = ::CreateCompatibleDC(_hdc);
    _tempBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _tempBack);
    ::DeleteObject(prev);

    // ������ ũ�� ���� �� ī�޶� ����Ʈ ũ�� ����
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

    // ī�޶� �ʱ�ȭ (�ʱ� ����Ʈ ũ�� ����)
    //camera = Camera((float)_rect.right, (float)_rect.bottom);
}

void Game::Update() {
    // Ŭ���̾�Ʈ ���� ũ�� ����
    GetClientRect(_hwnd, &_rect);

    GET_SINGLE(TimeManager)->Update();
    GET_SINGLE(InputManager)->Update();
    GET_SINGLE(UiManager)->Update();
    GET_SINGLE(SceneManager)->Update();

    // �Է¿� ���� ī�޶� �̵� ó��
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        camera.Move(Vector(-5.0f, 0.0f)); // ���� �̵�
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        camera.Move(Vector(5.0f, 0.0f)); // ������ �̵�
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        camera.Move(Vector(0.0f, -5.0f)); // ���� �̵�
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        camera.Move(Vector(0.0f, 5.0f)); // �Ʒ��� �̵�
    }
}

void Game::Render() {
    UINT32 fps = GET_SINGLE(TimeManager)->GetFps();
    float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
    POINT m_pos = GET_SINGLE(InputManager)->GetMousePos();
    WCHAR str[1024];
    

    // ī�޶� ��ǥ�� ������� ���� ��ǥ �� ȭ�� ��ǥ ��ȯ
    Vector worldPos(0,0); // ���� ��ǥ ����
    Vector screenPos = camera.WorldToScreen(worldPos);

    WCHAR camInfo[1024];
    
    // ȭ�鿡 ��� (��ȯ�� ȭ�� ��ǥ ����)

    // UI �� �� ������
    GET_SINGLE(UiManager)->Render(_hdcBack);
    GET_SINGLE(SceneManager)->Render(_hdcBack);

    //::TextOut(_hdcBack, (int)screenPos.x, (int)screenPos.y, L"Camera Target", 13);
    wsprintfW(camInfo, L"Camera pos : [%04d, %04d]", (int)camera.GetPosition().x, (int)camera.GetPosition().y);
    ::TextOut(_hdcBack, (int)screenPos.x + 20, (int)screenPos.y + 30, camInfo, lstrlen(camInfo));
    wsprintfW(str, L"mouse pos : [%04d, %04d]", m_pos.x, m_pos.y);
    ::TextOut(_hdcBack, (int)screenPos.x + 20, (int)screenPos.y + 10, str, lstrlen(str));
    // ���� ���۸����� ȭ�� ���
    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, screenPos.x, screenPos.y, SRCCOPY);
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
