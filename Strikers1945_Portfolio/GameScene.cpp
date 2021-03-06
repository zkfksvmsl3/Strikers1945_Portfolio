#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"

#include "Monster.h"
#include "Timer.h"
#include "Boss.h"
#include "AirMonster.h"
#include "BigAirPlan.h"
#include "MidAirPlan.h"
#include "Fish.h"
#include "UI.h"

#pragma comment (lib,"winmm")

GameScene::GameScene()
{
	sceneType = eSceneType::SCENE_GAME1;
	coolTime = 2.0f;

	isStart1 = true;
	isStart2 = true;
	isStart3 = true;
	isStart4 = true;
	isStart5 = true;
	isStart6 = true;
	isStart7 = true;
	isStart8 = true;
	isStart9 = true;
	isStart10 = true;
}

GameScene::~GameScene()
{

}

bool GameScene::Init()
{
	//GameNode::Init(true);
	//=========================================================
	GAMESYS->SetScore(0);

	// 시간
	RunTimer = 0;
	startTimer = GetTickCount(); // 전체 시작시간
	backImg = IMAGEMANAGER->FindImage("Stage_1");
	backImg->SetX(100.f);
	backImg->SetY((-18165.f + static_cast<float>(WINSIZEY)));
	_y = backImg->GetY();

	rcGameClient.left = 100.0f;
	rcGameClient.right = 900.0f;
	rcGameClient.top = 0.f;
	rcGameClient.bottom = static_cast<float>(WINSIZEY);

	ui = new UI();
	ui->Init();
	// 플레이어
	//player = new Player;
	//GAMESYS->SetPlayer(player);
	player = GAMESYS->GetPlayer();
	// 몬스터


	//
	//monster1 = new Monster;
	//monster1->Init(MONSTER_TYPE_NONE, 0, 100);

	//monster2 = new Monster;
	//monster2->Init(MONSTER_TYPE_NONE, WINSIZEX, 100);
	//player = new Player;
	//GAMESYS->SetPlayer(player);
	
	//boss = new Boss();
	//boss->Init();

	//=========================
	leftRect = RectMake(0, 0, 100, WINSIZEY);
	rightRect = RectMake(900, 0, 100, WINSIZEY);
	deltaTime = TIMEMANAGER->getElapsedTime();
	//=========================

	return true;
}

void GameScene::Release()
{
	//GameNode::Release();
	//=========================================================
	std::list<Monster*>::iterator it;
	for (it = monsterList.begin(); it != monsterList.end(); it++)
	{
		(*it)->Release();
	}
	monsterList.clear();
	backImg->Release();
	player->Release();
	SAFE_DELETE(player);
	SAFE_DELETE(boss);
	//=========================================================
	//=========================================================

}

void GameScene::Update()
{
	ui->Update();
	// BackGround
	_y -= 2.f;
	backImg->SetY(_y);

	//
	//GameNode::Update();
	//=========================================================
	// 시간
	RunTimer = GetTickCount() - startTimer; // 전체시간
	currentTime += TIMEMANAGER->getElapsedTime();
	coolTime -= deltaTime;
	// 플레이어
	player->Update();

	if (GAMESYS->IsGameClear())
	{
		if (player->GetY() <= 0)
		{
			SCENEMANAGER->ChangeScene(eSceneType::SCENE_CLEAR);
			GAMESYS->SetIsGameClear(false);
			return;
		}
	}

// 테스트
	if(GAMESYS->IsGameOver())
	{
		RunTimer = 0;
		startTimer = GetTickCount();
		GAMESYS->SetIsGameOver(false);
		return;
	}
	if (coolTime <= 0.0f  && currentTime < 60 + deltaTime) // 2초마다 나옴 60초 이전까지 랜덤한 위치에서 나옴
	{
 		coolTime = 2.0f;
		int iRand = RAND->getInt(6); // 0~5의 값을 랜덤하게 가져옴
		GAMEPOS randIndex1;
		GAMEPOS randIndex2;

		switch (iRand)
		{
		case 0:
			randIndex1 = GAMEPOS::G_LEFT1;
			randIndex2 = GAMEPOS::G_RIGHT2;
			break;
		case 1:
			randIndex1 = GAMEPOS::G_LEFT2;
			randIndex2 = GAMEPOS::G_RIGHT3;
			break;
		case 2:
			randIndex1 = GAMEPOS::G_LEFT3;
			randIndex2 = GAMEPOS::G_RIGHT1;
			break;
		case 3:
			randIndex1 = GAMEPOS::G_RIGHT1;
			randIndex2 = GAMEPOS::G_LEFT2;
			break;
		case 4:
			randIndex1 = GAMEPOS::G_RIGHT2;
			randIndex2 = GAMEPOS::G_LEFT3;
			break;
		case 5:
			randIndex1 = GAMEPOS::G_RIGHT3;
			randIndex2 = GAMEPOS::G_LEFT1;
			break;
		}

		Monster* monster = new AirMonster(randIndex1);
		monster->Init(TEXT("air_Monster"), 8, MonsterType::RandomType, randIndex2);
		monsterList.push_back(monster);		
	}
		
	// 몬스터
	//=============================== 30초 ~ 1분 ===================================

	if (currentTime > 15.0f && currentTime < 16.f) // 30초 : 1번 왼쪽 -> 오른쪽 위 [ 1]
	{
		if (isStart1)
		{
			AppearType1();
			isStart1 = false;
		}
	}
	if (currentTime > 25.0f && currentTime < 3326.0f) // 32초 :  오른쪽 -> 왼쪽 위 [2] 
	{
		if (isStart2)
		{
			AppearType2();
			isStart2 = false;
		}
	}
	if (currentTime > 35.0f && currentTime < 36.0f) // 35초 : 위 -> 아래 중심으로 이동 (중간 캐릭터 ) 
	{
		if (isStart3)
		{
			isStart3 = false;
			Monster* bigAirPlan = new BigAirPlan(GAMEPOS::G_UPDOWN1);
			bigAirPlan->Init(TEXT("BigAirPlan"), 1, MonsterType::MiddleType1, GAMEPOS::G_CENTER1);

			monsterList.push_back(bigAirPlan);


			int width = 0;
			std::list<Monster*>::iterator it;
			for (it = monsterList.begin(); it != monsterList.end(); it++)
			{
				if ((*it)->GetType() == MonsterType::MiddleType1)
				{
					width = (*it)->GetImage()->GetFrameWidth();
					(*it)->OffectX(width);
				}
			}
		}
		
	}
	if (currentTime > 40.0f && currentTime < 41.0f) // 40초 : 1번 2번 같이 생성
	{
		if (isStart4)
		{
			AppearType1();
			AppearType2();
			isStart4 = false;
		}
	}
	if (currentTime > 50.0f && currentTime < 51.0f) // 50초 : 중간 2 생성 -> 위 아래 
	{
		if (isStart5)
		{
			isStart5 = false;
			Monster* midAirPlan = new MidAirPlan(GAMEPOS::G_LEFT3);
			midAirPlan->Init(TEXT("MidAirPlan"), 1, MonsterType::MiddleType2, GAMEPOS::G_RIGHT3);

			monsterList.push_back(midAirPlan);

			int width = 0;
			std::list<Monster*>::iterator it;
			for (it = monsterList.begin(); it != monsterList.end(); it++)
			{
				if ((*it)->GetType() == MonsterType::MiddleType2)
				{
					width = (*it)->GetImage()->GetFrameWidth();
					(*it)->OffectX(width);
				}
			}
		}
		
	}

	//=============================== 1분 ~ 1분30초 ===================================

	if (currentTime > 60.0f && currentTime < 61.0f) // 1분 : 중간 크기 2마리
	{
		if (isStart6)
		{
			isStart6 = false;
			Monster* bigAirPlan1 = new BigAirPlan(GAMEPOS::G_UPDOWN1);
			bigAirPlan1->Init(TEXT("BigAirPlan"), 2, MonsterType::MiddleType1, GAMEPOS::G_CENTER1);

			monsterList.push_back(bigAirPlan1);

			Monster* bigAirPlan2 = new BigAirPlan(GAMEPOS::G_UPDOWN2);
			bigAirPlan2->Init(TEXT("BigAirPlan"), 2, MonsterType::MiddleType1, GAMEPOS::G_CENTER2);

			monsterList.push_back(bigAirPlan2);


			int width = 0;
			std::list<Monster*>::iterator it;
			for (it = monsterList.begin(); it != monsterList.end(); it++)
			{
				if ((*it)->GetType() == MonsterType::MiddleType1)
				{
					width = (*it)->GetImage()->GetFrameWidth();
					(*it)->OffectX(width);
				}
			}
		}
		
	}
	if (currentTime > 65.0f && currentTime < 66.0f) // 1분 5초 : 1번 2번 같이 생성
	{
		if (isStart7)
		{
			isStart7 = false;
			AppearType1();
			AppearType2();
		}
		
	}
	if (currentTime > 65.0f && currentTime < 66.0f) // 1분 15초 : 중간3 2마리 양쪽 사이드 생성 
	{
		if (isStart8)
		{
			isStart8 = false;
			Monster* fish1 = new Fish(GAMEPOS::G_LEFT3);
			fish1->Init(TEXT("fish"), 1, MonsterType::MiddleType3, GAMEPOS::G_RIGHT3);

			monsterList.push_back(fish1);

			Monster* fish2 = new Fish(GAMEPOS::G_RIGHT3);
			fish2->Init(TEXT("fish"), 2, MonsterType::MiddleType3, GAMEPOS::G_LEFT3);

			monsterList.push_back(fish2);

			int width = 0;
			std::list<Monster*>::iterator it;
			for (it = monsterList.begin(); it != monsterList.end(); it++)
			{
				if ((*it)->GetType() == MonsterType::MiddleType3)
				{
					width = (*it)->GetImage()->GetFrameWidth();
					(*it)->OffectX(width);
				}
			}

		}



		
	}

	//========================== 1분 30초! ( 보스 등장 ) ==============================
	
	//GAMESYS->DeleteObject(monsterList); // 지우는함수 부분
	//80
	if( currentTime > 80.0f && currentTime < 81.0f) // 1분 20초 : 보스 
	{
		if (isStart9)
		{
			isStart9 = false;
			boss = new Boss();
			boss->Init(WINSIZEX / 2, -500);
			GAMESYS->SetBoss(boss);
		}
		

	}

	if (!monsterList.empty())
	{
		if (currentTime >= 80.f)
		{
			GAMESYS->DeleteObject(monsterList);
			if (!boss->GetIsLive())
			{
				GAMESYS->SetIsGameClear(true);
				//boss->Release();
				//SAFE_DELETE(boss);
			}
		}
	}
	
	
	
	std::list<Monster*>::iterator it;

	for (it = monsterList.begin(); it != monsterList.end(); it++)
	{
		(*it)->Update();
	}

	if (NULL != boss)
	{
		boss->Update();
	}
	GAMESYS->CollisionObject(monsterList);
	//monster1->Update();
	//monster2->Update();

	//player->Update();
	//boss->Update();
	//GAMESYS->CollisionCharacter(_monster, rcTest);
}

void GameScene::Render(HDC hdc)
{
	//GameNode::Render(hdc);

	//HDC	backDC = (this->GetBackBuffer())->GetMemDC();
	//PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=========================================================
	
	backImg->LoopRender(hdc, &rcGameClient, 0, _y);

	ui->Render(hdc);
	TIMEMANAGER->Render(hdc);

	TCHAR choiceTime1[100] = { 0, };
	_stprintf_s(choiceTime1, sizeof(choiceTime1), TEXT("runTimer : %d"), RunTimer);
	TextOut(hdc, WINSIZEX / 2 - 270, 180, TEXT(choiceTime1), _tcslen(TEXT(choiceTime1)));

	// 플레이어

	// 몬스터
	std::list<Monster*>::iterator it;
	for (it = monsterList.begin(); it != monsterList.end(); it++)
	{
		(*it)->Render(hdc);
	}
	DrawObject(hdc, leftRect, 1, RGB(0, 0, 0), RECTANGLE);
	DrawObject(hdc, rightRect, 1, RGB(0, 0, 0), RECTANGLE);

	if (NULL != boss)
	{
		boss->Render(hdc);
	}
	player->Render(hdc);


	//monster1->Render(hdc);
	//monster2->Render(hdc);

	//player->Render(hdc);
	//boss->Render(hdc);

	//Rectangle(backDC, rcTest.left, rcTest.top, rcTest.right, rcTest.bottom);
	//=========================================================
	
	//=========================================================

	//this->GetBackBuffer()->Render(hdc, 0, 0);
}

void GameScene::AppearType1()
{
	isStart1 = false;
	for (int i = 0; i < 5; i++)
	{
		Monster* monster1 = new AirMonster(GAMEPOS::G_LEFT1);
		monster1->Init(TEXT("air_Monster"), 1, MonsterType::Type1, GAMEPOS::G_RIGHT3);

		monsterList.push_back(monster1);
	}

	int offset = 100;
	int width = 0;
	int height = 0;
	std::list<Monster*>::iterator it;
	for (it = monsterList.begin(); it != monsterList.end(); it++)
	{
		if ((*it)->GetType() == MonsterType::Type1)
		{
			width = (*it)->GetImage()->GetFrameWidth();
			(*it)->OffectX(width + offset);
			offset += 50;
		}
	}
}

void GameScene::AppearType2()
{
	for (int i = 0; i < 5; i++)
	{
		Monster* monster2 = new AirMonster(GAMEPOS::G_RIGHT1);
		monster2->Init(TEXT("air_Monster"), 2, MonsterType::Type2, GAMEPOS::G_LEFT3);

		monsterList.push_back(monster2);
	}

	int offset = 100;
	int width = 0;
	int height = 0;
	std::list<Monster*>::iterator it;
	for (it = monsterList.begin(); it != monsterList.end(); it++)
	{
		if ((*it)->GetType() == MonsterType::Type2)
		{
			width = (*it)->GetImage()->GetFrameWidth();
			(*it)->OffectX(width + offset);
			offset += 50;
		}
	}
}