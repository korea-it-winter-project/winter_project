#pragma once
#include "pch.h"
#include <filesystem>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>  // 스마트 포인터 사용을 위한 헤더

class ResourceManager
{
    DECLARE_SINGLE( ResourceManager );

public:
    ~ResourceManager()
    {
        _tileImages.clear();
        // _imageMap은 _tileImages와 같은 포인터를 관리하므로 별도 해제가 필요 없음.
        _imageMap.clear();
    }

    // 폴더 내의 이미지를 로드하여 카테고리별 및 파일이름별로 저장합니다.
    void LoadImagesIntoManager( const std::wstring& folderPath )
    {
        for ( const auto& entry : std::filesystem::directory_iterator( folderPath ) )
        {
            if ( !entry.is_regular_file() )
                continue;

            auto ext = entry.path().extension().wstring();
            if ( ext == L".png" || ext == L".jpg" || ext == L".bmp" )
            {
                std::wstring filename = entry.path().filename().wstring();
                // Gdiplus::Bitmap* 를 std::shared_ptr로 감싸서 생성합니다.
                std::shared_ptr<Gdiplus::Bitmap> pBitmap(
                    Gdiplus::Bitmap::FromFile(entry.path().c_str())
                );
                if ( pBitmap && pBitmap->GetLastStatus() == Gdiplus::Ok )
                {
                    // 파일 이름을 키로 _imageMap에 저장합니다.
                    _imageMap[ filename ] = pBitmap;

                    // 파일 이름에 따라 카테고리 지정하여 _tileImages에 저장합니다.
                    if ( filename.find( L"projectile_" ) != std::wstring::npos )
                    {
                        _tileImages[ L"projectile" ].push_back( pBitmap );
                        std::wcout << L"Loaded Projectile: " << filename << std::endl;
                    }
                    else if ( filename.find( L"stone_" ) != std::wstring::npos )
                    {
                        _tileImages[ L"stone" ].push_back( pBitmap );
                        std::wcout << L"Loaded Stone: " << filename << std::endl;
                    }
                    else if ( filename.find( L"dirt_" ) != std::wstring::npos )
                    {
                        _tileImages[ L"dirt" ].push_back( pBitmap );
                        std::wcout << L"Loaded Dirt: " << filename << std::endl;
                    }
                    else
                    {
                        // 기본 카테고리 (예: "default")에 저장
                        _tileImages[ L"default" ].push_back( pBitmap );
                        std::wcout << L"Loaded Default: " << filename << std::endl;
                    }
                }
                else
                {
                    std::wcerr << L"Failed: " << entry.path().c_str() << std::endl;
                }
            }
        }
    }

    // 특정 카테고리의 이미지 목록을 가져옵니다.
    const std::vector<std::shared_ptr<Gdiplus::Bitmap>>& GetImagesByCategory(const std::wstring& category) const
    {
        auto it = _tileImages.find( category );
        if ( it != _tileImages.end() )
            return it->second;

        static std::vector<std::shared_ptr<Gdiplus::Bitmap>> empty;
        return empty;
    }

    // 파일 이름으로 이미지를 검색합니다.
    std::shared_ptr<Gdiplus::Bitmap> FindImage(const std::wstring& filename)
    {
        auto it = _imageMap.find( filename );
        if ( it == _imageMap.end() )
            return nullptr;
        return it->second;
    }

    void DrawRotatedImage(Gdiplus::Graphics& g, std::shared_ptr<Gdiplus::Bitmap> pImage, float x, float y, float angle)
    {
        if ( !pImage ) return;

        // 1) 이미지의 폭과 높이
        float width = static_cast< float >( pImage->GetWidth() );
        float height = static_cast< float >( pImage->GetHeight() );

        // 2) 회전 중심 (이미지의 중심)
        float cx = x + width / 2.0f;
        float cy = y + height / 2.0f;

        // 3) 변환 매트릭스 생성 (중심 이동 -> 회전 -> 원점 복귀)
        Gdiplus::Matrix mat;
        mat.Translate( cx,cy );
        mat.Rotate( angle );
        mat.Translate( -cx,-cy );

        // 4) Graphics 객체에 매트릭스 적용
        g.SetTransform( &mat );

        g.DrawImage(pImage.get(), x, y, width, height);
        g.ResetTransform();
    }

    void DrawImageWithAlpha(Gdiplus::Graphics& g, std::shared_ptr<Gdiplus::Bitmap> pImage,
        float x, float y, float width, float height, float alpha)
    {
        if ( !pImage ) return;

        // RGBA 순서의 ColorMatrix (마지막 행/열은 보정용)
        Gdiplus::ColorMatrix colorMatrix =
        {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, alpha, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        // ImageAttributes에 ColorMatrix 적용
        Gdiplus::ImageAttributes imgAttr;
        imgAttr.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

        // 이미지 그리기
        g.DrawImage(
            pImage.get(),
            Gdiplus::RectF( x,y,width,height ),
            0.0f, 0.0f,
            static_cast< float >( pImage->GetWidth() ),
            static_cast< float >( pImage->GetHeight() ),
            Gdiplus::UnitPixel,
            &imgAttr
        );
    }

private:
    // 카테고리별 이미지 목록: std::shared_ptr 사용
    std::unordered_map<std::wstring, std::vector<std::shared_ptr<Gdiplus::Bitmap>>> _tileImages;
    // 파일 이름으로 이미지 검색용
    std::unordered_map<std::wstring, std::shared_ptr<Gdiplus::Bitmap>> _imageMap;
};
