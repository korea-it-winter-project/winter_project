#pragma once
#include "object.h"

class Player : public Object {
public :
	Player();
	virtual ~Player() ;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:

};
