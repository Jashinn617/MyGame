#include "Effect.h"
#include "../Util/Time.h"

EffectLoopFollow::EffectLoopFollow(const char* FileName, ObjectBase* pObject):
	m_pObject(pObject)
{
	SetData(FileName);
}

EffectLoopFollow::~EffectLoopFollow()
{
	StopEffekseer3DEffect(m_data.playingEffectH);
}

void EffectLoopFollow::Update()
{
	if (m_isEnd)
	{
		return;
	}

	// �I�u�W�F�N�g�̃|�C���^��null�ɂȂ�����
	// �G�t�F�N�g�̍Đ����I������
	if (m_pObject == nullptr)
	{
		m_isEnd = true;
		return;
	}

	// �I�u�W�F�N�g�����݂��Ă��Ȃ�������
	// �G�t�F�N�g�̍Đ����I������
	if (!m_pObject->GetInfo().isExist)
	{
		m_isEnd = true;
		return;
	}

	// �G�t�F�N�g�̍Đ�
	Play();

	// �G�t�F�N�g�̊p�x�̐ݒ�
	SetRotationPlayingEffekseer3DEffect
		(m_data.playingEffectH,
		m_pObject->GetInfo().rot.x,
		m_pObject->GetInfo().rot.y,
		m_pObject->GetInfo().rot.z);

	// �G�t�F�N�g�̍��W�̐ݒ�
	SetPosPlayingEffekseer3DEffect
		(m_data.playingEffectH,
		m_pObject->GetInfo().pos.x,
		m_pObject->GetInfo().pos.y,
		m_pObject->GetInfo().pos.z);
}

void EffectLoopFollow::Play()
{
	// ���U���g�̏�����
	int result = 0;

	// �G�t�F�N�g�̍Đ����͍Đ����Ȃ�
	if (IsEffekseer3DEffectPlaying(m_data.playingEffectH) == 0) return;

	// �G�t�F�N�g�̍Đ�
	result = m_data.playingEffectH = PlayEffekseer3DEffect(m_data.resouceH);
	assert(result != -1);

	// �G�t�F�N�g�̑傫���̐ݒ�
	result = SetScalePlayingEffekseer3DEffect(
		m_data.playingEffectH,
		m_data.size,
		m_data.size,
		m_data.size);
	assert(result != -1);

	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	result = SetSpeedPlayingEffekseer3DEffect
	(m_data.playingEffectH, m_data.speed);

	assert(result != -1);
}

EffectFollow::EffectFollow(const char* FileName, ObjectBase* pObject):
	m_pObject(pObject)
{
	SetData(FileName);
	m_data.playingEffectH = PlayEffekseer3DEffect(m_data.resouceH);
	Play();
}

EffectFollow::~EffectFollow()
{
	StopEffekseer3DEffect(m_data.playingEffectH);
}

void EffectFollow::Update()
{
	if (m_isEnd) return;

	// �G�t�F�N�g�̍Đ����I��������I������
	if (IsEffekseer3DEffectPlaying(m_data.playingEffectH) != 0)
	{
		m_isEnd = true;
		return;
	}

	// �I�u�W�F�N�g�̃|�C���^��null�ɂȂ�����
	// �G�t�F�N�g�̍Đ����I������
	if (m_pObject == nullptr)
	{
		m_isEnd = true;
		return;
	}

	// �I�u�W�F�N�g�����݂��Ă��Ȃ�������
	// �G�t�F�N�g�̍Đ����I������
	if (!m_pObject->GetInfo().isExist)
	{
		m_isEnd = true;
		return;
	}

	// �G�t�F�N�g�̍Đ�
	Play();

}

void EffectFollow::Play()
{
	// ���U���g�̏�����
	int result = 0;

	// �G�t�F�N�g�̊p�x�̐ݒ�
	SetRotationPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_pObject->GetInfo().rot.x,
		m_pObject->GetInfo().rot.y,
		m_pObject->GetInfo().rot.z);

	// �G�t�F�N�g�̍��W�̐ݒ�
	SetPosPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_pObject->GetInfo().pos.x,
		m_pObject->GetInfo().pos.y,
		m_pObject->GetInfo().pos.z);

	// �G�t�F�N�g�̑傫���̐ݒ�
	result = SetScalePlayingEffekseer3DEffect(
		m_data.playingEffectH,
		m_data.size,
		m_data.size,
		m_data.size);
	assert(result != -1);

	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	result = SetSpeedPlayingEffekseer3DEffect
	(m_data.playingEffectH, m_data.speed);

	assert(result != -1);
}

EffectLoop::EffectLoop(const char* FileName, VECTOR pos, VECTOR rot):
	m_pos(pos),
	m_rot(rot)
{
	SetData(FileName);
	Play();
}

EffectLoop::~EffectLoop()
{
	StopEffekseer3DEffect(m_data.playingEffectH);
}

void EffectLoop::Update()
{
	if (m_isEnd) return;

	Play();
}

void EffectLoop::Play()
{
	// �G�t�F�N�g�̍Đ����͍Đ����Ȃ�
	if (IsEffekseer3DEffectPlaying(m_data.playingEffectH) == 0) return;

	// ���U���g�̏�����
	int result = 0;
	// �G�t�F�N�g�̍Đ�
	result = m_data.playingEffectH = PlayEffekseer3DEffect(m_data.resouceH);
	assert(result != -1);
	

	// �G�t�F�N�g�̍��W�̐ݒ�
	SetPosPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// �G�t�F�N�g�̊p�x�̐ݒ�
	SetRotationPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_rot.x,
		m_rot.y,
		m_rot.z);

	// �G�t�F�N�g�̑傫���̐ݒ�
	result = SetScalePlayingEffekseer3DEffect(
		m_data.playingEffectH,
		m_data.size,
		m_data.size,
		m_data.size);
	assert(result != -1);

	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	result = SetSpeedPlayingEffekseer3DEffect
	(m_data.playingEffectH, m_data.speed);
	assert(result != -1);
}

EffectNormal::EffectNormal(const char* FileName, VECTOR pos, VECTOR rot):
	m_pos(pos),
	m_rot(rot)
{
	SetData(FileName);
	Play();
}

EffectNormal::~EffectNormal()
{
	StopEffekseer3DEffect(m_data.playingEffectH);
}

void EffectNormal::Update()
{
	if (m_isEnd) return;

	if (IsEffekseer3DEffectPlaying(m_data.playingEffectH) != 0)
	{
		m_isEnd = true;
		return;
	}
}

void EffectNormal::Play()
{
	// ���U���g�̏�����
	int result = 0;
	// �G�t�F�N�g�̍Đ�
	result = m_data.playingEffectH = PlayEffekseer3DEffect(m_data.resouceH);
	assert(IsEffekseer3DEffectPlaying(m_data.playingEffectH) == 0);


	// �G�t�F�N�g�̍��W�̐ݒ�
	SetPosPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// �G�t�F�N�g�̊p�x�̐ݒ�
	SetRotationPlayingEffekseer3DEffect
	(m_data.playingEffectH,
		m_rot.x,
		m_rot.y,
		m_rot.z);

	// �G�t�F�N�g�̑傫���̐ݒ�
	result = SetScalePlayingEffekseer3DEffect(
		m_data.playingEffectH,
		m_data.size,
		m_data.size,
		m_data.size);

	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	result = SetSpeedPlayingEffekseer3DEffect
	(m_data.playingEffectH, m_data.speed);
	assert(result != -1);
}
