#pragma once
#include "Engine/GameObject.h"

enum SCENE_ID : int;
class SceneManager;
class Text;
class Ground;

class TestScene : public GameObject
{
public:
	TestScene(GameObject* parent);
	~TestScene() override = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void AddScore(int val);
	int GetScore() const { return myScore; }
private:
	int myScore;
	bool isClear_;
	float clearTimer_;
	float timeLimit_;

	Text* pText_ = nullptr;
	Ground* pGround_ = nullptr;

	int currentSceneID_;
	int nextSceneID_;
};
