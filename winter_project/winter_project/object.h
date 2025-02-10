#pragma once
//#error "object.h 포함됨"

#include "pch.h"
#include "Collider.h"
//#include "Vector.h"
struct Stat {
    INT32 Hp = 0;
    UINT32 MaxHP = 0; // 음수로 못 넘어가게 부호 없는 정수로 지정
    float speed = 0.0f;
    UINT32 damage = 0;
    /*
    공격 중 음수 값으로 인해 적을 힐하는 경우 방지
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

    // 오브젝트 타입 반환
    ObjectType GetObjectType() const { return _type; }

    // 오브젝트 위치 관련 함수
    Vector GetPos() const { return _pos; }
    void SetPos(Vector pos) { _pos = pos; }

    // 오브젝트 크기 설정 및 가져오기
    Vector GetSize() const { return _size; }
    void SetSize(Vector size) { _size = size; }

    void SetBmp(std::shared_ptr<Gdiplus::Bitmap> _pBmp) { pBmp = _pBmp; }

    // 체력 관련 함수
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
    ObjectType _type = ObjectType::None; // 오브젝트 타입
    Stat _stat = {};                     // 스탯 정보
    Vector _pos = {};                    // 위치
    Vector _size = { 0.0f, 0.0f };       // 크기
    Collider* _collider;
    std::shared_ptr<Gdiplus::Bitmap> pBmp;
};

