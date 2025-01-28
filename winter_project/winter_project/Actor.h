#pragma once
#include "Vector.h"
class Component;

class Actor {
public:
	void AddComponent(Component* component) {
		if (component == nullptr)return;
		component->SetOwner(this);
		
	};
	void RemoveComponent(Component* component) {
	
	};

protected:
	Vector _pos{ 0,0 };
	vector<Component*>_compo;
};

