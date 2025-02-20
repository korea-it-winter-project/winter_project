#pragma once
#include "pch.h"
#include "BoxCollider.h"

enum SpawnerState
{
	Waiting,
	Spawning

};

class MonsterSpawner
{
	DECLARE_SINGLE( MonsterSpawner );
public:
	~MonsterSpawner()
	{

	}

	void Init( int* path,int pathLength ) {
		spawnTimer = 1.f ;
		_state = Spawning ;
		this->path = path;  
		this->pathLength = pathLength;  
	}

	void Update() {
		
		if ( _state == Spawning )
		{
			spawnTimer -= GET_SINGLE( TimeManager )->GetDeltaTime();
			if ( spawnTimer <= 0.f ) {
				SpawnMonster();
				spawnTimer = 2.f;
			}
		}
	}

	void DirectionCaluation()
	{
		/*for ( int i = 0; i < pathLength; i++ ) {
			this->path[ i ] = path[ i ];
		}*/


	}

	void SpawnMonster() {
		Monster* monster = GET_SINGLE( ObjectManager )->CreateObject<Monster>( path,pathLength );
		monster->SetPos( Vector{ 0,0 } );
		monster->SetSize( Vector{ 25,25 } );
		monster->SetCollider( new BoxCollider( monster,monster->GetSize() ) );
		GET_SINGLE( ObjectManager )->Add( monster );

	}

	void SetState( SpawnerState newState ) {
		_state = newState;
	}

private:
	float spawnTimer;
	SpawnerState _state;
	int* path;  // 수정된 부분
	int pathLength;  // 수정된 부분
	int direction[];
};