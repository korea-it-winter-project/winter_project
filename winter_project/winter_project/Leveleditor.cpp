#include "pch.h"
#include "Leveleditor.h"
#include <fstream> // ofstream, ifstream 등
#include "ResourceManager.h"
#include "ToolUi.h"
#include "MonsterSpawner.h"
#include "MapData.h"


// 생성자: 타일 배열 초기화 및 기본 타일 설정
Leveleditor::Leveleditor() {
    selectedTile = -9;
}

// 소멸자
Leveleditor::~Leveleditor() {

}

void Leveleditor::Init() {
    //GET_SINGLE( MonsterSpawner )->Init();
    isActive_ = false;
    isMapEdit_ = false;
    // MapData를 통해 파일에서 맵 데이터를 로드
    GET_SINGLE( MapData )->LoadFromFileText( "map.csv" );

    const int( &mapRef )[ MAP_ROWS ][ MAP_COLS ] = GET_SINGLE( MapData )->GetMap();
    ut.RunPathfinding( &mapRef[ 0 ][ 0 ],MAP_ROWS,MAP_COLS );

    for ( int y = 0; y < MAP_ROWS; ++y )
    {
        for ( int x = 0; x < MAP_COLS; ++x )
        {
            // CSV에서 읽은 타일 값
            int tileValue = GET_SINGLE( MapData )->GetTile( x,y );
            if ( tileValue != -9 )
            {
                 //ObjectManager를 통해 Tile 객체 생성
                Tile* tile = GET_SINGLE( ObjectManager )->CreateObject<Tile>();
                // 타일의 위치는 그리드 좌표이며, 실제 픽셀 좌표는 TILE_SIZE를 곱해 계산
                tile->SetPos( Vector{ static_cast< float >( x ), static_cast< float >( y ) } );
                tile->SetSize( Vector{ static_cast< float >( TILE_SIZE ), static_cast< float >( TILE_SIZE ) } );
                // Tile::Update()에서 MapData를 참조하여 auto tile index 등을 계산
                GET_SINGLE( ObjectManager )->Add( tile );
            }
        }
    }
    //path = ut.GetPath();
    //pathLength = ut.GetPathLength();
    //GET_SINGLE( MonsterSpawner )->Init( path,pathLength-1 );
    //GET_SINGLE( MonsterSpawner )->SpawnMonster();
}

void Leveleditor::Update() {
    //GET_SINGLE( MonsterSpawner )->Update();
    // Delete 키로 맵 데이터 초기화
    //GET_SINGLE( MonsterSpawner )->Update();

    if ( GetAsyncKeyState( VK_DELETE ) & 0x0001 ) {
        if ( MessageBox( nullptr,TEXT( "※맵 데이터를 초기화하시겠습니까?" ),TEXT( "주의" ),
            MB_YESNO | MB_ICONWARNING ) == IDYES )
        {
            GET_SINGLE( MapData )->Clear( 0 );
            GET_SINGLE( MapData )->SaveToFileText( "map.csv" );
            MessageBox( nullptr,TEXT( "저장되었습니다." ),TEXT( "알림" ),
                MB_OK | MB_ICONINFORMATION );
        }
    }
    // Ctrl + S로 맵 데이터 저장
    if ( GET_SINGLE( InputManager )->GetButton( keytype::L_Ctrl ) &&
        GET_SINGLE( InputManager )->GetButton( keytype::S ) )
    {
        GET_SINGLE( MapData )->SaveToFileText( "map.csv" );
        MessageBox( nullptr,TEXT( "저장되었습니다." ),TEXT( "알림" ),
            MB_OK | MB_ICONINFORMATION );
    }

    // 마우스 좌표 얻기
    POINT pt;
    GetCursorPos( &pt );
    pt = GET_SINGLE( InputManager )->GetMousePos();

    RECT tRect = GET_SINGLE(ToolUi)->GetRect();
    if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_Ctrl)) isActive_ = !isActive_;
    if (isActive_) {
        if (GET_SINGLE(InputManager)->CheckMousePoint(tRect)) {
            return;
        }
    }
    if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::BACKSP)) isMapEdit_ = !isMapEdit_;
    if (isMapEdit_) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            int tileX = pt.x / TILE_SIZE;
            int tileY = pt.y / TILE_SIZE;
            if (GET_SINGLE(MapData)->GetTile(tileX, tileY)) return;
            GET_SINGLE(MapData)->SetTile(tileX, tileY, selectedTile);
            if (GET_SINGLE(MapData)->GetTile(tileX, tileY) == 0) return;


            printf("%d", GET_SINGLE(MapData)->GetTile(tileX, tileY));
            Tile* _tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
            _tile->SetPos(Vector{ (float)tileX,(float)tileY });
            _tile->SetSize(Vector{ TILE_SIZE, TILE_SIZE });
            //_tile->SetBmp(pBmp);
            switch (GET_SINGLE(MapData)->GetTile(tileX, tileY)) {
            case -9: _tile->SetBaseName(L"dirt_"); break;  // 흙(벽)
            case 1: _tile->SetBaseName(L"stone_"); break; // 돌(길)
            default: break;
            }
            GET_SINGLE(ObjectManager)->Add(_tile);

        }
    }
    //if ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) {
    //    int tileX = pt.x / TILE_SIZE;
    //    int tileY = pt.y / TILE_SIZE;
    //    if ( GET_SINGLE( MapData )->GetTile( tileX,tileY ) ) return;
    //    GET_SINGLE( MapData )->SetTile( tileX,tileY,selectedTile );
    //    if (GET_SINGLE(MapData)->GetTile(tileX, tileY) == 0) return;

    //    printf( "%d",GET_SINGLE( MapData )->GetTile( tileX,tileY ) );

    //    Tile* _tile = GET_SINGLE( ObjectManager )->CreateObject<Tile>();
    //    _tile->SetPos( Vector{ ( float ) tileX,( float ) tileY } );
    //    _tile->SetSize( Vector{ TILE_SIZE, TILE_SIZE } );
    //    //_tile->SetBmp(pBmp);
    //    GET_SINGLE( ObjectManager )->Add( _tile );
    //}
    switch (GET_SINGLE(ToolUi)->GetNum()) {
    case 1:
        selectedTile = -9;
        break;
    case 2:
        selectedTile = 1;
        break;
    case 10:
        selectedTile = 10;
        break;
    case 11:
        GET_SINGLE(MapData)->Clear();
        break;
    }
}

void Leveleditor::Render( HDC hdc ) {
    // 스페이스바를 누르면 그리드 표시 on/off 전환
    if ( GET_SINGLE( InputManager )->GetButtonDwon( keytype::SPBAR ) ) {
        grid = !grid;
    }

    // GDI+ Graphics 객체 생성
    //Gdiplus::Graphics graphics( hdc );

    // 타일 그리기: MAP_ROWS, MAP_COLS는 MapData 혹은 프로젝트에서 정의된 상수로 가정합니다
    // 그리드(격자) 그리기
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
}

// 만약 Leveleditor에서 Save/Load 기능을 직접 구현하고 싶다면 아래에 구현하세요.
// 현재 MapData가 파일 입출력을 담당한다면, 이 함수들은 단순히 MapData의 해당 함수를 호출하도록 할 수 있습니다.

void Leveleditor::SaveToFileText( const std::string& filename ) {
    // 예: MapData의 SaveToFileText 함수를 호출
    GET_SINGLE( MapData )->SaveToFileText( filename );
}

void Leveleditor::LoadFromFileText( const std::string& filename ) {
    // 예: MapData의 LoadFromFileText 함수를 호출
    GET_SINGLE( MapData )->LoadFromFileText( filename );
}
