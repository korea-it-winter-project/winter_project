#pragma once
#include "pch.h"
#include <string>
#include <fstream>
#include <cstdlib>    // rand() ��� �� �ʿ�

/// �� ���� ���� ���
static const int TILE_SIZE = 24;   // �� Ÿ���� �ȼ� ũ��
static const int MAP_COLS = 1000 / TILE_SIZE; ///< ���� ���� ĭ ��
static const int MAP_ROWS = 600 / TILE_SIZE; ///< ���� ���� ĭ ��


class MapData
{
    DECLARE_SINGLE( MapData );
public:
    // �� �����Ϳ� �ε��� ��� �ʱ�ȭ (Ÿ�� ���� value, �ε����� -1�� �ʱ�ȭ)
    void Clear( int value = 0 ) {
        for ( int y = 0; y < MAP_ROWS; ++y )
        {
            for ( int x = 0; x < MAP_ROWS; ++x )
            {
                _map[ y ][ x ] = value;
                _autoTileIndices[ y ][ x ] = -1;
            }
        }

        GET_SINGLE(ObjectManager)->clear();
        
    };

    // �� ���� üũ �� Ÿ�� �� ���� �� ���� Ÿ���� ���� �ε��� ����
    void SetTile( int x,int y,int tileValue ) {
        if ( x < 0 || x >= MAP_COLS ) return;
        if ( y < 0 || y >= MAP_ROWS ) return;
        if ( _map[ y ][ x ] == tileValue )return;
        _map[ y ][ x ] = tileValue;
        // Ÿ���� ����Ǿ����Ƿ� �ش� Ÿ�ϰ� ���� Ÿ���� ���� Ÿ�� �ε����� �����մϴ�.
        ComputeAutoTileIndexAt( x,y );
        if ( x > 0 )              ComputeAutoTileIndexAt( x - 1,y );
        if ( x < MAP_COLS - 1 )   ComputeAutoTileIndexAt( x + 1,y );
        if ( y > 0 )              ComputeAutoTileIndexAt( x,y - 1 );
        if ( y < MAP_ROWS - 1 )   ComputeAutoTileIndexAt( x,y + 1 );
    };

    // ���� Ÿ�� �� ��ȯ
    int GetTile( int x,int y ) const {
        if ( x < 0 || x >= MAP_COLS ) return 0;
        if ( y < 0 || y >= MAP_ROWS ) return 0;
        return _map[ y ][ x ];
    };

    // CSV �ؽ�Ʈ ���Ϸ� ���� (Ÿ�� ���� ����; ���� �ε����� ���� ���)
    void SaveToFileText( const std::string& filename ) {
        std::ofstream outFile( filename );
        if ( !outFile.is_open() ) {
            MessageBox( nullptr,TEXT( "���� ���� ����" ),TEXT( "����" ),MB_OK );
            return;
        }

        for ( int y = 0; y < MAP_ROWS; ++y )
        {
            for ( int x = 0; x < MAP_COLS; ++x )
            {
                outFile << _map[ y ][ x ];
                if ( x < MAP_COLS - 1 )
                    outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    };

    // CSV �ؽ�Ʈ ���Ͽ��� �ҷ��� �� ��ü ���� Ÿ�� �ε��� ���
    void LoadFromFileText( const std::string& filename ) {
        std::ifstream inFile( filename );
        if ( !inFile.is_open() ) {
            MessageBox( nullptr,TEXT( "���� ���� ����" ),TEXT( "����" ),MB_OK );
            return;
        }

        for ( int y = 0; y < MAP_ROWS; ++y )
        {
            for ( int x = 0; x < MAP_COLS; ++x )
            {
                char comma;
                inFile >> _map[ y ][ x ];
                if ( x < MAP_COLS - 1 )
                    inFile >> comma;
            }
        }
        inFile.close();

        // �ε� �� ��ü Ÿ�Ͽ� ���� ���� Ÿ�� �ε��� ���
        ComputeAllAutoTileIndices();
    };

    // ����� ���� Ÿ�� �ε����� ��ȯ
    int GetAutoTileIndex( int x,int y ) const {
        if ( x < 0 || x >= MAP_COLS ) return 0;
        if ( y < 0 || y >= MAP_ROWS ) return 0;
        return _autoTileIndices[ y ][ x ];
    };

private:
    int _map[ MAP_ROWS ][ MAP_COLS ];            // �� Ÿ���� �� (Ÿ�� ����)
    int _autoTileIndices[ MAP_ROWS ][ MAP_COLS ];  // ���� ���� Ÿ�� �ε���

    // �־��� ���� ������ start���� count ���� ���� �ε����� ���� �����ϴ� ���� �Լ�
    int PickRandomIndex( int start,int count )
    {
        return start + ( rand() % count );
    }

    // �־��� ��ǥ (x,y)�� Ÿ�ϰ� ������ Ÿ���� ������ ���θ� ��Ʈ����ũ�� ��ȯ  
    // �� ��Ʈ(0:��, 1:������, 2:�Ʒ�, 3:����)�� 1�̸� �ش� ������ Ÿ���� ���� Ÿ�ϰ� ������
    int GetTileMaskSame( int x,int y ) const {
        int currentTile = GetTile( x,y );
        if ( currentTile == 0 )
            return 0;

        int mask = 0;
        // ���� (��Ʈ 0)
        if ( y > 0 && GetTile( x,y - 1 ) == currentTile )
            mask |= ( 1 << 0 );
        // ������ (��Ʈ 1)
        if ( x < MAP_COLS - 1 && GetTile( x + 1,y ) == currentTile )
            mask |= ( 1 << 1 );
        // �Ʒ��� (��Ʈ 2)
        if ( y < MAP_ROWS - 1 && GetTile( x,y + 1 ) == currentTile )
            mask |= ( 1 << 2 );
        // ���� (��Ʈ 3)
        if ( x > 0 && GetTile( x - 1,y ) == currentTile )
            mask |= ( 1 << 3 );

        return mask;
    }

    // (x,y) ��ǥ�� Ÿ�Ͽ� ���� ���� Ÿ�� �ε����� ����ϰ� ����  
    void ComputeAutoTileIndexAt( int x,int y ) {
        if ( GetTile( x,y ) == 0 ) {
            _autoTileIndices[ y ][ x ] = 0;
            return;
        }

        int mask = GetTileMaskSame( x,y );
        bool upEmpty = !( mask & ( 1 << 0 ) );
        bool rightEmpty = !( mask & ( 1 << 1 ) );
        bool downEmpty = !( mask & ( 1 << 2 ) );
        bool leftEmpty = !( mask & ( 1 << 3 ) );

        // ����� ���
        /*std::cout << "[x=" << x << ",y=" << y
            << "] upE=" << upEmpty << " rightE=" << rightEmpty
            << " downE=" << downEmpty << " leftE=" << leftEmpty << std::endl;*/

        int autoIndex = 0;
        // �Ʒ��� ����ִ� ��� �� ���� 0~2 ���� �� ���� ����
        if ( !upEmpty && !rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 0, 3 );
        }
        // 4�� ��� ����ִ� ��� �� 3~5
        else if ( upEmpty && rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 3, 3 );
        }
        // ���� �Ʒ��� ����ִ� ��� �� �ε��� 6
        else if ( !upEmpty && !rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = 6;
        }
        // ���� ������ ����ִ� ��� �� 7~9
        else if ( !upEmpty && rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 7, 3 );
        }
        // ���� ���� ����ִ� ��� �� �ε��� 10
        else if ( upEmpty && !rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = 10;
        }
        // ���ʸ� ����ִ� ��� �� 11~13
        else if ( !upEmpty && !rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 11, 3 );
        }
        // ������ �Ʒ��� ����ִ� ��� �� �ε��� 14
        else if ( !upEmpty && rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = 14;
        }
        // ������ ���� ����ִ� ��� �� �ε��� 15
        else if ( upEmpty && rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = 15;
        }
        // �����ʸ� ����ִ� ��� �� 16~18
        else if ( !upEmpty && rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 16, 3 );
        }
        // ���� �Ʒ��� ����ִ� ��� �� 19~21
        else if ( upEmpty && !rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 19, 3 );
        }
        // ���ʸ� ����ִ� ��� �� 22~24
        else if ( upEmpty && !rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 22, 3 );
        }
        // �Ʒ��� �� ����ִ� ��� �� 25~27
        else if ( upEmpty && rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 25, 3 );
        }
        // ���ʸ� �� ����ִ� ��� �� 28~30
        else if ( upEmpty && rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 28, 3 );
        }
        // �����ʸ� �� ����ִ� ��� �� 31~33
        else if ( upEmpty && !rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 31, 3 );
        }
        // ���ʸ� �� ����ִ� ��� �� 34~36
        else if ( !upEmpty && rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 34, 3 );
        }
        // 4�� ��� �� ����ִ� ��� �� 37~39
        else if ( !upEmpty && !rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 37,3 ); 
        }
        else {
            autoIndex = 0;
        }
        _autoTileIndices[ y ][ x ] = autoIndex;
    }

    // ��ü �ʿ� ���� ���� Ÿ�� �ε��� ��� (���� CSV ���� �ε� �� ȣ��)
    void ComputeAllAutoTileIndices() {
        for ( int y = 0; y < MAP_ROWS; ++y )
        {
            for ( int x = 0; x < MAP_COLS; ++x )
            {
                ComputeAutoTileIndexAt( x,y );
            }
        }
    }
};
