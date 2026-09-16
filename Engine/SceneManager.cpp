#include "../TestScene.h"
#include "../TitleScene.h"
#include "../ResultScene.h"
#include "SceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"

//コンストラクタ
SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
};

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//更新
void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		KillAllChildren();

		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE:  Instantiate<TitleScene>(this);  break;
		case SCENE_ID_TEST:   Instantiate<TestScene>(this);   break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break; 
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}
