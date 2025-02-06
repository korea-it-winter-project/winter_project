#pragma once
#include "Scene.h"
#include "InputManager.h"
#include "Camera.h"
#include <string>
#include <fstream>

// ------------------------
// FHD 해상도에 맞춘 설정
// ------------------------
static const int TILE_SIZE = 24;   // 한 타일의 픽셀 크기
static const int MAP_COLS = 80;   // 가로 타일 개수
static const int MAP_ROWS = 45;   // 세로 타일 개수

class Leveleditor : public Scene {
    class Player* _player = nullptr;
public:
    Leveleditor() {
       /* _player = new Player();
        _player->Init();*/
        // 타일 배열 초기화
        for ( int y = 0; y < MAP_ROWS; ++y ) {
            for ( int x = 0; x < MAP_COLS; ++x ) {
                mapData[ y ][ x ] = 0; // 0은 빈칸
            }
        }

        // 시작 타일 종류
        selectedTile = 1;
    };
    virtual ~Leveleditor() override {};

    virtual void Init(HWND hwnd) override {
        LoadFromFileText( "map.csv" );
    };

    virtual void Update() override {



        if ( GetAsyncKeyState( VK_DELETE ) & 0x0001 )
        {
            if ( MessageBox( nullptr,TEXT( "※맵 데이터를 초기화하시겠습니까?" ),TEXT( "주의" ),MB_YESNO | MB_ICONWARNING /*경고 아이콘*/) 
                == IDYES )
            {
                // 맵 데이터 초기화
                for ( int y = 0; y < MAP_ROWS; ++y ) {
                    for ( int x = 0; x < MAP_COLS; ++x ) {
                        mapData[ y ][ x ] = 0;
                    }
                }
                SaveToFileText( "map.csv" );
                MessageBox( nullptr,TEXT( "저장되었습니다." ),TEXT( "알림" ),MB_OK | MB_ICONINFORMATION/*윈도우 정보아이콘*/);
            }
        }
        // Ctrl + S로 저장
        if ( GET_SINGLE( InputManager )->GetButton( keytype::L_Ctrl ) &&
             GET_SINGLE( InputManager )->GetButton( keytype::S ) )
        {
            SaveToFileText( "map.csv" );
            MessageBox( nullptr,TEXT( "저장되었습니다." ),TEXT( "알림" ),MB_OK | MB_ICONINFORMATION/*윈도우 정보아이콘*/ );
        }

        // 마우스 좌표 얻기
        POINT pt;
        GetCursorPos( &pt );
        pt = GET_SINGLE( InputManager )->GetMousePos();

        // 왼쪽 버튼이 눌려 있는 동안 타일 배치
        if ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) {
            int tileX = pt.x / TILE_SIZE;
            int tileY = pt.y / TILE_SIZE;

            if ( tileX >= 0 && tileX < MAP_COLS &&
                tileY >= 0 && tileY < MAP_ROWS )
            {
                mapData[ tileY ][ tileX ] = selectedTile;
            }
        }

        // 숫자 키(1~3, 0)로 타일 종류 선택
        if ( GetAsyncKeyState( '1' ) & 0x0001 ) {
            selectedTile = 1;
        }
        else if ( GetAsyncKeyState( '2' ) & 0x0001 ) {
            selectedTile = 2;
        }
        else if ( GetAsyncKeyState( '3' ) & 0x0001 ) {
            selectedTile = 3;
        }
        else if ( GetAsyncKeyState( '0' ) & 0x0001 ) {
            selectedTile = 0;
        }
    };

    bool grid = true;
    virtual void Render( HDC hdc ) override {
        // 스페이스바를 누르면 그리드(격자) 표시 on/off
        if ( GET_SINGLE( InputManager )->GetButtonDwon( keytype::SPBAR ) ) {
            grid = !grid;
        }

        // 타일 그리기
        for ( int y = 0; y < MAP_ROWS; ++y ) {
            for ( int x = 0; x < MAP_COLS; ++x ) {
                int tileType = mapData[ y ][ x ];
                if ( tileType == 0 ) {
                    // 빈 칸이면 그냥 배경에 그리드만 표시
                    continue;
                }

                COLORREF color;
                switch ( tileType ) {
                case 1: color = RGB( 255,0,0 );   break; // 빨강
                case 2: color = RGB( 0,255,0 );   break; // 초록
                case 3: color = RGB( 0,0,255 );   break; // 파랑
                default: color = RGB( 0,0,0 );    break; // 기타
                }

                HBRUSH brush = CreateSolidBrush( color );
                HBRUSH oldBrush = ( HBRUSH ) SelectObject( hdc,brush );

                RECT tileRect;
                tileRect.left = x * TILE_SIZE;
                tileRect.top = y * TILE_SIZE;
                tileRect.right = tileRect.left + TILE_SIZE;
                tileRect.bottom = tileRect.top + TILE_SIZE;

                Rectangle( hdc,tileRect.left,tileRect.top,tileRect.right,tileRect.bottom );

                // 원상 복구
                SelectObject( hdc,oldBrush );
                DeleteObject( brush );
            }
        }

        // 격자 그리기
        if ( grid ) {
            HPEN hPen = CreatePen( PS_SOLID,1,RGB( 0,255,0 ) );
            HPEN hOldPen = ( HPEN ) SelectObject( hdc,hPen );

            // 세로선
            for ( int x = 0; x <= MAP_COLS; ++x ) {
                MoveToEx( hdc,x * TILE_SIZE,0,nullptr );
                LineTo( hdc,x * TILE_SIZE,MAP_ROWS * TILE_SIZE );
            }
            // 가로선
            for ( int y = 0; y <= MAP_ROWS; ++y ) {
                MoveToEx( hdc,0,y * TILE_SIZE,nullptr );
                LineTo( hdc,MAP_COLS * TILE_SIZE,y * TILE_SIZE );
            }

            SelectObject( hdc,hOldPen );
            DeleteObject( hPen );
        }
    };

    // -----------------
    // 파일 저장/불러오기
    // -----------------
    void SaveToFileText( const std::string& filename ) {
        std::ofstream outFile( filename );
        if ( !outFile.is_open() ) {
            MessageBox( nullptr,TEXT( "파일 열기 실패" ),TEXT( "에러" ),MB_OK );
            return;
        }

        for ( int y = 0; y < MAP_ROWS; ++y ) {
            for ( int x = 0; x < MAP_COLS; ++x ) {
                outFile << mapData[ y ][ x ];
                if ( x < MAP_COLS - 1 )
                    outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    };

    void LoadFromFileText( const std::string& filename ) {
        std::ifstream inFile( filename );
        if ( !inFile.is_open() ) {
            MessageBox( nullptr,TEXT( "파일 열기 실패" ),TEXT( "에러" ),MB_OK );
            return;
        }

        for ( int y = 0; y < MAP_ROWS; ++y ) {
            for ( int x = 0; x < MAP_COLS; ++x ) {
                char comma;
                inFile >> mapData[ y ][ x ];
                if ( x < MAP_COLS - 1 ) {
                    // CSV에서 콤마를 같이 읽어오기 위함
                    inFile >> comma;
                }
            }
        }
        inFile.close();
    };

private:
    // FHD 기준 1920×1080을 가득 채울 수 있는 크기
    int mapData[ MAP_ROWS ][ MAP_COLS ]; // 맵 정보
    int selectedTile;                // 현재 선택된 타일 종류
    //Camera camera; // 화면 크기: 800x600

};
