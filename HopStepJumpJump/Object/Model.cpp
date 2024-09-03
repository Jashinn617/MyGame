#include "Model.h"

#include <assert.h>

Model::Model(const char* fileName):
	m_pos{0,0,0},
	m_modelH(-1),
	m_animSpeed(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(-1),
	m_isUseCol(false),
	m_isUpdateCol(false)
{
	// ���f���̓ǂݍ���
	m_modelH = MV1LoadModel(fileName);
	assert(m_modelH != -1);	// ���[�h���s

	// �A�j���[�V�������̃N���A
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::Model(int modelH):
	m_pos{ 0,0,0 },
	m_modelH(-1),
	m_animSpeed(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(-1),
	m_isUseCol(false),
	m_isUpdateCol(false)
{
	// ���f���̃R�s�[
	m_modelH = MV1DuplicateModel(modelH);
	assert(m_modelH != -1);	// �R�s�[���s

	// �A�j���[�V�������̃N���A
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::~Model()
{
	// �����蔻��̏����g�p���Ă����ꍇ
	if (m_isUseCol)
	{
		// �����蔻��̏����폜����
		MV1TerminateCollInfo(m_modelH, -1);
		m_isUseCol = false;
	}
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelH);
}

void Model::Update()
{
	m_animSpeed++;
	// �A�j���[�V��������������ꍇ
	if (m_animSpeed >= m_animChangeFrameTotal)
	{
		// �A�j���[�V�����̍X�V������
		UpdateAnim(m_prevAnim);
		UpdateAnim(m_nextAnim);
		m_animSpeed = 0;
	}

	// �w��t���[�������ăA�j���[�V������ύX����
	m_animChangeFrame++;
	if (m_animChangeFrame > m_animChangeFrameTotal)
	{
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
	// �T�C�Y�̐ݒ�
	MV1SetScale(m_modelH, scale);
}

void Model::SetRot(VECTOR rot)
{
	// ��]���̐ݒ�
	MV1SetRotationXYZ(m_modelH, rot);
}

void Model::SetAnim(int animNo, bool isLoop, bool isForceChange)
{
	// isForceChange��false�������ꍇ�A
	// ���ɃA�j���[�V�������Đ�����Ă����ꍇ�͍Đ����Ȃ�
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// �ȑO�̃A�j���[�V�������c���Ă����ꍇ�͏I������
	if (m_prevAnim.attachNo != -1)
	{
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	if (m_nextAnim.attachNo != -1)
	{
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_nextAnim);
	}

	// �V�����A�j���[�V������ݒ肷��
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// �ύX�Ɋ|����t���[������ݒ肷��
	m_animChangeFrameTotal = 1;
	m_animChangeFrame = 1;
}

void Model::ChangeAnim(int animNo, bool isLoop, bool isForceChange, int changeFrameNum)
{
	// isForceChange��false�������ꍇ�A
	// ���ɃA�j���[�V�������Đ�����Ă����ꍇ�͍Đ����Ȃ�
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// �ȑO�̃A�j���[�V�������c���Ă����ꍇ�͏I������
	if (m_prevAnim.attachNo != -1)
	{
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	// ���ݍĐ����̃A�j���[�V�������Â�����
	m_prevAnim = m_nextAnim;

	// �V�����A�j���[�V������ݒ肷��
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// �ύX�Ɋ|����t���[������ݒ肷��
	m_animChangeFrameTotal = changeFrameNum;
	m_animChangeFrame = 0;

	// �A�j���[�V�����̃u�����h���̐ݒ�
	UpdateAnimBlendRate();
}

bool Model::IsAnimEnd()
{
	// Loop�A�j���̏ꍇ��false��Ԃ�
	if (m_nextAnim.isLoop)return false;

	// ���݂̃A�j���[�V�����̍Đ�����
	float time = MV1GetAttachAnimTime(m_modelH, m_nextAnim.attachNo);
	// ���݂̃A�j���[�V�����̍Đ����Ԃ��A�j���[�V�����̑��Đ����Ԃ���
	// �傫��������true��Ԃ�
	if (time >= m_nextAnim.totalTime) return true;

	return false;
}

void Model::ClearAnimData(AnimData& anim)
{
	anim.animNo = -1;
	anim.attachNo = -1;
	anim.totalTime = 0.0f;
	anim.isLoop = false;
}

void Model::UpdateAnim(AnimData anim, float animSpeed)
{
	// �A�j���[�V�������ݒ肳��Ă��Ȃ������ꍇ�͉������Ȃ�
	if (anim.attachNo == -1)return;

	// �A�j���[�V�����̍X�V
	float nowTime = MV1GetAttachAnimTime(m_modelH, anim.attachNo);
	nowTime += animSpeed;
	if (nowTime > anim.totalTime)
	{
		if (anim.isLoop)
		{
			// �A�j���[�V���������[�v������
			nowTime -= anim.totalTime;
		}
		else
		{
			nowTime = anim.totalTime;
		}
	}
	MV1SetAttachAnimTime(m_modelH, anim.attachNo, nowTime);
}

void Model::UpdateAnimBlendRate()
{
	// �A�j���[�V�����ω��̃t���[�����ɉ������u�����h����ݒ肷��
	float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	// �u�����h����1�ȏ�ɂȂ�Ȃ��悤�ɂ���
	if (rate > 1.0f)rate = 1.0f;

	MV1SetAttachAnimBlendRate(m_modelH, m_prevAnim.attachNo, 1.0f - rate);
	MV1SetAttachAnimBlendRate(m_modelH, m_nextAnim.attachNo, rate);
}
