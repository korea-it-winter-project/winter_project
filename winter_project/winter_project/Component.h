#pragma once
class Component {
public:
	Actor* GetOwner() { return _owner; };
	void SetOwner(Actor* owner) { _owner = owner };
private:
	Actor* _owner = nullptr;

};