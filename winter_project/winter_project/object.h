#pragma once
//#error "object.h ���Ե�"

#include "pch.h"
#include "Collider.h"
//#include "Vector.h"
struct Stat {
    INT32 Hp = 0;
    UINT32 MaxHP = 0; // ������ �� �Ѿ�� ��ȣ ���� ������ ����
    float speed = 0.0f;
    UINT32 damage = 0;
    /*
    ���� �� ���� ������ ���� ���� ���ϴ� ��� ����
    */
};

enum class ObjectType {
    None,
    Player,
    Monster,
    Projectile,
    Block,
    Tower,
    Ui
};


class Object {
public:
    Object(ObjectType objType) : _type(objType) {}
    virtual ~Object() {}

    virtual void Init() {};
    virtual void Update(float dTime) {

    };
    virtual void Render(HDC hdc) {
        if (_collider) {
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // ������ �׵θ�
            HGDIOBJ oldPen = SelectObject(hdc, hPen);
            HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // ���� ����
            HGDIOBJ oldBrush = SelectObject(hdc, hBrush);
            Rectangle(hdc, _pos.x - _collider->_size.x, _pos.y - _collider->_size.y,
                _pos.x + _collider->_size.x, _pos.y + _collider->_size.y);
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            SelectObject(hdc, oldBrush);
        }
    };

    // ������Ʈ Ÿ�� ��ȯ
    ObjectType GetObjectType() const { return _type; }

    // ������Ʈ ��ġ ���� �Լ�
    Vector GetPos() const { return _pos; }
    void SetPos(Vector pos) { _pos = pos; }

    // ������Ʈ ũ�� ���� �� ��������
    Vector GetSize() const { return _size; }
    void SetSize(Vector size) { _size = size; }

    void SetBmp(std::shared_ptr<Gdiplus::Bitmap> _pBmp) { pBmp = _pBmp; }
    std::shared_ptr<Gdiplus::Bitmap> GetBmp() { return pBmp; }
    int GetLayer() const { return _layer; }
    void SetLayer(int layer) { _layer = layer; }

    // ü�� ���� �Լ�
    void TakeDamage(UINT32 dmg) {
        if (_stat.Hp > (INT32)dmg)
            _stat.Hp -= dmg;
        else
            _stat.Hp = 0;
    }

    bool IsDead() const { return _stat.Hp <= 0; }

    void SetCollider(Collider* collider) { _collider = collider; }
    Collider* GetCollider() const { return _collider; }


    virtual void OnCollision(Collider* other) {

    }
    HBITMAP ConvertToHBITMAP(std::shared_ptr<Gdiplus::Bitmap> gdiBitmap, COLORREF background = RGB(255, 255, 255)) {
        if (!gdiBitmap) return nullptr;

        HBITMAP hBitmap = nullptr;
        gdiBitmap->GetHBITMAP(background, &hBitmap); // GDI+ Bitmap�� HBITMAP���� ��ȯ
        return hBitmap;
    }
protected:
    ObjectType _type = ObjectType::None; // ������Ʈ Ÿ��
    Stat _stat = {};                     // ���� ����
    Vector _pos = {};                    // ��ġ
    Vector _size = { 0.0f, 0.0f };       // ũ��
    Collider* _collider;
    std::shared_ptr<Gdiplus::Bitmap> pBmp;
    int _layer = 0;
};

