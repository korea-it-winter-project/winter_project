#include "pch.h"
#include "Leveleditor.h"
#include <fstream> // ofstream, ifstream ��
#include "ResourceManager.h"
#include "ToolUi.h"
#include "MonsterSpawner.h"
#include "MapData.h"


// ������: Ÿ�� �迭 �ʱ�ȭ �� �⺻ Ÿ�� ����
Leveleditor::Leveleditor() {
    selectedTile = -9;
}

// �Ҹ���
Leveleditor::~Leveleditor() {

}

void Leveleditor::Init() {
    //GET_SINGLE( MonsterSpawner )->Init();
    isActive_ = false;
    isMapEdit_ = false;
    // MapData�� ���� ���Ͽ��� �� �����͸� �ε�
    GET_SINGLE( MapData )->LoadFromFileText( "map.csv" );

    const int( &mapRef )[ MAP_ROWS ][ MAP_COLS ] = GET_SINGLE( MapData )->GetMap();
    ut.RunPathfinding( &mapRef[ 0 ][ 0 ],MAP_ROWS,MAP_COLS );

    for ( int y = 0; y < MAP_ROWS; ++y )
    {
        for ( int x = 0; x < MAP_COLS; ++x )
        {
            // CSV���� ���� Ÿ�� ��
            int tileValue = GET_SINGLE( MapData )->GetTile( x,y );
            if ( tileValue != -9 )
            {
                 //ObjectManager�� ���� Tile ��ü ����
                Tile* tile = GET_SINGLE( ObjectManager )->CreateObject<Tile>();
                // Ÿ���� ��ġ�� �׸��� ��ǥ�̸�, ���� �ȼ� ��ǥ�� TILE_SIZE�� ���� ���
                tile->SetPos( Vector{ static_cast< float >( x ), static_cast< float >( y ) } );
                tile->SetSize( Vector{ static_cast< float >( TILE_SIZE ), static_cast< float >( TILE_SIZE ) } );
                // Tile::Update()���� MapData�� �����Ͽ� auto tile index ���� ���
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
    // Delete Ű�� �� ������ �ʱ�ȭ
    //GET_SINGLE( MonsterSpawner )->Update();

    if ( GetAsyncKeyState( VK_DELETE ) & 0x0001 ) {
        if ( MessageBox( nullptr,TEXT( "�ظ� �����͸� �ʱ�ȭ�Ͻðڽ��ϱ�?" ),TEXT( "����" ),
            MB_YESNO | MB_ICONWARNING ) == IDYES )
        {
            GET_SINGLE( MapData )->Clear( 0 );
            GET_SINGLE( MapData )->SaveToFileText( "map.csv" );
            MessageBox( nullptr,TEXT( "����Ǿ����ϴ�." ),TEXT( "�˸�" ),
                MB_OK | MB_ICONINFORMATION );
        }
    }
    // Ctrl + S�� �� ������ ����
    if ( GET_SINGLE( InputManager )->GetButton( keytype::L_Ctrl ) &&
        GET_SINGLE( InputManager )->GetButton( keytype::S ) )
    {
        GET_SINGLE( MapData )->SaveToFileText( "map.csv" );
        MessageBox( nullptr,TEXT( "����Ǿ����ϴ�." ),TEXT( "�˸�" ),
            MB_OK | MB_ICONINFORMATION );
    }

    // ���콺 ��ǥ ���
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
            case -9: _tile->SetBaseName(L"dirt_"); break;  // ��(��)
            case 1: _tile->SetBaseName(L"stone_"); break; // ��(��)
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
    // �����̽��ٸ� ������ �׸��� ǥ�� on/off ��ȯ
    if ( GET_SINGLE( InputManager )->GetButtonDwon( keytype::SPBAR ) ) {
        grid = !grid;
    }

    // GDI+ Graphics ��ü ����
    //Gdiplus::Graphics graphics( hdc );

    // Ÿ�� �׸���: MAP_ROWS, MAP_COLS�� MapData Ȥ�� ������Ʈ���� ���ǵ� ����� �����մϴ�
    // �׸���(����) �׸���
    if ( grid ) {
        HPEN hPen = CreatePen( PS_SOLID,1,RGB( 0,255,0 ) );
        HPEN hOldPen = ( HPEN ) SelectObject( hdc,hPen );
        // ���μ�
        for ( int x = 0; x <= MAP_COLS; ++x ) {
            MoveToEx( hdc,x * TILE_SIZE,0,nullptr );
            LineTo( hdc,x * TILE_SIZE,MAP_ROWS * TILE_SIZE );
        }
        // ���μ�
        for ( int y = 0; y <= MAP_ROWS; ++y ) {
            MoveToEx( hdc,0,y * TILE_SIZE,nullptr );
            LineTo( hdc,MAP_COLS * TILE_SIZE,y * TILE_SIZE );
        }
        SelectObject( hdc,hOldPen );
        DeleteObject( hPen );
    }
}

// ���� Leveleditor���� Save/Load ����� ���� �����ϰ� �ʹٸ� �Ʒ��� �����ϼ���.
// ���� MapData�� ���� ������� ����Ѵٸ�, �� �Լ����� �ܼ��� MapData�� �ش� �Լ��� ȣ���ϵ��� �� �� �ֽ��ϴ�.

void Leveleditor::SaveToFileText( const std::string& filename ) {
    // ��: MapData�� SaveToFileText �Լ��� ȣ��
    GET_SINGLE( MapData )->SaveToFileText( filename );
}

void Leveleditor::LoadFromFileText( const std::string& filename ) {
    // ��: MapData�� LoadFromFileText �Լ��� ȣ��
    GET_SINGLE( MapData )->LoadFromFileText( filename );
}
