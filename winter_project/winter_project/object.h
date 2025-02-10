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
};


class Object {
public:
    Object(ObjectType objType) : _type(objType) {}
    virtual ~Object() {}

    virtual void Init() {};
    virtual void Update() {

    };
    virtual void Render(HDC hdc) {

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

protected:
    ObjectType _type = ObjectType::None; // ������Ʈ Ÿ��
    Stat _stat = {};                     // ���� ����
    Vector _pos = {};                    // ��ġ
    Vector _size = { 0.0f, 0.0f };       // ũ��
    Collider* _collider;
    std::shared_ptr<Gdiplus::Bitmap> pBmp;
};

