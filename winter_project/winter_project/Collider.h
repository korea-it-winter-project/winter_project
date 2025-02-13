#pragma once
#include "pch.h"
class Object;
//#include "object.h"

class Collider {
public:
    Collider(Object* owner) : _owner(owner) {}
    virtual ~Collider() {}

    virtual bool CheckCollision(Collider* other) = 0;
    virtual void ResolveCollision(Collider* other) = 0; 

    Object* GetOwner() const { return _owner; }
    void Render(HDC hdc) {
        
    }
    Vector _size;
     
protected:
    Object* _owner;

};

