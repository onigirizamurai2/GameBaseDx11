#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Food.h"

namespace
{
    using std::vector;
}

Ground::Ground(GameObject* parent)
    : GameObject(parent, "Ground"),
    hModel_(-1),
    hModelt_(-1),
    hEsaModel_(-1),
    hDekaesaModel_(-1),
    mapWidth_(-1),
    mapHeight_(-1)
{
    CsvReader csvData;
    csvData.Load("map.csv"); 
    mapWidth_ = csvData.GetWidth(); 
    mapHeight_ = csvData.GetHeight() / 2;

    mapData_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));
    objMap_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));

    for (int x = 0; x < mapWidth_; x++)
    {
        for (int y = 0; y < mapHeight_; y++)
        {
            mapData_[y][x] = csvData.GetValue(x, y);
        }
    }
    for (int x = 0; x < mapWidth_; x++)
    {
        for (int y = 0; y < mapHeight_; y++)
        {
            objMap_[y][x] = csvData.GetValue(x, y + mapHeight_);
        }
    }
}

void Ground::Initialize()
{
    hModel_ = Model::Load("jimen3.fbx");
    hModelt_ = Model::Load("block.fbx");

    esaCount_ = 0;
    dekaEsaCount_ = 0; 

    for (int x = 0; x < mapWidth_; x++)
    {
        for (int y = 0; y < mapHeight_; y++)
        {
            if (mapData_[y][x] == 1) {
                continue;
            }
            if (objMap_[y][x] == 2)
            {
                Food* food = (Food*)Instantiate<Food>(this);
                food->SetPosition({ -9.0f + x * 2.0f, 0.5f, 9.0f - y * 2.0f });
                food->SetFoodType(FoodType::FOODTYPE_POWER);

                dekaEsaCount_++;
            }
            else if (objMap_[y][x] == 0)
            {
                Food* food = (Food*)Instantiate<Food>(this);
                food->SetPosition({ -9.0f + x * 2.0f, 0.5f, 9.0f - y * 2.0f });
                food->SetFoodType(FoodType::FOODTYPE_NORMAL);

                esaCount_++;
            }
        }
    }
}


void Ground::Update()
{
}

void Ground::Draw()
{
    // 地面の描画
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    // 壁（ブロック）の描画: mapData_が1の場所に配置
    for (int j = 0; j < mapHeight_; j++) {
        for (int i = 0; i < mapWidth_; i++) {
            if (mapData_[j][i] == 1) {
                Transform tr;
                tr.position_ = { -9.0f + i * 2.0f, 0.0f, 9.0f - j * 2.0f };
                Model::SetTransform(hModelt_, tr);
                Model::Draw(hModelt_);
            }
        }
    }
}

void Ground::Release()
{
}

void Ground::DecEsaCount(FoodType type)
{
    if (type == FoodType::FOODTYPE_NORMAL)
    {
        if (esaCount_ > 0)
        {
            esaCount_--;
        }
    }
    else if (type == FoodType::FOODTYPE_POWER)
    {
        if (dekaEsaCount_ > 0)
        {
            dekaEsaCount_--;
        }
    }
}


