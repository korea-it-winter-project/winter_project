#pragma once
#include "Collider.h"
#include "Vector.h"
class BoxCollider : public Collider {
public:
    BoxCollider(Object* owner, Vector size) : Collider(owner) { _size = size; }

    bool CheckCollision(Collider* other) override {
        BoxCollider* box = dynamic_cast<BoxCollider*>(other);
        if (!box) return false;

        Vector posA = _owner->GetPos();
        Vector sizeA = _size;
        Vector minA = { posA.x - sizeA.x, posA.y - sizeA.x };                      // AABB �ּ� ��ǥ (�»��)
        Vector maxA = { posA.x + sizeA.x, posA.y + sizeA.y };  // AABB �ִ� ��ǥ (���ϴ�)

        Vector posB = box->_owner->GetPos();
        Vector sizeB = box->_size;
        Vector minB = { posB.x - sizeB.x, posB.y - sizeB.x };
        Vector maxB = { posB.x + sizeB.x, posB.y + sizeB.y };

        return (minA.x < maxB.x && maxA.x > minB.x &&
            minA.y < maxB.y && maxA.y > minB.y);
    }


    void ResolveCollision(Collider* other) override {
        // �浹 �ذ� ���� �߰� ����
    }

    void SetSize(Vector size) { _size = size; }
    Vector GetSize() const { return _size; }

private:
};
