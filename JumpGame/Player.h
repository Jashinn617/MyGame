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
	// �ʒu
	VECTOR m_pos;
	// 3D���f��
	int m_modelHandle;

	// ���f���̃|�C���^
	unique_ptr<ModelManager> m_pModel;
};

