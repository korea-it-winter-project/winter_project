#pragma once
#include "pch.h"
#include "TimeManager.h"
#include "Leveleditor.h"
//#include "Scene.h"

class UiScene :public Scene{
private:
	COLORREF barColor;
	RECT rect;
	RECT backRect;
	RECT hpRect;
	RECT hpBarRect;
	RECT coinRect;
	RECT statRect;
	RECT menuRect;
	RECT upButtonRect;
	RECT upTitleRect;
	RECT dmgUpRect;
	RECT dmgUpBRect;
	RECT maxHpUpRect;
	RECT maxHpUpBRect;
	RECT towButtonRect;
	RECT towTitleRect;
	RECT bTowRect;
	RECT bTowBuyRect;
	RECT dmgRect;
	RECT accDmgRect;
	RECT remMobRect;
	RECT killedMobRect;
	HPEN pen;
	HPEN oldPen;
	//DECLARE_SINGLE(UiScene);
public:
	int coin;
	int hp, maxHp;
	int dmg;
	int accDmg, remMob, killedMob;
	bool isUpgrade_;
	bool isTower_;
	bool isStart = false;
	UiScene() {};
	virtual ~UiScene() override {};
	void isStarted() {
		true;
	}
	virtual void Init() override {
		coin = 0;
		hp = 500;
		maxHp = 500;
		dmg = 10;
		isUpgrade_ = false;
		isTower_ = false;
		accDmg = 0, remMob = 100, killedMob = 0;
	}
	virtual void Update() override {
		rect = GET_SINGLE(InputManager)->GetRect(); // 메인 좌표 가져옴
		backRect = { rect.left + 60, rect.bottom - 50, rect.right - 60, rect.bottom - 10 }; // 뒷배경 좌표
		hpRect = { backRect.left + 10, backRect.top + 10, backRect.left + 210, backRect.bottom - 10 }; // hp 좌표
		hpBarRect = { hpRect.left, hpRect.top, hpRect.left + static_cast<int>((static_cast<float>(hp) / (static_cast<float>(maxHp))) * (hpRect.right - hpRect.left)),hpRect.bottom }; // hp 비율에 따라 바 크기 변경
		coinRect = { hpRect.right + 5, hpRect.top, hpRect.right + 75, hpRect.bottom }; // 코인 표기 좌표
		statRect = { backRect.right - 200, backRect.top - 100, backRect.right, backRect.top - 10 }; // 스탯창 좌표
		menuRect = { backRect.right - 200, rect.top + 10, backRect.right, backRect.top - 10 }; // 메뉴 좌표
		upButtonRect = { backRect.right - 100, backRect.top + 10, backRect.right - 10, backRect.bottom - 10 }; // 강화 메뉴 버튼 좌표
		upTitleRect = { menuRect.left, menuRect.top, menuRect.right, menuRect.top + 25 }; // 강화 타이틀 좌표
		dmgUpRect = { menuRect.left + 10, upTitleRect.bottom + 5, menuRect.right - 10, upTitleRect.bottom + 65 }; // 데미지 강화 좌표
		dmgUpBRect = { dmgUpRect.right - 75, dmgUpRect.top + 15, dmgUpRect.right - 5, dmgUpRect.bottom - 5 }; // 데미지 강화 버튼 좌표
		maxHpUpRect = { dmgUpRect.left, dmgUpRect.bottom + 5, dmgUpRect.right, dmgUpRect.bottom + 65 }; // 최대 체력 강화 좌표
		maxHpUpBRect = { maxHpUpRect.right - 75, maxHpUpRect.top + 15, maxHpUpRect.right - 5, maxHpUpRect.bottom - 5 }; // 최대 체력 강화 버튼 좌표
		towButtonRect = { upButtonRect.left - 100, upButtonRect.top, upButtonRect.left - 10, upButtonRect.bottom }; // 타워 메뉴 버튼 좌표
		towTitleRect = upTitleRect; // 타워 타이틀 좌표
		bTowRect = { menuRect.left + 10, towTitleRect.bottom + 5, menuRect.right - 10, towTitleRect.bottom + 65 }; // 기본 타워 구매 좌표
		bTowBuyRect = { bTowRect.right - 75, bTowRect.top + 15, bTowRect.right - 5, bTowRect.bottom - 5 }; // 기본 타워 구매 버튼 좌표
		dmgRect = { statRect.left + 10, statRect.top + 5, statRect.right - 10, statRect.top + 21 }; // 현재 데미지 표기 좌표
		accDmgRect = { dmgRect.left, dmgRect.bottom + 5, dmgRect.right, dmgRect.bottom + 21 }; // 누적 데미지 표기 좌표
		remMobRect = { accDmgRect.left, accDmgRect.bottom + 5, accDmgRect.right, accDmgRect.bottom + 21 }; // 남은 몬스터 수 표기 좌표
		killedMobRect = { remMobRect.left, remMobRect.bottom + 5, remMobRect.right, remMobRect.bottom + 21 }; // 죽인 몬스터 수 표기 좌표

		if (hp > maxHp * 0.6) { // hp 비율에 따라 바 색상 변경
			barColor = RGB(0, 255, 0); // 초록
		}
		else if (hp > maxHp * 0.2) {
			barColor = RGB(255, 255, 0); // 노랑
		}
		else {
			barColor = RGB(255, 0, 0); // 빨강
		}

		if (hp != 0) {
			//float dtime = GET_SINGLE(TimeManager)->GetDeltaTime();
			hp -= 1 * GET_SINGLE(TimeManager)->GetDeltaTime();
		}
		else
			hp = maxHp;

		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) { // 좌클릭 인식
			if (GET_SINGLE(InputManager)->CheckMousePoint(upButtonRect)) { // 강화 메뉴 버튼을 누를 경우
				isUpgrade_ = !isUpgrade_; // 강화 메뉴 활성화/비활성화
				isTower_ = false; // 타워 메뉴 비활성화
				coin += 1000;
			}
			if (isUpgrade_) { // 강화 메뉴가 활성화되어 있을 때
				if (GET_SINGLE(InputManager)->CheckMousePoint(dmgUpBRect)) { // 데미지 강화 버튼을 누를 경우
					if (coin >= 20) { // 코인이 20개 이상 있을 경우
						dmg += 2;
						coin -= 20;
					}
				}
				if (GET_SINGLE(InputManager)->CheckMousePoint(maxHpUpBRect)) { // 최대 체력 강화 버튼을 누를 경우
					if (coin >= 50) { //코인이 50개 이상 있을 경우
						maxHp += 20;
						coin -= 50;
					}
				}
			}
			if (GET_SINGLE(InputManager)->CheckMousePoint(towButtonRect)) { // 타워 메뉴 버튼을 누를 경우
				isUpgrade_ = false; // 강화 메뉴 비활성화
				isTower_ = !isTower_; // 타워 메뉴 활성화/비활성화
				coin += 1000;
			}
			if (isTower_) { // 타워 메뉴가 활성화되어 있을 때
				if (GET_SINGLE(InputManager)->CheckMousePoint(bTowBuyRect)) {
					if (coin >= 200) { // 코인이 200개 이상 있을 경우
						coin -= 200;
					}
				}
			}
		}

		// 임시
		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::R_mouse)) {
			if (GET_SINGLE(InputManager)->CheckMousePoint(hpRect)) {
				if (remMob > 0) {
					remMob -= 1;
					killedMob += 1;
				}
			}
			accDmg += dmg;
		}
	}
	virtual void Render(HDC hdc) override  {
		
		pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, backRect.left, backRect.top, backRect.right, backRect.bottom); // 뒷 배경 테두리
		Rectangle(hdc, hpRect.left - 2, hpRect.top - 2, hpRect.right + 2, hpRect.bottom + 2); // hp바 겉 테두리
		Rectangle(hdc, upButtonRect.left, upButtonRect.top, upButtonRect.right, upButtonRect.bottom); // 강화 메뉴 버튼 테두리
		Rectangle(hdc, towButtonRect.left, towButtonRect.top, towButtonRect.right, towButtonRect.bottom); // 타워 메뉴 버튼 테두리
		if (isUpgrade_ || isTower_) {
			Rectangle(hdc, menuRect.left, menuRect.top, menuRect.right, menuRect.bottom); // 강화 메뉴 테두리
			if (isUpgrade_) {
				Rectangle(hdc, upTitleRect.left, upTitleRect.top, upTitleRect.right, upTitleRect.bottom); // 강화 타이틀 테두리
				Rectangle(hdc, dmgUpRect.left, dmgUpRect.top, dmgUpRect.right, dmgUpRect.bottom); // 데미지 강화 테두리
				Rectangle(hdc, dmgUpBRect.left, dmgUpBRect.top, dmgUpBRect.right, dmgUpBRect.bottom); // 데미지 강화 버튼 테두리
				Rectangle(hdc, maxHpUpRect.left, maxHpUpRect.top, maxHpUpRect.right, maxHpUpRect.bottom); // 최대 체력 강화 테두리
				Rectangle(hdc, maxHpUpBRect.left, maxHpUpBRect.top, maxHpUpBRect.right, maxHpUpBRect.bottom); // 최대 체력 강화 버튼 테두리
				SetBkMode(hdc, TRANSPARENT); // 텍스트 배경 없앰
				wchar_t upTitle_buffer[100]; // 강화 타이틀 표기
				swprintf(upTitle_buffer, 100, L"UPGRADE");
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, upTitle_buffer, -1, &upTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				wchar_t dmgUp_buffer[100]; // 데미지 강화 표기
				swprintf(dmgUp_buffer, 100, L"DMG Upgrade");
				DrawText(hdc, dmgUp_buffer, -1, &dmgUpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t maxHpUp_buffer[100]; // 최대 체력 강화 표기
				swprintf(maxHpUp_buffer, 100, L"MaxHp Upgrade");
				DrawText(hdc, maxHpUp_buffer, -1, &maxHpUpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Upgrade_buffer[100]; // 강화 버튼 표기
				swprintf(Upgrade_buffer, 100, L"Upgrade");
				DrawText(hdc, Upgrade_buffer, -1, &dmgUpBRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				DrawText(hdc, Upgrade_buffer, -1, &maxHpUpBRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SetBkMode(hdc, OPAQUE); // 텍스트 배경 복구
			}
			if (isTower_) {
				Rectangle(hdc, towTitleRect.left, towTitleRect.top, towTitleRect.right, towTitleRect.bottom); // 타워 타이틀 테두리
				Rectangle(hdc, bTowRect.left, bTowRect.top, bTowRect.right, bTowRect.bottom); // 기본 타워 구매 테두리
				Rectangle(hdc, bTowBuyRect.left, bTowBuyRect.top, bTowBuyRect.right, bTowBuyRect.bottom); // 기본 타워 구매 버튼 테두리
				SetBkMode(hdc, TRANSPARENT);
				wchar_t towTitle_buffer[100]; // 타워 타이틀 표기
				swprintf(towTitle_buffer, 100, L"TOWER");
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, towTitle_buffer, -1, &towTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				wchar_t bTow_buffer[100]; // 기본 타워 표기
				swprintf(bTow_buffer, 100, L"Basic Tower");
				DrawText(hdc, bTow_buffer, -1, &bTowRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Buy_buffer[100]; // 구매 버튼 표기
				swprintf(Buy_buffer, 100, L"Buy");
				DrawText(hdc, Buy_buffer, -1, &bTowBuyRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SetBkMode(hdc, OPAQUE);
			}
		}
		if (!isUpgrade_ && !isTower_) {
			Rectangle(hdc, statRect.left, statRect.top, statRect.right, statRect.bottom); // 스탯창 테두리
			SetBkMode(hdc, TRANSPARENT);
			wchar_t dmg_buffer[100]; // 데미지 표기
			swprintf(dmg_buffer, 100, L"Dmg: %d", dmg);
			SetTextColor(hdc, RGB(128, 128, 128)); // 회색
			DrawText(hdc, dmg_buffer, -1, &dmgRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t accDmg_buffer[100]; // 누적 데미지 표기
			swprintf(accDmg_buffer, 100, L"Accumulated Dmg: %d", accDmg);
			DrawText(hdc, accDmg_buffer, -1, &accDmgRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t remMob_buffer[100]; // 남은 몬스터 수 표기
			swprintf(remMob_buffer, 100, L"Remaining Mob: %d", remMob);
			DrawText(hdc, remMob_buffer, -1, &remMobRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t kilMob_buffer[100]; // 죽인 몬스터 수 표기
			swprintf(kilMob_buffer, 100, L"Killed Mob: %d", killedMob);
			DrawText(hdc, kilMob_buffer, -1, &killedMobRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			SetBkMode(hdc, OPAQUE);
		}
		// hp바 그리기
		HBRUSH barBrush = CreateSolidBrush(barColor);
		FillRect(hdc, &hpBarRect, barBrush);
		DeleteObject(barBrush);
		SetBkMode(hdc, TRANSPARENT);
		wchar_t hp_buffer[100]; // hp 표기
		swprintf(hp_buffer, 100, L"hp: %d/%d", hp, maxHp);
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, hp_buffer, -1, &hpRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t coin_buffer[100]; // 코인 표기
		swprintf(coin_buffer, 100, L"coin: %d", coin);
		DrawText(hdc, coin_buffer, -1, &coinRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		wchar_t up_buffer[100]; // 강화 메뉴 버튼 표기
		swprintf(up_buffer, 100, L"Upgrade");
		DrawText(hdc, up_buffer, -1, &upButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t tow_buffer[100]; // 타워 메뉴 버튼 표기
		swprintf(tow_buffer, 100, L"Tower");
		DrawText(hdc, tow_buffer, -1, &towButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetBkMode(hdc, OPAQUE);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
};