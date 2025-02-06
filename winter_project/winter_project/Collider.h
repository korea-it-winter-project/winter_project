#pragma once
//#include "pch.h"
class Object;

class Collider {
public:
    Collider(Object* owner) : _owner(owner) {}
    virtual ~Collider() {}

    virtual bool CheckCollision(Collider* other) = 0;
    virtual void ResolveCollision(Collider* other) = 0;

    Object* GetOwner() const { return _owner; }

protected:
    Object* _owner;
};

