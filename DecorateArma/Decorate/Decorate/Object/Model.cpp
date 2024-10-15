#include "Model.h"

#include <cassert>

Model::Model(const char* fileName):
	m_modelH(-1),
	m_animFrame(0),
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
	m_animFrame(0),
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
	// �����蔻������g�p���Ă����ꍇ
	if (m_isUseCol)
	{
		// �����蔻��̏����폜����
		MV1TerminateCollInfo(m_modelH, -1);
		// �����蔻������g�p���Ȃ��ݒ�ɂ���
		m_isUseCol = false;
	}
}

void Model::Update()
{
	// �A�j���[�V������i�߂�
	m_animFrame++;

	// �A�j���[�V��������������ꍇ
	if (m_animFrame >= m_animChangeFrameTotal)
	{
		// �A�j���[�V�����̍X�V������
		UpdateAnim(m_prevAnim);
		UpdateAnim(m_nextAnim);
		// �t���[�������Z�b�g����
		m_animFrame = 0;
	}

	/*�w��t���[�������ăA�j���[�V������ύX����*/
	// �A�j���[�V�����̐؂�ւ���i�߂�
	m_animChangeFrame++;
	// �؂�ւ��t���[�������t���[�����ɒB�����ꍇ
	if (m_animChangeFrame > m_animChangeFrameTotal)
	{
		// �؂�ւ��t���[���������t���[�������z���Ȃ��悤�ɂ���
		m_animChangeFrame = m_animChangeFrameTotal;
	}
	// �A�j���[�V�����̃u�����h���̐ݒ�
	UpdateAnimBlendRate();

	// �����蔻��f�[�^�̍X�V
	if (m_isUseCol && m_isUpdateCol)
	{
		// �R���W�������̍\�z
		MV1RefreshCollInfo(m_modelH, m_colFrameIndex);
	}
}

void Model::Draw()
{
	// ���f���̕`��
	MV1DrawModel(m_modelH);
}

void Model::SetPos(VECTOR pos)
{
	// �ʒu���̐ݒ�
	m_pos = pos;
	MV1SetPosition(m_modelH, m_pos);
}

void Model::SetScale(VECTOR scale)
{
	// �X�P�[���̐ݒ�
	MV1SetScale(m_modelH, scale);
}

void Model::SetRot(VECTOR rot)
{
	// ��]�̐ݒ�
	MV1SetRotationXYZ(m_modelH, rot);
}

void Model::SetAnim(int animNo, bool isLoop, bool isForceChange)
{
	/* �w�肳�ꂽ�A�j���[�V�����Ɠ����A�j���[�V�������Đ����������ꍇ��
	 �Đ������Ȃ��ݒ肾�������A���ɓ����A�j���[�V�������Đ�����Ă����ꍇ��
	 �������Ȃ�*/
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// �A�j���[�V�������c���Ă����ꍇ
	if (m_prevAnim.attachNo != -1)
	{
		// ���̃A�j���[�V�������I������
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	// �A�j���[�V�������c���Ă����ꍇ
	if (m_nextAnim.attachNo != -1)
	{
		// ���̃A�j���[�V�������I������
		MV1DetachAnim(m_modelH, m_nextAnim.attachNo);
		ClearAnimData(m_nextAnim);
	}

	// �V�����A�j���[�V������ݒ肷��
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// �ύX�ɂ�����t���[������ݒ肷��
	m_animChangeFrameTotal = 1;
	m_animChangeFrame = 1;	
}

void Model::ChangeAnim(int animNo, int changeFrameNum, bool isLoop, bool isForceChange)
{
	/* �w�肳�ꂽ�A�j���[�V�����Ɠ����A�j���[�V�������Đ����������ꍇ��
	 �Đ������Ȃ��ݒ肾�������A���ɓ����A�j���[�V�������Đ�����Ă����ꍇ��
	 �������Ȃ�*/
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// �A�j���[�V�������c���Ă����ꍇ�͏I������
	if (m_prevAnim.attachNo != -1)
	{
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	// ���ݍĐ����̃A�j���[�V�������Â����̂ɂ���
	m_prevAnim = m_nextAnim;

	// �V�����A�j���[�V������ݒ肷��
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// �ύX�ɂ�����t���[������ݒ肷��
	m_animChangeFrameTotal = changeFrameNum;
	m_animChangeFrame = 0;

	// �A�j���[�V�����̃u�����h���̐ݒ�
	UpdateAnimBlendRate();
}

bool Model::IsAnimEnd()
{
	// ���[�v����A�j���[�V�����̏ꍇ��false�ŕԂ�
	if (m_nextAnim.isLoop)return false;

	// ���݂̃A�j���[�V�����̍Đ�
	float time = MV1GetAttachAnimTime(m_modelH, m_nextAnim.attachNo);

	/*���݂̃A�j���[�V�����̍Đ����Ԃ��A�j���[�V�����̑��Đ����Ԃ���
	�傫��������true�Ԃ�*/
	if (time >= m_nextAnim.totalTime)return true;
	
	// �����łȂ����false��Ԃ�
	return false;
}

void Model::ClearAnimData(AnimData& anim)
{
	// �A�j���[�V������������������
	anim.animNo = -1;
	anim.attachNo = -1;
	anim.totalTime = 0.0f;
	anim.isLoop = false;
}

void Model::UpdateAnim(AnimData anim, float animSpeed)
{
	// �A�j���[�V�����������ݒ肳��Ă��Ȃ���Ή������Ȃ�
	if (anim.animNo == -1)return;

	// �A�j���[�V�����̍X�V
	float nowFrame = MV1GetAttachAnimTime(m_modelH, anim.attachNo);
	nowFrame += animSpeed;
	// ���݂̃t���[���������Đ����Ԃ����傫�������ꍇ
	if (nowFrame > anim.totalTime)
	{
		// �A�j���[�V���������[�v������
		nowFrame -= anim.totalTime;
	}
	// �A�j���[�V�����̍Đ����Ԃ̐ݒ�
	MV1SetAttachAnimTime(m_modelH, anim.attachNo, nowFrame);
}

void Model::UpdateAnimBlendRate()
{
	// �A�j���[�V�����ω��̃t���[�����ɉ������u�����h�����v�Z����
	float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	// �u�����h����1�ȏ�ɂȂ�Ȃ��悤�ɂ���
	if (rate > 1.0f)rate = 1.0f;

	/*�u�����h���̐ݒ�*/
	// rate���i�ނɂ�O�̃A�j���[�V�����̃u�����h���������Ă���
	MV1SetAttachAnimBlendRate(m_modelH, m_prevAnim.attachNo, 1.0f - rate);
	MV1SetAttachAnimBlendRate(m_modelH, m_nextAnim.attachNo, rate);
}
