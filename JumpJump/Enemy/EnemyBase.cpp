#include "EnemyBase.h"

EnemyBase::EnemyBase(int modelHandle):
	m_modelHandle(-1),
	m_rad(0),
	m_scale(1),
	m_pos{0,0,0},
	m_angle{0,0,0}
{
	// モデルの読み込み
	m_modelHandle = MV1DuplicateModel(modelHandle);
}

EnemyBase::~EnemyBase()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::Draw()
{
	// モデルの描画
	MV1DrawModel(m_modelHandle);

	// 当たり判定のデバッグ表示
#ifdef _DEBUG
	VECTOR pos = VAdd(MV1GetPosition(m_modelHandle), VGet(0, m_rad, 0));

	DrawSphere3D(pos, m_rad, 32, 0xff0000, 0xff00000, false);
#endif // _DEBUG

}