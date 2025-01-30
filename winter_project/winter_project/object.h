#pragma once

#include "pch.h"

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
};

class Object {
public:
    Object(ObjectType objType) : _type(objType) {}
    virtual ~Object() {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;

    // ������Ʈ Ÿ�� ��ȯ
    ObjectType GetObjectType() const { return _type; }

    // ������Ʈ ��ġ ���� �Լ�
    FPOINT GetPos() const { return _pos; }
    void SetPos(FPOINT pos) { _pos = pos; }

    // ������Ʈ ũ�� ���� �� ��������
    FPOINT GetSize() const { return _size; }
    void SetSize(FPOINT size) { _size = size; }

    // ü�� ���� �Լ�
    void TakeDamage(UINT32 dmg) {
        if (_stat.Hp > (INT32)dmg)
            _stat.Hp -= dmg;
        else
            _stat.Hp = 0;
    }

    bool IsDead() const { return _stat.Hp <= 0; }

protected:
    ObjectType _type = ObjectType::None; // ������Ʈ Ÿ��
    Stat _stat = {};                     // ���� ����
    FPOINT _pos = {};                    // ��ġ
    FPOINT _size = { 0.0f, 0.0f };         // ũ��
};
