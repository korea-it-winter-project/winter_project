#pragma once
#include "pch.h"
#include "TimeManager.h"
#include "Leveleditor.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "UIobject.h"
#include "TextOjbect.h"
#include "Scene.h"

class UiScene :public Scene{
private:
	RECT rect;
	RECT backRect;
	RECT coinRect;
	RECT menuRect;
	RECT shopButtonRect;
	RECT dmgUpRect;
	RECT dmgUpBRect;
	RECT bTowRect;
	RECT bTowBuyRect;
	RECT remMobRect;
	HPEN pen;
	HPEN oldPen;
	POINT coinImaRect;
	POINT hpImaRect;
public:
	int coin;
	int hp, maxHp;
	int dmg, remMob;
	bool isShop_;
	std::shared_ptr<Gdiplus::Bitmap> UiBackGroundIma;
	std::shared_ptr<Gdiplus::Bitmap> CoinIma;
	std::shared_ptr<Gdiplus::Bitmap> ShopButtonIma;
	std::shared_ptr<Gdiplus::Bitmap> MenuIma;
	std::shared_ptr<Gdiplus::Bitmap> FullHpIma;
	std::shared_ptr<Gdiplus::Bitmap> HalfHpIma;
	std::shared_ptr<Gdiplus::Bitmap> EmptyHpIma;
	std::shared_ptr<Gdiplus::Bitmap> MainBackGroundIma;

	UiScene() {};
	virtual ~UiScene() override {};

	UiObject* UIcreate(std::shared_ptr<Gdiplus::Bitmap> bmp, Vector pos, Vector size,bool A) {
		UiObject* UIobj = GET_SINGLE(ObjectManager)->CreateObject<UiObject>();
		UIobj->SetPos(pos);
		UIobj->SetSize(size);
		UIobj->IsShow(true);
		UIobj->SetBmp(bmp);
		UIobj->isA = A;
		GET_SINGLE(ObjectManager)->Add(UIobj);
		return UIobj;
	}
	virtual void Init() override {
		coin = 0;
		hp = 20;
		maxHp = 20;
		dmg = 10;
		isShop_ = false;
		remMob = 100;

		// 리소스를 한번만 로드
		ResourceManager* resourceManager = GET_SINGLE(ResourceManager);
		UiBackGroundIma = resourceManager->FindImage(L"game_ui_player_background.png");
		CoinIma = resourceManager->FindImage(L"game_ui_coin.png");
		ShopButtonIma = resourceManager->FindImage(L"game_ui_shop_button.png");
		MenuIma = resourceManager->FindImage(L"game_ui_menu.png");
		FullHpIma = resourceManager->FindImage(L"game_ui_full_heart.png");
		HalfHpIma = resourceManager->FindImage(L"game_ui_half_heart.png");
		EmptyHpIma = resourceManager->FindImage(L"game_ui_empty_heart.png");
		MainBackGroundIma = resourceManager->FindImage(L"game_ui_main_background.png");

		UIcreate(MainBackGroundIma, Vector{ 0,0 }, Vector{ 1000,600 },false);
		UIcreate(UiBackGroundIma, Vector{ 0,535.f }, Vector{ 1000.0f, 65.0f },false);
		UIcreate(ShopButtonIma, Vector{ 805,540.f }, Vector{ 195.f, 50.0f },true);

		coinRect = { 50,50,100,100 };

		TextObject* text1 = GET_SINGLE(ObjectManager)->CreateObject<TextObject>();	
		text1->SetRECT(coinRect);
		text1->showText(L"", coin);
		GET_SINGLE(ObjectManager)->Add(text1);






		/*UiObject* UIbackGround = GET_SINGLE(ObjectManager)->CreateObject<UiObject>();
		UIbackGround->SetPos(Vector{ 0,535.f   });
		UIbackGround->SetSize(Vector{ 1000.0f, 65.0f });
		UIbackGround->IsShow(true);
		UIbackGround->SetBmp(UiBackGroundIma);
		GET_SINGLE(ObjectManager)->Add(UIbackGround);*/


		//GET_SINGLE(ResourceManager)->DrawImage2(hdc, UiBackGroundIma, backRect.left, backRect.top, 940.0, 65.0);
	}

	virtual void Update() override {
		rect = GET_SINGLE(InputManager)->GetRect();
		backRect = { rect.left + 30, rect.bottom - 70, rect.right - 30, rect.bottom - 5 };
		coinRect = { coinImaRect.x + 20, backRect.top + 10, shopButtonRect.left - 10, backRect.bottom - 10 };
		menuRect = { backRect.right - 200, rect.top + 5, backRect.right, backRect.top - 15 };
		shopButtonRect = { menuRect.left, backRect.top + 5, backRect.right - 15, backRect.bottom - 10 };
		dmgUpRect = { menuRect.left + 10, menuRect.top + 50, menuRect.right - 10, menuRect.top + 110 };
		dmgUpBRect = { dmgUpRect.right - 75, dmgUpRect.top + 15, dmgUpRect.right - 5, dmgUpRect.bottom - 5 };
		bTowRect = { dmgUpRect.left, dmgUpRect.bottom + 5, dmgUpRect.right, dmgUpRect.bottom + 65 };
		bTowBuyRect = { bTowRect.right - 75, bTowRect.top + 15, bTowRect.right - 5, bTowRect.bottom - 5 };
		remMobRect = { backRect.left + 310, backRect.top, backRect.left + 470, backRect.bottom };
		coinImaRect = { backRect.left + 500, backRect.top + 12 };
		hpImaRect = { backRect.left + 15, backRect.top + 10 };

		if (GET_SINGLE(InputManager)->GetButtonDwon(keytype::L_mouse)) {
			hp -= 1;
			if (GET_SINGLE(InputManager)->CheckMousePoint(shopButtonRect)) {
				isShop_ = !isShop_;
				coin += 1000;
			}
			if (isShop_ && GET_SINGLE(InputManager)->CheckMousePoint(dmgUpBRect)) {
				if (coin >= 20) {
					dmg += 2;
					coin -= 20;
				}
			}
		}

		if (hp == 0) hp = maxHp;
	}
	virtual void Render(HDC hdc) override  {
		
		pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, pen);
		Gdiplus::Graphics graphics(hdc);

		if (ShopButtonIma) { // 상점 메뉴 버튼
			
			GET_SINGLE(ResourceManager)->DrawImage(graphics, ShopButtonIma, shopButtonRect.left, shopButtonRect.top - 2.0, 185.0, 50.0);
			//GET_SINGLE(ResourceManager)->DrawImage2(hdc, ShopButtonIma, shopButtonRect.left, shopButtonRect.top - 2.0, 185.0, 50.0);
		}
		if (CoinIma) { // 코인
			GET_SINGLE(ResourceManager)->DrawImage(graphics, CoinIma, coinImaRect.x, coinImaRect.y, 25.0, 40.0);
		}
		if (hp == maxHp) { // 현재 체력이 가득 차 있을 경우
			if (FullHpIma) { // hp
				for (int i = 0; i < 10; i++)
					GET_SINGLE(ResourceManager)->DrawImage(graphics, FullHpIma, hpImaRect.x + i * 28, hpImaRect.y + 7, 30.0, 30.0);
			}
		}
		if (hp < maxHp) { // 현재 체력이 닳아있을 경우
			int checkHp = hp;
			for (int i = 0; i < 10; i++) {
				if (checkHp - 2 >= 0) {
					GET_SINGLE(ResourceManager)->DrawImage(graphics, FullHpIma, hpImaRect.x + i * 28, hpImaRect.y + 7, 30.0, 30.0);
					checkHp -= 2;
				}
				else if (checkHp == 1) {
					GET_SINGLE(ResourceManager)->DrawImage(graphics, HalfHpIma, hpImaRect.x + i * 28, hpImaRect.y + 7, 30.0, 30.0);
					checkHp -= 1;
				}
				else 
					GET_SINGLE(ResourceManager)->DrawImage(graphics, EmptyHpIma, hpImaRect.x + i * 28, hpImaRect.y + 7, 30.0, 30.0);
			}
		}
		if (isShop_) {
			if (MenuIma) { // 메뉴
				GET_SINGLE(ResourceManager)->DrawImage2(hdc, MenuIma, menuRect.left, menuRect.top, 200.0, 520.0);
			}
			if (isShop_) {
				Rectangle(hdc, dmgUpRect.left, dmgUpRect.top, dmgUpRect.right, dmgUpRect.bottom); // 데미지 강화 테두리
				Rectangle(hdc, dmgUpBRect.left, dmgUpBRect.top, dmgUpBRect.right, dmgUpBRect.bottom); // 데미지 강화 버튼 테두리
				Rectangle(hdc, bTowRect.left, bTowRect.top, bTowRect.right, bTowRect.bottom); // 기본 타워 구매 테두리
				Rectangle(hdc, bTowBuyRect.left, bTowBuyRect.top, bTowBuyRect.right, bTowBuyRect.bottom); // 기본 타워 구매 버튼 테두리
				SetBkMode(hdc, TRANSPARENT); // 텍스트 배경 없앰
				wchar_t dmgUp_buffer[100]; // 데미지 강화 표기
				swprintf(dmgUp_buffer, 100, L"DMG Upgrade");
				DrawText(hdc, dmgUp_buffer, -1, &dmgUpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Upgrade_buffer[100]; // 강화 버튼 표기
				swprintf(Upgrade_buffer, 100, L"Upgrade");
				DrawText(hdc, Upgrade_buffer, -1, &dmgUpBRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				wchar_t bTow_buffer[100]; // 기본 타워 표기
				swprintf(bTow_buffer, 100, L"Basic Tower");
				DrawText(hdc, bTow_buffer, -1, &bTowRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				wchar_t Buy_buffer[100]; // 구매 버튼 표기
				swprintf(Buy_buffer, 100, L"Buy");
				DrawText(hdc, Buy_buffer, -1, &bTowBuyRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				SetBkMode(hdc, OPAQUE); // 텍스트 배경 복구
			}
		}
		SetBkMode(hdc, TRANSPARENT);
		wchar_t coin_buffer[100]; // 코인 표기
		swprintf(coin_buffer, 100, L"      %d coin", coin);
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, coin_buffer, -1, &coinRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		wchar_t remMob_buffer[100]; // 남은 몬스터 수 표기
		swprintf(remMob_buffer, 100, L"Remaining Mob: %d", remMob);
		DrawText(hdc, remMob_buffer, -1, &remMobRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetBkMode(hdc, OPAQUE);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
};