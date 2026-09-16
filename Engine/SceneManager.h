#pragma once
#include "global.h"
#include "GameObject.h"

class TitleScene;
class TestScene;
class ResultScene;

enum SCENE_ID
{
	SCENE_ID_TITLE = 0,
	SCENE_ID_TEST,
	SCENE_ID_RESULT,
};

class SceneManager : public GameObject
{
public:

	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void ChangeScene(SCENE_ID next);

	void SetSavedScore(int score) { savedScore_ = score; }
	int GetSavedScore() const { return savedScore_; }

private:
	SCENE_ID currentSceneID_;	
	SCENE_ID nextSceneID_;	

	int savedScore_ = 0;

};
