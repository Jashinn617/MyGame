#pragma once
#include "DxLib.h"
#include <memory>

using namespace std;

class ModelManager;
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw()const;

private:
	// 位置
	VECTOR m_pos;
	// 3Dモデル
	int m_modelHandle;

	// モデルのポインタ
	unique_ptr<ModelManager> m_pModel;
};

