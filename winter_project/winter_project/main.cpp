

#include <windows.h>                           // ������ �������
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "init.h"
#include "resource.h"
HINSTANCE hInst;;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                              //�ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("�ڼ���_24311032");         //���� ǥ���ٿ� ǥ�õǴ� ����


#define t_print(x,y,text,number) TextOut(hdc, x, y, text, number)
#define m_box(title, text) MessageBox(hWnd, text, title, MB_OK)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;                                 //������ �ڵ� ����
    MSG Message;                              //�޼��� ����ü ���� ����
    WNDCLASS WndClass;                           //Windows Class ����ü ���� ����
    g_hInst = hInstance;                        //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

    WndClass.cbClsExtra = 0;                     //���� ����. ������ ���X
    WndClass.cbWndExtra = 0;                     //���� ����
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // �������� ��� ������ ����
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //�������� ���콺������ ����� ����
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //�������� Ŀ�� ������ ��� ����
    WndClass.hInstance = hInstance;                  //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
    WndClass.lpfnWndProc = WndProc;                  //������ �޼��� ó�� �Լ� ����
    WndClass.lpszClassName = lpszClass;               //������ Ŭ������ �̸� ����
    WndClass.lpszMenuName = MAKEINTRESOURCE(NULL);                  //�޴� ����
    WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;         //�������� ��Ÿ���� ����

    RegisterClass(&WndClass);                     //WNDCLASS ����ü�� ������ ����


    hWnd = CreateWindow(lpszClass, lpszClass,         //�����츦 ����
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //�޼��� ������ ����
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue�� �ִ� �޼����� �о���δ�
        TranslateMessage(&Message);                  //Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� 
        //  ����� �� �ֵ���
        DispatchMessage(&Message);                  //�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
    }
    return (int)Message.wParam;                     //Ż�� �ڵ�. ���α׷� ����
}
#define pc_size 25
#define Bsize2 10
#define rc 13
#define re 15
#define swap(x,y) temp = x; x=y;y=temp;


double lengthpts(int x1, int y1, int x2, int y2) {
    return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}
//bool inCircle(int x, int y, int mx, int my) {
//    if (lengthpts(x, y, mx, my) <= Bsize) return true;
//    return false;
//}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    //Ellipse(hdc, x, y, x + 20, y + 20); ���׸���
    //SetTimer(hWnd, number, ms, NULL); 
     //wsprintf(LPOUT, TEXT("%d : %d"), df.x, df.y);
    //TextOut(hdc, 100, 100, LPOUT,lstrlen(LPOUT));
    HDC hdc, bufferDC, bufferDC2;
    static HBITMAP hBit1, hBit2, oldBit1, oldBit2;
    PAINTSTRUCT ps;
    HBRUSH MyBrush, OldBrush;
    RECT rectView;
    HPEN Hpen, oldpen;
    HBRUSH hB, oB;
    static bool mouse_truck;
    static player pc;
    static Vector2 mouse_pos;
    WCHAR text[1024];

    

    switch (iMessage) {
    case WM_CREATE:
        //hBit1 = hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        SetTimer(hWnd, 1, 1, NULL);
    case WM_SIZE:
        GetClientRect(hWnd, &rectView);
        break;
    case WM_TIMER:
        pc.dir.x = pc.pos.x - mouse_pos.x;
        pc.dir.y = pc.pos.y - mouse_pos.y;

        pc.dir.x = pc.dir.x / lengthpts(pc.pos.x, pc.pos.y, mouse_pos.x, mouse_pos.y);
        pc.dir.y = pc.dir.y / lengthpts(pc.pos.x, pc.pos.y, mouse_pos.x, mouse_pos.y);
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_LBUTTONDOWN:
        mouse_truck = true; break;
    case WM_MOUSEMOVE:
        if (mouse_truck) {
            mouse_pos.x=LOWORD(lParam), mouse_pos.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, false);
        }

        break;
    case WM_LBUTTONUP:
        mouse_truck = false;
        break;
    case WM_KEYDOWN:
        /*switch (wParam) {
        case 'W': case VK_UP: pc.pos.y -= 1; break;
        case 'A': case VK_LEFT: pc.pos.x -= 1; break;
        case 'S': case VK_DOWN: pc.pos.y += 1; break;
        case 'D': case VK_RIGHT: pc.pos.x += 1; break;
        }*/
        pc.before_pos = pc.pos;
        if(GetAsyncKeyState('W')|| GetAsyncKeyState(VK_UP)) pc.pos.y -= 1;
        if(GetAsyncKeyState('A')|| GetAsyncKeyState(VK_LEFT))pc.pos.x -= 1;
        if(GetAsyncKeyState('S')|| GetAsyncKeyState(VK_DOWN))pc.pos.y += 1;
        if(GetAsyncKeyState('D')|| GetAsyncKeyState(VK_RIGHT))pc.pos.x += 1;
        InvalidateRect(hWnd, NULL,true);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        bufferDC = CreateCompatibleDC(hdc);
        bufferDC2 = CreateCompatibleDC(bufferDC);
        if (hBit1 == NULL)
            hBit1 = CreateCompatibleBitmap(hdc, 800, 500);
        oldBit1 = (HBITMAP)SelectObject(bufferDC, hBit1);
        oldBit2 = (HBITMAP)SelectObject(bufferDC2, hBit2);

        BitBlt(bufferDC, 0, 0, 800, 500, bufferDC2, 0, 0, SRCCOPY);

        		//������ ���� ��� SetBackGroundMode
        wsprintf(text, L"%d : %d  %d : %d   %d.%d : %d.%d",
            (int)pc.pos.x, (int)pc.pos.y, (int)mouse_pos.x, (int)mouse_pos.y,
            (int)pc.dir.x, (int)(pc.dir.x * 100) % 100,
            (int)pc.dir.y, (int)(pc.dir.y * 100) % 100);
        TextOut(bufferDC, 100, 100, text, lstrlen(text));
        Ellipse(bufferDC, pc.pos.x - pc_size, pc.pos.y - pc_size, pc.pos.x + pc_size, pc.pos.y + pc_size);
        Ellipse(bufferDC, (int)mouse_pos.x - 5, (int)mouse_pos.y - 5, (int)mouse_pos.x + 5, (int)mouse_pos.y + 5);
        BitBlt(hdc, 0, 0, 800, 500, bufferDC, 0, 0, SRCCOPY);

        SelectObject(bufferDC, oldBit1);
        SelectObject(bufferDC2, oldBit2);
        DeleteDC(bufferDC);
        DeleteDC(bufferDC2);
        //EndPaint(hwnd, &ps);

        EndPaint(hWnd, &ps);

        return 0;
    case WM_DESTROY:
        PostQuitMessage(1);
        KillTimer(hWnd,1);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}