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
#include <memory>  // ����Ʈ ������ ����� ���� ���

class ResourceManager
{
    DECLARE_SINGLE( ResourceManager );

public:
    ~ResourceManager()
    {
        _tileImages.clear();
        // _imageMap�� _tileImages�� ���� �����͸� �����ϹǷ� ���� ������ �ʿ� ����.
        _imageMap.clear();
    }

    // ���� ���� �̹����� �ε��Ͽ� ī�װ��� �� �����̸����� �����մϴ�.
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
                // Gdiplus::Bitmap* �� std::shared_ptr�� ���μ� �����մϴ�.
                std::shared_ptr<Gdiplus::Bitmap> pBitmap(
                    Gdiplus::Bitmap::FromFile(entry.path().c_str())
                );
                if ( pBitmap && pBitmap->GetLastStatus() == Gdiplus::Ok )
                {
                    // ���� �̸��� Ű�� _imageMap�� �����մϴ�.
                    _imageMap[ filename ] = pBitmap;

                    // ���� �̸��� ���� ī�װ� �����Ͽ� _tileImages�� �����մϴ�.
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
                        // �⺻ ī�װ� (��: "default")�� ����
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

    // Ư�� ī�װ��� �̹��� ����� �����ɴϴ�.
    const std::vector<std::shared_ptr<Gdiplus::Bitmap>>& GetImagesByCategory(const std::wstring& category) const
    {
        auto it = _tileImages.find( category );
        if ( it != _tileImages.end() )
            return it->second;

        static std::vector<std::shared_ptr<Gdiplus::Bitmap>> empty;
        return empty;
    }

    // ���� �̸����� �̹����� �˻��մϴ�.
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

        // 1) �̹����� ���� ����
        float width = static_cast< float >( pImage->GetWidth() );
        float height = static_cast< float >( pImage->GetHeight() );

        // 2) ȸ�� �߽� (�̹����� �߽�)
        float cx = x + width / 2.0f;
        float cy = y + height / 2.0f;

        // 3) ��ȯ ��Ʈ���� ���� (�߽� �̵� -> ȸ�� -> ���� ����)
        Gdiplus::Matrix mat;
        mat.Translate( cx,cy );
        mat.Rotate( angle );
        mat.Translate( -cx,-cy );

        // 4) Graphics ��ü�� ��Ʈ���� ����
        g.SetTransform( &mat );

        g.DrawImage(pImage.get(), x, y, width, height);
        g.ResetTransform();
    }

    void DrawImageWithAlpha(Gdiplus::Graphics& g, std::shared_ptr<Gdiplus::Bitmap> pImage,
        float x, float y, float width, float height, float alpha)
    {
        if ( !pImage ) return;

        // RGBA ������ ColorMatrix (������ ��/���� ������)
        Gdiplus::ColorMatrix colorMatrix =
        {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, alpha, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        // ImageAttributes�� ColorMatrix ����
        Gdiplus::ImageAttributes imgAttr;
        imgAttr.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

        // �̹��� �׸���
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
    // ī�װ��� �̹��� ���: std::shared_ptr ���
    std::unordered_map<std::wstring, std::vector<std::shared_ptr<Gdiplus::Bitmap>>> _tileImages;
    // ���� �̸����� �̹��� �˻���
    std::unordered_map<std::wstring, std::shared_ptr<Gdiplus::Bitmap>> _imageMap;
};
