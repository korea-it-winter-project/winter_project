#pragma once

#include "Scene.h"
#include "InputManager.h"
#include "MapData.h"
#include "Tile.h"
#include <string>
#include <fstream>

class Leveleditor : public Scene {
    //DECLARE_SINGLE(Leveleditor);
public:
    // 생성자와 소멸자 선언
    Leveleditor();
    virtual ~Leveleditor() override;

    // Scene 인터페이스 재정의
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render( HDC hdc ) override;

    // 파일 저장 및 로드 함수 (필요시 구현)
    void SaveToFileText( const std::string& filename );
    void LoadFromFileText( const std::string& filename );

private:
    int selectedTile;                // 현재 선택된 타일 종류
    bool grid = true;                // 그리드 표시 on/off
    bool isActive_;
    bool isMapEdit_;
    
};
