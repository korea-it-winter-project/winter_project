#pragma once
#include "pch.h"

class Player : public Object {
public :
	Player();
	virtual ~Player() override;

	virtual void init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:

};