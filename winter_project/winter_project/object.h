#pragma once

#include "pch.h"

struct Stat {
	UINT32 Hp = 0;
	UINT32 MaxHP = 0;
	float speed;
	UINT damage=0;
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
	Object(ObjectType objType);
	virtual ~Object();

	virtual void init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

public :
	ObjectType GetObjectType() { return _type; }
	FPOINT GetPos() { return _pos; }
	void SetPos(FPOINT pos) { _pos = pos; }
protected:
	ObjectType _type = ObjectType::None;
	Stat _stat = {};
	FPOINT _pos;

};
