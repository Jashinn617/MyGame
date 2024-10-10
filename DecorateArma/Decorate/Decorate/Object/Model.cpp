#include "Model.h"

#include <cassert>

Model::Model(const char* fileName):
	m_modelH(-1),
	m_animSpeed(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(0),
	m_isUseCol(false),
	m_isUpdateCol(false),
	m_pos{0.0f,0.0f,0.0f}
{
	// 非同期読み込み設定に変更する
	SetUseASyncLoadFlag(true);
	// モデルのロード
	m_modelH = MV1LoadModel(fileName);
	// モデルのロードに失敗したら止まる
	assert(m_modelH != -1);
	// 非同期読み込み設定を解除する
	SetUseASyncLoadFlag(false);	

	// アニメーション情報のクリア
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::Model(int modelH):
	m_modelH(-1),	// モデルのコピー
	m_animSpeed(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(0),
	m_isUseCol(false),
	m_isUpdateCol(false),
	m_pos{ 0.0f,0.0f,0.0f }
{
	// 非同期読み込み設定に変更する
	SetUseASyncLoadFlag(true);
	// モデルのロード
	m_modelH = MV1DuplicateModel(modelH);
	// モデルのロードに失敗したら止まる
	assert(m_modelH != -1);
	// 非同期読み込み設定を解除する
	SetUseASyncLoadFlag(false);

	// アニメーション情報のクリア
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::~Model()
{
	if (m_isUseCol)	// 当たり判定情報を使用していた場合
	{
		// 当たり判定の情報を削除する
		MV1TerminateCollInfo(m_modelH, -1);
		// 当たり判定情報を使用しない設定にする
		m_isUseCol = false;
	}
}

void Model::Update()
{
}

void Model::Draw()
{
}

void Model::SetPos(VECTOR pos)
{
}

void Model::SetScale(VECTOR scale)
{
}

void Model::SetRot(VECTOR rot)
{
}

void Model::SetAnim(int animNo, bool isLoop, bool isForceChange)
{
}

void Model::ChangeAnim(int animNo, int changeFrameNum, bool isLoop, bool isForceChange)
{
}

bool Model::IsAnimEnd()
{
	return false;
}

void Model::ClearAnimData(AnimData& anim)
{
}

void Model::UpdateAnim(AnimData anim, float animSpeed)
{
}

void Model::UpdateAnimBlendRate()
{
}
