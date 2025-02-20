#include "pch.h"
#include "Player.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"

//FPOINT pos = { 300,300 };
float _speed = 1000;

DevScene::DevScene() {

}
DevScene::~DevScene() {

}
void DevScene::Init() {
	GET_SINGLE(MapData)->LoadFromFileText("map.csv");
	int *map = GET_SINGLE(MapData)->GetMap2();
	//for (int i = 0; i < MAP_ROWS + 2; i++) {
	//	for (int j = 0; j < MAP_COLS + 2; j++) {
	//		//std::cout << *(map + i * (MAP_COLS + 2) + j) << " ";
	//		printf("%s ", *(map + i * (MAP_COLS + 2) + j) == -9 ? "X" : *(map + i * (MAP_COLS + 2) + j) == 1?"S": *(map + i * (MAP_COLS + 2) + j)==999?"G":" ");
	//	}
	//	std::cout << std::endl;
	//}
	utils ut;
	ut.RunPathfinding(map, MAP_ROWS + 2, MAP_COLS+2);
}
void DevScene::Update() {
	
}
void DevScene::Render(HDC hdc) {
	//Rectangle(hdc, (int)_pos.x - 25, (int)_pos.y - 25, (int)_pos.x + 25, (int)_pos.y + 25);
}
