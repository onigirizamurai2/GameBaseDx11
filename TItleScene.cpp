#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene"), pText_(nullptr)
{
}

void TitleScene::Initialize()
{
    pText_ = new Text();
    pText_->Initialize();
}

void TitleScene::Update()
{
    if (Input::IsKeyDown(DIK_RETURN)) {
        SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
        if (pManager) {
            pManager->ChangeScene(SCENE_ID_TEST);
        }
    }
}

void TitleScene::Draw()
{
    if (pText_) {
        pText_->Draw(100, 100, "TITLE SCREEN");
        pText_->Draw(100, 150, "PRESS ENTER TO START");
    }
}

void TitleScene::Release()
{
}
