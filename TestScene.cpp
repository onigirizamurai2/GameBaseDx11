#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "ResultScene.h"
#include "TItleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Text.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"), myScore(0), isClear_(false), clearTimer_(0.0f), timeLimit_(15.0f)
{
}

void TestScene::Initialize()
{
	Player* pPlayer = Instantiate <Player>(this);
	pGround_ = Instantiate<Ground>(this);
	pPlayer->SetGround(pGround_);

	Camera::SetPosition({ 0,10,-20 });
	Camera::SetTarget({ 0,0,0 });

	pText_ = new Text;
	pText_->Initialize();

	clearTimer_ = 0.0f;
	timeLimit_ = 15.0f;
}

void TestScene::Update()
{
	if (!isClear_)
	{
		timeLimit_ -= 1.0f / 60.0f;
		if (timeLimit_ <= 0.0f)
		{
			timeLimit_ = 0.0f;
			nextSceneID_ = SCENE_ID_RESULT;
		}
	}

	if (isClear_)
	{
		clearTimer_ += 1.0f / 60.0f;
		if (clearTimer_ >= 5.0f)
		{
			nextSceneID_ = SCENE_ID_RESULT;
		}
	}

	if (nextSceneID_ != currentSceneID_) {
		SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
		if (pManager) {
			pManager->SetSavedScore(myScore); 
			pManager->ChangeScene(static_cast<SCENE_ID>(nextSceneID_)); 
			return;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void TestScene::Draw()
{
	if (nextSceneID_ == SCENE_ID_RESULT)
	{
		return;
	}

	std::string scrText = "SCORE:" + std::to_string(myScore);
	pText_->Draw(20, 20, scrText.c_str());

	if (pGround_ != nullptr)
	{
		std::string feedText = "ESA:" + std::to_string(pGround_->GetEsaCount());
		pText_->Draw(20, 50, feedText.c_str());

		std::string bigFeedText = "DEKAESA:" + std::to_string(pGround_->GetDekaEsaCount());
		pText_->Draw(20, 80, bigFeedText.c_str());
	}

	std::string limitText = "TIME:" + std::to_string(static_cast<int>(timeLimit_)) + "s";
	pText_->Draw(1000, 20, limitText.c_str());

	if (isClear_)
	{
		pText_->Draw(300, 200, "=============================");
		pText_->Draw(350, 240, "        GAME CLEAR !!        ");
		pText_->Draw(300, 280, "=============================");

		int remainingTime = 5 - static_cast<int>(clearTimer_);
		if (remainingTime < 0) remainingTime = 0;

		std::string timerText = "Result in " + std::to_string(remainingTime) + "s...";
		pText_->Draw(350, 340, timerText.c_str());
	}
}

void TestScene::Release()
{
	if (pText_ != nullptr)
	{
		delete pText_;
		pText_ = nullptr;
	}
}

void TestScene::AddScore(int val)
{
	myScore += val;
}
