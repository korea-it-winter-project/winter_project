#pragma once
#include "Collider.h"
#include "Vector.h"
class BoxCollider : public Collider {
public:
    BoxCollider(Object* owner, Vector size) : Collider(owner), _size(size) {}

    bool CheckCollision(Collider* other) override {
        BoxCollider* box = dynamic_cast<BoxCollider*>(other);
        if (!box) return false;

        Vector posA = _owner->GetPos();
        Vector posB = box->_owner->GetPos();
        Vector sizeA = _size;
        Vector sizeB = box->_size;

        return (posA.x < posB.x + sizeB.x &&
            posA.x + sizeA.x > posB.x &&
            posA.y < posB.y + sizeB.y &&
            posA.y + sizeA.y > posB.y);
    }

    void ResolveCollision(Collider* other) override {
        // 충돌 해결 로직 추가 가능
    }

    void SetSize(Vector size) { _size = size; }
    Vector GetSize() const { return _size; }

private:
    Vector _size;
};
