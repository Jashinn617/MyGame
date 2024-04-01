#include "EnemyBee.h"

namespace
{
	// 敵のスケール
	constexpr float kScale = 0.005f;
}

EnemyBee::EnemyBee(int modelHandle):
	EnemyBase(modelHandle)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Update()
{
	
	// モデルのスケールを決定する
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// モデルの位置設定
	MV1SetPosition(m_modelHandle, m_pos);

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 90.0f, 0.0f));
}
