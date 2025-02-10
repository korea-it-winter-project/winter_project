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
		rect = GET_SINGLE(InputManager)->GetRect(); // ���� ��ǥ ������
		backRect = { rect.left + 60, rect.bottom - 50, rect.right - 60, rect.bottom - 10 }; // �޹�� ��ǥ
		hpRect = { backRect.left + 10, backRect.top + 10, backRect.left + 210, backRect.bottom - 10 }; // hp ��ǥ
		hpBarRect = { hpRect.left, hpRect.top, hpRect.left + static_cast<int>((static_cast<float>(hp) / (static_cast<float>(maxHp))) * (hpRect.right - hpRect.left)),hpRect.bottom }; // hp ������ ���� �� ũ�� ����
		coinRect = { hpRect.right + 5, hpRect.top, hpRect.right + 75, hpRect.bottom }; // ���� ǥ�� ��ǥ
		statRect = { backRect.right - 200, backRect.top - 100, backRect.right, backRect.top - 10 }; // ����â ��ǥ
		menuRect = { backRect.right - 200, rect.top + 10, backRect.right, backRect.top - 10 }; // �޴� ��ǥ
		upButtonRect = { backRect.right - 100, backRect.top + 10, backRect.right - 10, backRect.bottom - 10 }; // ��ȭ �޴� ��ư ��ǥ
		upTitleRect = { menuRect.left, menuRect.top, menuRect.right, menuRect.top + 25 }; // ��ȭ Ÿ��Ʋ ��ǥ
		dmgUpRect = { menuRect.left + 10, upTitleRect.bottom + 5, menuRect.right - 10, upTitleRect.bottom + 65 }; // ������ ��ȭ ��ǥ
		dmgUpBRect = { dmgUpRect.right - 75, dmgUpRect.top + 15, dmgUpRect.right - 5, dmgUpRect.bottom - 5 }; // ������ ��ȭ ��ư ��ǥ
		maxHpUpRect = { dmgUpRect.left, dmgUpRect.bottom + 5, dmgUpRect.right, dmgUpRect.bottom + 65 }; // �ִ� ü�� ��ȭ ��ǥ
		maxHpUpBRect = { maxHpUpRect.right - 75, maxHpUpRect.top + 15, maxHpUpRect.right - 5, maxHpUpRect.bottom - 5 }; // �ִ� ü�� ��ȭ ��ư ��ǥ
		towButtonRect = { upButtonRect.left - 100, upButtonRect.top, upButtonRect.left - 10, upButtonRect.bottom }; // Ÿ�� �޴� ��ư ��ǥ
		towTitleRect = upTitleRect; // Ÿ�� Ÿ��Ʋ ��ǥ
		bTowRect = { menuRect.left + 10, towTitleRect.bottom + 5, menuRect.right - 10, towTitleRect.bottom + 65 }; // �⺻ Ÿ�� ���� ��ǥ
		bTowBuyRect = { bTowRect.right - 75, bTowRect.top + 15, bTowRect.right - 5, bTowRect.bottom - 5 }; // �⺻ Ÿ�� ���� ��ư ��ǥ
		dmgRect = { statRect.left + 10, statRect.top + 5, statRect.right - 10, statRect.top + 21 }; // ���� ������ ǥ�� ��ǥ
		accDmgRect = { dmgRect.left, dmgRect.bottom + 5, dmgRect.right, dmgRect.bottom + 21 }; // ���� ������ ǥ�� ��ǥ
		remMobRect = { accDmgRect.left, accDmgRect.bottom + 5, accDmgRect.right, accDmgRect.bottom + 21 }; // ���� ���� �� ǥ�� ��ǥ
		killedMobRect = { remMobRect.left, remMobRect.bottom + 5, remMobRect.right, remMobRect.bottom + 21 }; // ���� ���� �� ǥ�� ��ǥ

		if (hp > maxHp * 0.6) { // hp ������ ���� �� ���� ����
			barColor = RGB(0, 255, 0); // �ʷ�
		}
		else if (hp > maxHp * 0.2) {
			barColor = RGB(255, 255, 0); // ���
		}
		else {
			barColor = RGB(255, 0, 0); // ����
		}

		if (hp != 0) {
			//float dtime = GET_SINGLE(TimeManager)->GetDeltaTime();
			hp -= 1 * GET_SINGLE(TimeManager)->GetDeltaTime();
		}
		else
			hp = maxHp;

		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) { // ��Ŭ�� �ν�
			if (GET_SINGLE(InputManager)->CheckMousePoint(upButtonRect)) { // ��ȭ �޴� ��ư�� ���� ���
				isUpgrade_ = !isUpgrade_; // ��ȭ �޴� Ȱ��ȭ/��Ȱ��ȭ
				isTower_ = false; // Ÿ�� �޴� ��Ȱ��ȭ
				coin += 1000;
			}
			if (isUpgrade_) { // ��ȭ �޴��� Ȱ��ȭ�Ǿ� ���� ��
				if (GET_SINGLE(InputManager)->CheckMousePoint(dmgUpBRect)) { // ������ ��ȭ ��ư�� ���� ���
					if (coin >= 20) { // ������ 20�� �̻� ���� ���
						dmg += 2;
						coin -= 20;
					}
				}
				if (GET_SINGLE(InputManager)->CheckMousePoint(maxHpUpBRect)) { // �ִ� ü�� ��ȭ ��ư�� ���� ���
					if (coin >= 50) { //������ 50�� �̻� ���� ���
						maxHp += 20;
						coin -= 50;
					}
				}
			}
			if (GET_SINGLE(InputManager)->CheckMousePoint(towButtonRect)) { // Ÿ�� �޴� ��ư�� ���� ���
				isUpgrade_ = false; // ��ȭ �޴� ��Ȱ��ȭ
				isTower_ = !isTower_; // Ÿ�� �޴� Ȱ��ȭ/��Ȱ��ȭ
				coin += 1000;
			}
			if (isTower_) { // Ÿ�� �޴��� Ȱ��ȭ�Ǿ� ���� ��
				if (GET_SINGLE(InputManager)->CheckMousePoint(bTowBuyRect)) {
					if (coin >= 200) { // ������ 200�� �̻� ���� ���
						coin -= 200;
					}
				}
			}
		}

		// �ӽ�
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
		Rectangle(hdc, backRect.left, backRect.top, backRect.right, backRect.bottom); // �� ��� �׵θ�
		Rectangle(hdc, hpRect.left - 2, hpRect.top - 2, hpRect.right + 2, hpRect.bottom + 2); // hp�� �� �׵θ�
		Rectangle(hdc, upButtonRect.left, upButtonRect.top, upButtonRect.right, upButtonRect.bottom); // ��ȭ �޴� ��ư �׵θ�
		Rectangle(hdc, towButtonRect.left, towButtonRect.top, towButtonRect.right, towButtonRect.bottom); // Ÿ�� �޴� ��ư �׵θ�
		if (isUpgrade_ || isTower_) {
			Rectangle(hdc, menuRect.left, menuRect.top, menuRect.right, menuRect.bottom); // ��ȭ �޴� �׵θ�
			if (isUpgrade_) {
				Rectangle(hdc, upTitleRect.left, upTitleRect.top, upTitleRect.right, upTitleRect.bottom); // ��ȭ Ÿ��Ʋ �׵θ�
				Rectangle(hdc, dmgUpRect.left, dmgUpRect.top, dmgUpRect.right, dmgUpRect.bottom); // ������ ��ȭ �׵θ�
				Rectangle(hdc, dmgUpBRect.left, dmgUpBRect.top, dmgUpBRect.right, dmgUpBRect.bottom); // ������ ��ȭ ��ư �׵θ�
				Rectangle(hdc, maxHpUpRect.left, maxHpUpRect.top, maxHpUpRect.right, maxHpUpRect.bottom); // �ִ� ü�� ��ȭ �׵θ�
				Rectangle(hdc, maxHpUpBRect.left, maxHpUpBRect.top, maxHpUpBRect.right, maxHpUpBRect.bottom); // �ִ� ü�� ��ȭ ��ư �׵θ�
				SetBkMode(hdc, TRANSPARENT); // �ؽ�Ʈ ��� ����
				wchar_t upTitle_buffer[100]; // ��ȭ Ÿ��Ʋ ǥ��
				swprintf(upTitle_buffer, 100, L"UPGRADE");
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, upTitle_buffer, -1, &upTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				wchar_t dmgUp_buffer[100]; // ������ ��ȭ ǥ��
				swprintf(dmgUp_buffer, 100, L"DMG Upgrade");
				DrawText(hdc, dmgUp_buffer, -1, &dmgUpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t maxHpUp_buffer[100]; // �ִ� ü�� ��ȭ ǥ��
				swprintf(maxHpUp_buffer, 100, L"MaxHp Upgrade");
				DrawText(hdc, maxHpUp_buffer, -1, &maxHpUpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Upgrade_buffer[100]; // ��ȭ ��ư ǥ��
				swprintf(Upgrade_buffer, 100, L"Upgrade");
				DrawText(hdc, Upgrade_buffer, -1, &dmgUpBRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				DrawText(hdc, Upgrade_buffer, -1, &maxHpUpBRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SetBkMode(hdc, OPAQUE); // �ؽ�Ʈ ��� ����
			}
			if (isTower_) {
				Rectangle(hdc, towTitleRect.left, towTitleRect.top, towTitleRect.right, towTitleRect.bottom); // Ÿ�� Ÿ��Ʋ �׵θ�
				Rectangle(hdc, bTowRect.left, bTowRect.top, bTowRect.right, bTowRect.bottom); // �⺻ Ÿ�� ���� �׵θ�
				Rectangle(hdc, bTowBuyRect.left, bTowBuyRect.top, bTowBuyRect.right, bTowBuyRect.bottom); // �⺻ Ÿ�� ���� ��ư �׵θ�
				SetBkMode(hdc, TRANSPARENT);
				wchar_t towTitle_buffer[100]; // Ÿ�� Ÿ��Ʋ ǥ��
				swprintf(towTitle_buffer, 100, L"TOWER");
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, towTitle_buffer, -1, &towTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				wchar_t bTow_buffer[100]; // �⺻ Ÿ�� ǥ��
				swprintf(bTow_buffer, 100, L"Basic Tower");
				DrawText(hdc, bTow_buffer, -1, &bTowRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Buy_buffer[100]; // ���� ��ư ǥ��
				swprintf(Buy_buffer, 100, L"Buy");
				DrawText(hdc, Buy_buffer, -1, &bTowBuyRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SetBkMode(hdc, OPAQUE);
			}
		}
		if (!isUpgrade_ && !isTower_) {
			Rectangle(hdc, statRect.left, statRect.top, statRect.right, statRect.bottom); // ����â �׵θ�
			SetBkMode(hdc, TRANSPARENT);
			wchar_t dmg_buffer[100]; // ������ ǥ��
			swprintf(dmg_buffer, 100, L"Dmg: %d", dmg);
			SetTextColor(hdc, RGB(128, 128, 128)); // ȸ��
			DrawText(hdc, dmg_buffer, -1, &dmgRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t accDmg_buffer[100]; // ���� ������ ǥ��
			swprintf(accDmg_buffer, 100, L"Accumulated Dmg: %d", accDmg);
			DrawText(hdc, accDmg_buffer, -1, &accDmgRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t remMob_buffer[100]; // ���� ���� �� ǥ��
			swprintf(remMob_buffer, 100, L"Remaining Mob: %d", remMob);
			DrawText(hdc, remMob_buffer, -1, &remMobRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			wchar_t kilMob_buffer[100]; // ���� ���� �� ǥ��
			swprintf(kilMob_buffer, 100, L"Killed Mob: %d", killedMob);
			DrawText(hdc, kilMob_buffer, -1, &killedMobRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			SetBkMode(hdc, OPAQUE);
		}
		// hp�� �׸���
		HBRUSH barBrush = CreateSolidBrush(barColor);
		FillRect(hdc, &hpBarRect, barBrush);
		DeleteObject(barBrush);
		SetBkMode(hdc, TRANSPARENT);
		wchar_t hp_buffer[100]; // hp ǥ��
		swprintf(hp_buffer, 100, L"hp: %d/%d", hp, maxHp);
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, hp_buffer, -1, &hpRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t coin_buffer[100]; // ���� ǥ��
		swprintf(coin_buffer, 100, L"coin: %d", coin);
		DrawText(hdc, coin_buffer, -1, &coinRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		wchar_t up_buffer[100]; // ��ȭ �޴� ��ư ǥ��
		swprintf(up_buffer, 100, L"Upgrade");
		DrawText(hdc, up_buffer, -1, &upButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wchar_t tow_buffer[100]; // Ÿ�� �޴� ��ư ǥ��
		swprintf(tow_buffer, 100, L"Tower");
		DrawText(hdc, tow_buffer, -1, &towButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetBkMode(hdc, OPAQUE);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
};