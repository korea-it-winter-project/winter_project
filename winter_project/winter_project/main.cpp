#include "pch.h"
#include "Game.h" // Game Ŭ���� �߰�
#include "InputManager.h"
#include "TimeManager.h"

HINSTANCE hInst;
HWND g_hwnd;

Game game;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("�����̵�");

#define t_print(x, y, text, number) TextOut(hdc, x, y, text, number)
#define m_box(title, text) MessageBox(hWnd, text, title, MB_OK)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
    MSG msg = {};
    g_hInst = hInstance;

    // 1. ������ Ŭ���� ���
    if (!MyRegisterClass(hInstance)) {
        MessageBox(NULL, L"Window Class Registration Failed!", L"Error", MB_ICONERROR);
        return FALSE;
    }

    // 2. ������ �ν��Ͻ� �ʱ�ȭ
    if (!InitInstance(hInstance, nCmdShow)) {
        MessageBox(NULL, L"Window Instance Initialization Failed!", L"Error", MB_ICONERROR);
        return FALSE;
    }

    // 3. ���� ��ü ���� �� �ʱ�ȭ
    game.Init(g_hwnd);

    // 4. �޽��� ���� ����
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // ���� ����
            game.Update();
            game.Render();
        }
    }

    return (int)msg.wParam;
} 

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    RECT winRect = { 0, 0, 800, 600 };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(
        L"GameCoding2",      // Ŭ���� �̸� (MyRegisterClass���� ����� �̸�)
        L"Game Window",      // ������ ����
        WS_OVERLAPPEDWINDOW, // ��Ÿ��
        CW_USEDEFAULT, 0,
        winRect.right - winRect.left,
        winRect.bottom - winRect.top,
        nullptr, nullptr, hInstance, nullptr
    );
       
    g_hwnd = hWnd;

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �⺻ ������
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // �⺻ Ŀ��
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� ����
    wcex.lpszMenuName = nullptr; // �޴� ����
    wcex.lpszClassName = L"GameCoding2"; // Ŭ���� �̸�
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // ���� ������

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage) {
        case                                                                      

    case WM_SIZE:
        game.SceneSzieCH(g_hwnd);
                 
        InvalidateRect(hWnd, NULL, false);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, iMessage, wParam, lParam);
    }
}
