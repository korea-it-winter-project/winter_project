

#include <windows.h>                           // 윈도우 헤더파일
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "init.h"
#include "resource.h"
HINSTANCE hInst;;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                              //인스턴스 핸들
LPCTSTR lpszClass = TEXT("박성원_24311032");         //제목 표시줄에 표시되는 내용


#define t_print(x,y,text,number) TextOut(hdc, x, y, text, number)
#define m_box(title, text) MessageBox(hWnd, text, title, MB_OK)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;                                 //윈도우 핸들 선언
    MSG Message;                              //메세지 구조체 변수 선언
    WNDCLASS WndClass;                           //Windows Class 구조체 변수 선언
    g_hInst = hInstance;                        //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

    WndClass.cbClsExtra = 0;                     //예약 영역. 지금은 사용X
    WndClass.cbWndExtra = 0;                     //예약 영역
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // 윈도우의 배경 색상을 지정
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //윈도우의 마우스포인터 모양을 지정
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //윈도우의 커서 아이콘 모양 지정
    WndClass.hInstance = hInstance;                  //윈도우 클래스를 등록하는 프로그램 번호
    WndClass.lpfnWndProc = WndProc;                  //윈도우 메세지 처리 함수 지정
    WndClass.lpszClassName = lpszClass;               //윈도우 클래스의 이름 지정
    WndClass.lpszMenuName = MAKEINTRESOURCE(NULL);                  //메뉴 지정
    WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;         //윈도우의 스타일을 정의

    RegisterClass(&WndClass);                     //WNDCLASS 구조체의 번지를 전달


    hWnd = CreateWindow(lpszClass, lpszClass,         //윈도우를 생성
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //메세지 루프를 실행
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue에 있는 메세지를 읽어들인다
        TranslateMessage(&Message);                  //키보드 입력 메세지를 가공하여 프로그램에서 쉽게 
        //  사용할 수 있도록
        DispatchMessage(&Message);                  //메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
    }
    return (int)Message.wParam;                     //탈출 코드. 프로그램 종료
}
#define pc_size 25
#define Bsize2 10
#define rc 13
#define re 15
#define swap(x,y) temp = x; x=y;y=temp;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    //Ellipse(hdc, x, y, x + 20, y + 20); 원그리기
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
        pc.update_dir(mouse_pos);
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

        pc.before_pos = pc.pos;
        pc.move();
        InvalidateRect(hWnd, NULL,true);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        bufferDC = CreateCompatibleDC(hdc);
        bufferDC2 = CreateCompatibleDC(bufferDC);
        if (hBit1 == NULL)
            hBit1 = CreateCompatibleBitmap(hdc, 800, 500);
        

        
        wsprintf(text, L"%4d : %4d  %4d : %4d   %d.%2d : %d.%2d",
            (int)pc.pos.x, (int)pc.pos.y, (int)mouse_pos.x, (int)mouse_pos.y,
            (int)pc.dir.x, (int)(pc.dir.x * 100) % 100,
            (int)pc.dir.y, (int)(pc.dir.y * 100) % 100);
        TextOut(hdc, 100, 100, text, lstrlen(text));
        Ellipse(hdc, (int)pc.pos.x - (int)pc_size, (int)pc.pos.y - (int)pc_size, (int)pc.pos.x + (int)pc_size, (int)pc.pos.y + pc_size);
        Ellipse(hdc, (int)mouse_pos.x - 5, (int)mouse_pos.y - 5, (int)mouse_pos.x + 5, (int)mouse_pos.y + 5);
        //BitBlt(hdc, 0, 0, 800, 500, bufferDC, 0, 0, SRCCOPY);

       /* SelectObject(bufferDC, oldBit1);
        SelectObject(bufferDC2, oldBit2);
        DeleteDC(bufferDC);
        DeleteDC(bufferDC2);*/
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