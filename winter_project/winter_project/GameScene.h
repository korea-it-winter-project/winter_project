#pragma once
#include "Scene.h"
#include "Vector.h"
#include "ObjectManager.h"
#include "Player.h"
#include "monster.h"
#include "BoxCollider.h"

class GameScene :public Scene {
	//class Player* _player;
	//class Monster* _monster;

public :
	GameScene() {};
	virtual ~GameScene() override {};

	virtual void Init()override {
		{
			Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
			player->SetPos(Vector{ 400,400 });
			player->SetSize(Vector{ 25,25 });
			GET_SINGLE(ObjectManager)->Add(player);
			player->SetCollider(new BoxCollider(player, player->GetSize()));
		}
		{
			Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
			monster->SetPos(Vector{ 200,400 });
			monster->SetSize(Vector{ 25,25 });
			GET_SINGLE(ObjectManager)->Add(monster);
			monster->SetCollider(new BoxCollider(monster, monster->GetSize()));
		}
	};
	virtual void Update()override {
	
	};
	virtual void Render(HDC hdc)override {
	
	};
	

};
