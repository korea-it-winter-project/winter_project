#pragma once
#include "pch.h"
#include "object.h"

class Object;

class ObjectManager {
    DECLARE_SINGLE(ObjectManager);

public:
    ~ObjectManager() {
        clear();
    }

    void Add(Object* object) {
        if (object == nullptr) return;

        auto findIt = std::find(_objects.begin(), _objects.end(), object);
        if (findIt != _objects.end()) return;

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
        _objects.clear();
    }

    const std::vector<Object*>& GetObjects() const {
        return _objects;
    }

    template<typename T>
    T* CreateObject() {
        static_assert(std::is_base_of<Object, T>::value, "T must be derived from Object");

        T* object = new T();
        object->Init();  // Object 클래스 또는 파생 클래스에 Init 메서드가 있어야 합니다.
        Add(object);
        return object;
    }

private:
    std::vector<Object*> _objects;
};