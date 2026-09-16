#include "Food.h"
#include "TestScene.h"
#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h" 

Food::Food(GameObject* parent)
	:GameObject(parent, "Food"), type_(FOODTYPE_NORMAL), hModel_(-1), score_(0)
{
}

Food::~Food()
{
}

void Food::Initialize()
{
	transform_.scale_ = { 0.3f,0.3f,0.3f };
	if (type_ == FoodType::FOODTYPE_NORMAL)
	{
		hModel_ = Model::Load("Esa.fbx");
		score_ = 1;
	}
	else if (type_ == FoodType::FOODTYPE_POWER)
	{
		hModel_ = Model::Load("Dekaesa.fbx");
		score_ = 3;
	}

	SphereCollider* sphereCollider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.5f);
	AddCollider(sphereCollider);
}


void Food::Update()
{
	if (type_ == FoodType::FOODTYPE_POWER)
	{
		transform_.rotate_.y += 1.0f;
	}
}

void Food::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Food::Release()
{
}

void Food::SetFoodType(FoodType type)
{
	type_ = type;
	if (type_ == FoodType::FOODTYPE_NORMAL)
	{
		hModel_ = Model::Load("Esa.fbx");
		score_ = 5;
	}
	else if (type_ == FoodType::FOODTYPE_POWER)
	{
		hModel_ = Model::Load("Dekaesa.fbx");
		transform_.scale_ = { 0.8f, 0.8f, 0.8f };
		score_ = 10;
	}
}

void Food::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		TestScene* testScene = dynamic_cast<TestScene*>(GetParent()->GetParent());
		testScene->AddScore(score_);
		Ground* ground = dynamic_cast<Ground*>(FindObject("Ground"));
		ground->DecEsaCount(type_);
		KillMe();
	}
}
