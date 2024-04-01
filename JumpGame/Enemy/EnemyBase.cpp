#include "EnemyBase.h"

EnemyBase::EnemyBase(int modelHandle):
	m_modelHandle(-1),
	m_pos{0,0,0}
{
	m_modelHandle = MV1DuplicateModel(modelHandle);
}

EnemyBase::~EnemyBase()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);
}
