#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include "Food.h" 

class Ground :
	public GameObject
{
public:
	Ground(GameObject* parent);
	void Initialize() override;
	std::vector<std::vector<int>> GetMapData() { return mapData_; }
	void Update() override;
	void Draw() override;
	void Release() override;

	void DecEsaCount(FoodType type);
	int GetEsaCount() const { return esaCount_; }
	int GetDekaEsaCount() const { return dekaEsaCount_; } 
private:
	int hModel_;
	int hModelt_;
	int hEsaModel_;
	int hDekaesaModel_;

	std::vector<std::vector<int>> mapData_;
	std::vector<std::vector<int>> objMap_;

	int mapWidth_;
	int mapHeight_;
	int esaCount_ = 0;
	int dekaEsaCount_ = 0; 
};
