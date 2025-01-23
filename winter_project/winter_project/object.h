#pragma once

#include "pch.h"

struct Stat {
	UINT32 Hp = 0;
	UINT32 MaxHP = 0; //음수로 못넘어 가게 부호 없는 정수로 지정
	float speed;
	UINT32 damage=0; 
	/*
	간혹 게임중 공격도중 음수 값이 나와 딜이아니라
	적을 힐을 하는 경우가 있음 이를 막기 위해 부호 없는 정수로 지정
	*/
};


enum class ObjectType {
	None,
	Player,
	Monster,
	Projectle,
	block,
};

class Object {
public:
	Object(ObjectType objType) {};
	~Object() {};

	virtual void Init() abstract {};
	virtual void Update() abstract {};
	virtual void Render(HDC hdc) abstract {};

public :
	ObjectType GetObjectType() { return _type; }
	FPOINT GetPos() { return _pos; }
	void SetPos(FPOINT pos) { _pos = pos; }
protected:
	ObjectType _type = ObjectType::None;
	Stat _stat = {};
	FPOINT _pos = {};

};
