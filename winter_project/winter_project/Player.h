#pragma once
#include"InputManager.h"
#include"TimeManager.h"
#include "object.h"
#include "utils.h"
#include "Collider.h"


class Player : public Object {
public :
	Player() : Object(ObjectType::Player) {
		/*collider->init(this, CollderType::Rect);
		collider->SetCollider(Vector(_size.x + 5, _size.y + 5));*/
	};
	virtual ~Player() {

	};

	virtual void Init() override {
		_stat.Hp = 100;
		_stat.MaxHP = 100;
		_stat.speed = 100;
	};
	virtual void Update() override {
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
		if (GET_SINGLE(InputManager)->GetButton(keytype::A))
			_pos.x -= _stat.speed * deltaTime;
		if (GET_SINGLE(InputManager)->GetButton(keytype::D))
			_pos.x += _stat.speed * deltaTime;
		if (GET_SINGLE(InputManager)->GetButton(keytype::W))
			_pos.y -= _stat.speed * deltaTime;

		if (GET_SINGLE(InputManager)->GetButton(keytype::S))
			_pos.y += _stat.speed * deltaTime;
	};
	virtual void Render(HDC hdc) override {
		//Rectangle(hdc, (int)(_pos.x - _size.x)/2, (int)(_pos.y - _size.y)/2, (int)(_pos.x - _size.x) / 2, (int)(_pos.y - _size.y) / 2);
		ut.DrawRect(hdc, _pos, 50, 50);
	};
	void OnCollision(Collider* other) {
		if (other->GetOwner()->GetObjectType() == ObjectType::Monster) {
			IsDead();
		}
	}
public:
	utils ut;
	//Collider2* collider;
};
