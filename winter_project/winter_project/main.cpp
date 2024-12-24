

#include <windows.h>                           // ������ �������
#include <stdlib.h>
#include <time.h>
#include <math.h>


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
#define Bsize 25
#define Bsize2 10
#define rc 13
#define re 15
#define swap(x,y) temp = x; x=y;y=temp;


double lengthpts(int x1, int y1, int x2, int y2) {
    return(sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}
bool inCircle(int x, int y, int mx, int my) {
    if (lengthpts(x, y, mx, my) <= Bsize) return true;
    return false;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    //Ellipse(hdc, x, y, x + 20, y + 20); ���׸���
    //SetTimer(hWnd, number, ms, NULL); 
     //wsprintf(LPOUT, TEXT("%d : %d"), df.x, df.y);
    //TextOut(hdc, 100, 100, LPOUT,lstrlen(LPOUT));
    HDC hdc, MemDC, ImgDC;
    PAINTSTRUCT ps;
    HBRUSH MyBrush, OldBrush;

    HPEN Hpen, oldpen;
    HBRUSH hB, oB;





    switch (iMessage) {
    case WM_CREATE:

    case WM_SIZE:
        GetClientRect(hWnd, &rectView);
        break;
    case WM_TIMER:
        
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_KEYDOWN:
       
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);

        return 0;
    case WM_DESTROY:
        PostQuitMessage(1);

        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}