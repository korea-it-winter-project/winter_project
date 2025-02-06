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
        object->Init();  // Object Ŭ���� �Ǵ� �Ļ� Ŭ������ Init �޼��尡 �־�� �մϴ�.
        Add(object);
        return object;
    }


    void CheckCollisions() {
        for (size_t i = 0; i < _objects.size(); ++i) {
            Collider* colliderA = _objects[i]->GetCollider();
            if (!colliderA) continue;  // �浹ü�� ���� ��� ����

            for (size_t j = i + 1; j < _objects.size(); ++j) {
                Collider* colliderB = _objects[j]->GetCollider();
                if (!colliderB) continue;  // �浹ü�� ���� ��� ����

                if (colliderA->CheckCollision(colliderB)) {
                    // **�浹 �߻� �� ó��**
                    _objects[i]->OnCollision(colliderB);
                    _objects[j]->OnCollision(colliderA);
                }
            }
        }
    }
private:
    std::vector<Object*> _objects;
};