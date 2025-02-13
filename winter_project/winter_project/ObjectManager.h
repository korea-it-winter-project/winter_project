#pragma once
#include "pch.h"
#include "object.h"

//class Object;

class ObjectManager {
    DECLARE_SINGLE(ObjectManager);

public:
    ~ObjectManager() {
        clear();
    }
    void Render(HDC hdc) {
        for (auto* obj : _objects) {
            obj->Render(hdc);
        }
    }
    int GetObjC() { return objcount; }
    void Add(Object* object) {
        if (object == nullptr) return;

        auto findIt = std::find(_objects.begin(), _objects.end(), object);
        if (findIt != _objects.end()) return;
        objcount++;
        _objects.push_back(object);
    }

    void Remove(Object* object) {
        if (object == nullptr) return;

        auto it = std::remove(_objects.begin(), _objects.end(), object);
        _objects.erase(it, _objects.end());

        delete object;
    }

    void clear() {
        for (auto* obj : _objects) {
            delete obj;
        }
        objcount = 0;
        _objects.clear();
    }

    const std::vector<Object*>& GetObjects() const {
        return _objects;
    }

    template<typename T, typename... Args>
    T* CreateObject(Args&&... args) {
        static_assert(std::is_base_of<Object, T>::value, "T must be derived from Object");

        T* object = new T(std::forward<Args>(args)...);
        object->Init();  // Object 클래스 또는 파생 클래스에 Init 메서드가 있어야 합니다.
        Add(object);
        return object;
    }


    void CheckCollisions() {
        for (size_t i = 0; i < _objects.size(); i++) {
            for (size_t j = i + 1; j < _objects.size(); j++) {
                Object* objA = _objects[i];
                Object* objB = _objects[j];

                if (!objA->GetCollider() || !objB->GetCollider()) continue;

                if (objA->GetCollider()->CheckCollision(objB->GetCollider())) {
                    objA->OnCollision(objB->GetCollider());
                    objB->OnCollision(objA->GetCollider());
                }
            }
        }
    }

private:
    std::vector<Object*> _objects;
    int objcount;
};