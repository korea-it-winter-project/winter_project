#pragma once
#include "pch.h"
#include <string>
#include <fstream>
#include <cstdlib>    // rand() 사용 시 필요

/// 맵 관련 고정 상수
static const int TILE_SIZE = 24;   // 한 타일의 픽셀 크기
static const int MAP_COLS = 1000 / TILE_SIZE; ///< 맵의 가로 칸 수
static const int MAP_ROWS = 600 / TILE_SIZE; ///< 맵의 세로 칸 수


class MapData
{
    DECLARE_SINGLE( MapData );
public:
    // 맵 데이터와 인덱스 모두 초기화 (타일 값는 value, 인덱스는 -1로 초기화)
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

    // 맵 범위 체크 후 타일 값 설정 및 인접 타일의 오토 인덱스 재계산
    void SetTile( int x,int y,int tileValue ) {
        if ( x < 0 || x >= MAP_COLS ) return;
        if ( y < 0 || y >= MAP_ROWS ) return;
        if ( _map[ y ][ x ] == tileValue )return;
        _map[ y ][ x ] = tileValue;
        // 타일이 변경되었으므로 해당 타일과 인접 타일의 오토 타일 인덱스를 갱신합니다.
        ComputeAutoTileIndexAt( x,y );
        if ( x > 0 )              ComputeAutoTileIndexAt( x - 1,y );
        if ( x < MAP_COLS - 1 )   ComputeAutoTileIndexAt( x + 1,y );
        if ( y > 0 )              ComputeAutoTileIndexAt( x,y - 1 );
        if ( y < MAP_ROWS - 1 )   ComputeAutoTileIndexAt( x,y + 1 );
    };

    // 현재 타일 값 반환
    int GetTile( int x,int y ) const {
        if ( x < 0 || x >= MAP_COLS ) return 0;
        if ( y < 0 || y >= MAP_ROWS ) return 0;
        return _map[ y ][ x ];
    };

    // CSV 텍스트 파일로 저장 (타일 값만 저장; 오토 인덱스는 동적 계산)
    void SaveToFileText( const std::string& filename ) {
        std::ofstream outFile( filename );
        if ( !outFile.is_open() ) {
            MessageBox( nullptr,TEXT( "파일 열기 실패" ),TEXT( "에러" ),MB_OK );
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

    // CSV 텍스트 파일에서 불러온 후 전체 오토 타일 인덱스 계산
    void LoadFromFileText( const std::string& filename ) {
        std::ifstream inFile( filename );
        if ( !inFile.is_open() ) {
            MessageBox( nullptr,TEXT( "파일 열기 실패" ),TEXT( "에러" ),MB_OK );
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

        // 로드 후 전체 타일에 대해 오토 타일 인덱스 계산
        ComputeAllAutoTileIndices();
    };

    // 저장된 오토 타일 인덱스를 반환
    int GetAutoTileIndex( int x,int y ) const {
        if ( x < 0 || x >= MAP_COLS ) return 0;
        if ( y < 0 || y >= MAP_ROWS ) return 0;
        return _autoTileIndices[ y ][ x ];
    };

private:
    int _map[ MAP_ROWS ][ MAP_COLS ];            // 각 타일의 값 (타일 종류)
    int _autoTileIndices[ MAP_ROWS ][ MAP_COLS ];  // 계산된 오토 타일 인덱스

    // 주어진 범위 내에서 start부터 count 범위 내의 인덱스를 랜덤 선택하는 보조 함수
    int PickRandomIndex( int start,int count )
    {
        return start + ( rand() % count );
    }

    // 주어진 좌표 (x,y)의 타일과 인접한 타일이 같은지 여부를 비트마스크로 반환  
    // 각 비트(0:위, 1:오른쪽, 2:아래, 3:왼쪽)가 1이면 해당 방향의 타일이 현재 타일과 동일함
    int GetTileMaskSame( int x,int y ) const {
        int currentTile = GetTile( x,y );
        if ( currentTile == 0 )
            return 0;

        int mask = 0;
        // 위쪽 (비트 0)
        if ( y > 0 && GetTile( x,y - 1 ) == currentTile )
            mask |= ( 1 << 0 );
        // 오른쪽 (비트 1)
        if ( x < MAP_COLS - 1 && GetTile( x + 1,y ) == currentTile )
            mask |= ( 1 << 1 );
        // 아래쪽 (비트 2)
        if ( y < MAP_ROWS - 1 && GetTile( x,y + 1 ) == currentTile )
            mask |= ( 1 << 2 );
        // 왼쪽 (비트 3)
        if ( x > 0 && GetTile( x - 1,y ) == currentTile )
            mask |= ( 1 << 3 );

        return mask;
    }

    // (x,y) 좌표의 타일에 대해 오토 타일 인덱스를 계산하고 저장  
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

        // 디버그 출력
        /*std::cout << "[x=" << x << ",y=" << y
            << "] upE=" << upEmpty << " rightE=" << rightEmpty
            << " downE=" << downEmpty << " leftE=" << leftEmpty << std::endl;*/

        int autoIndex = 0;
        // 아래만 비어있는 경우 → 원래 0~2 범위 중 랜덤 선택
        if ( !upEmpty && !rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 0, 3 );
        }
        // 4면 모두 비어있는 경우 → 3~5
        else if ( upEmpty && rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 3, 3 );
        }
        // 왼쪽 아래쪽 비어있는 경우 → 인덱스 6
        else if ( !upEmpty && !rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = 6;
        }
        // 왼쪽 오른쪽 비어있는 경우 → 7~9
        else if ( !upEmpty && rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 7, 3 );
        }
        // 왼쪽 위쪽 비어있는 경우 → 인덱스 10
        else if ( upEmpty && !rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = 10;
        }
        // 왼쪽만 비어있는 경우 → 11~13
        else if ( !upEmpty && !rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 11, 3 );
        }
        // 오른쪽 아래쪽 비어있는 경우 → 인덱스 14
        else if ( !upEmpty && rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = 14;
        }
        // 오른쪽 위쪽 비어있는 경우 → 인덱스 15
        else if ( upEmpty && rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = 15;
        }
        // 오른쪽만 비어있는 경우 → 16~18
        else if ( !upEmpty && rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 16, 3 );
        }
        // 위쪽 아래쪽 비어있는 경우 → 19~21
        else if ( upEmpty && !rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 19, 3 );
        }
        // 위쪽만 비어있는 경우 → 22~24
        else if ( upEmpty && !rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 22, 3 );
        }
        // 아래만 안 비어있는 경우 → 25~27
        else if ( upEmpty && rightEmpty && !downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 25, 3 );
        }
        // 왼쪽만 안 비어있는 경우 → 28~30
        else if ( upEmpty && rightEmpty && downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 28, 3 );
        }
        // 오른쪽만 안 비어있는 경우 → 31~33
        else if ( upEmpty && !rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 31, 3 );
        }
        // 위쪽만 안 비어있는 경우 → 34~36
        else if ( !upEmpty && rightEmpty && downEmpty && leftEmpty )
        {
            autoIndex = PickRandomIndex( 34, 3 );
        }
        // 4면 모두 안 비어있는 경우 → 37~39
        else if ( !upEmpty && !rightEmpty && !downEmpty && !leftEmpty )
        {
            autoIndex = PickRandomIndex( 37,3 ); 
        }
        else {
            autoIndex = 0;
        }
        _autoTileIndices[ y ][ x ] = autoIndex;
    }

    // 전체 맵에 대해 오토 타일 인덱스 계산 (보통 CSV 파일 로드 후 호출)
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
