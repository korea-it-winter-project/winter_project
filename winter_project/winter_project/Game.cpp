#include "pch.h"
#include "SceneManager.h"


static UINT32 fps;
static float deltaTime;
static POINT m_pos;

inline void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init(sceneType::DevScene);

	GET_SINGLE(SceneManager)->ChScene(sceneType::DevScene);
}

inline void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->UPdate();

	fps = GET_SINGLE(TimeManager)->GetFps();
	deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	m_pos = GET_SINGLE(InputManager)->GetMousePos();
	//if (GET_SINGLE(InputManager)->GetButton(keytype::UP)) {
	//	pc.move(0,0.1f);
	//}
}

inline void Game::Render() {

	WCHAR str[1024];
	//WCHAR pc_pos[100];
	wsprintfW(str, L"mouse pos : [%04d, %04d]",
		m_pos.x, m_pos.y, fps, deltaTime);
	/*wsprintfW(pc_pos, L"pc pos : [%04d.%03d : %04d.%03d]",
		(int)pc.pos.x, (int)(pc.pos.x * 100) % 100, (int)pc.pos.y, (int)(pc.pos.y * 100) % 100);*/
	::TextOut(_hdc, 20, 10, str, lstrlen(str));
	//::TextOut(_hdc, 20, 40, pc_pos, lstrlen(pc_pos));

	//Rectangle(_hdc, pc.pos.x - 25, pc.pos.y - 25, pc.pos.x + 25, pc.pos.y+25);


	GET_SINGLE(SceneManager)->Render(_hdc);

}
