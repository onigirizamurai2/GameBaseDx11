#pragma once
#include "Engine/GameObject.h"

// 前方宣言
class Text;

class ResultScene : public GameObject
{
private:
    float timer_;
    int score_; 
    Text* pText_;  

public:
    ResultScene(GameObject* parent);
    ~ResultScene() {}
    void SetScore(int score) { score_ = score; }
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
