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
	// �񓯊��ǂݍ��ݐݒ�ɕύX����
	SetUseASyncLoadFlag(true);
	// ���f���̃��[�h
	m_modelH = MV1LoadModel(fileName);
	// ���f���̃��[�h�Ɏ��s������~�܂�
	assert(m_modelH != -1);
	// �񓯊��ǂݍ��ݐݒ����������
	SetUseASyncLoadFlag(false);	

	// �A�j���[�V�������̃N���A
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::Model(int modelH):
	m_modelH(-1),	// ���f���̃R�s�[
	m_animSpeed(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(0),
	m_isUseCol(false),
	m_isUpdateCol(false),
	m_pos{ 0.0f,0.0f,0.0f }
{
	// �񓯊��ǂݍ��ݐݒ�ɕύX����
	SetUseASyncLoadFlag(true);
	// ���f���̃��[�h
	m_modelH = MV1DuplicateModel(modelH);
	// ���f���̃��[�h�Ɏ��s������~�܂�
	assert(m_modelH != -1);
	// �񓯊��ǂݍ��ݐݒ����������
	SetUseASyncLoadFlag(false);

	// �A�j���[�V�������̃N���A
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::~Model()
{
	if (m_isUseCol)	// �����蔻������g�p���Ă����ꍇ
	{
		// �����蔻��̏����폜����
		MV1TerminateCollInfo(m_modelH, -1);
		// �����蔻������g�p���Ȃ��ݒ�ɂ���
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
