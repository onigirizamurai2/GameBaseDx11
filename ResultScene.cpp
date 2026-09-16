#include "ResultScene.h"
#include "TItleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

ResultScene::ResultScene(GameObject* parent)
    : GameObject(parent), timer_(0.0f), pText_(nullptr)
{
}

void ResultScene::Initialize()
{
    timer_ = 0.0f;

    SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
    if (pManager != nullptr) {
        score_ = pManager->GetSavedScore();
    }

    pText_ = new Text();
    pText_->Initialize();
}


void ResultScene::Update()
{
    timer_ += 1.0f / 60.0f;

    if (timer_ >= 5.0f || Input::IsKeyDown(DIK_RETURN)) {
        SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
        if (pManager) {
            pManager->ChangeScene(SCENE_ID_TITLE);
        }
    }
}

void ResultScene::Draw()
{
    if (pText_ != nullptr) {
        std::string resText = "TOTAL SCORE: " + std::to_string(score_);
        pText_->Draw(400, 250, resText.c_str());
    }
}

void ResultScene::Release()
{
    if (pText_ != nullptr) {
        pText_->Release();
        delete pText_;
        pText_ = nullptr;
    }
}
