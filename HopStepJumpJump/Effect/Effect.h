#pragma once
#include "Effekseer3DManager.h"

#include <memory>

// �Ǐ]�ƃ��[�v������G�t�F�N�g�̃N���X
class EffectLoopFollow : public Effekseer3DManager::EffectBehavior
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="FileName">�t�@�C���p�X</param>
	/// <param name="pObject">�I�u�W�F�N�g</param>
	EffectLoopFollow(const char* FileName, ObjectBase* pObject);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EffectLoopFollow();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	void Play() override final;

private:
	ObjectBase* m_pObject;	// �I�u�W�F�N�g
};

// �Ǐ]����G�t�F�N�g�̃N���X
class EffectFollow : public Effekseer3DManager::EffectBehavior
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="FileName">�t�@�C���p�X</param>
	/// <param name="pObject">�I�u�W�F�N�g</param>
	EffectFollow(const char* FileName, ObjectBase* pObject);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EffectFollow();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	void Play() override final;

private:
	ObjectBase* m_pObject;	// �I�u�W�F�N�g
};

// ���[�v����G�t�F�N�g�̃N���X
class EffectLoop : public Effekseer3DManager::EffectBehavior
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="FineName">�t�@�C���p�X</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">�p�x</param>
	EffectLoop(const char* FileName,
		VECTOR pos,
		VECTOR rot = VGet(0.0f, 0.0f, 0.0f));

	virtual ~EffectLoop();

	void Update() override final;
	void Play() override final;

private:
	VECTOR m_pos;
	VECTOR m_rot;
};

// ���̑��̃G�t�F�N�g�̃N���X
class EffectNormal : public Effekseer3DManager::EffectBehavior
{
public:
	EffectNormal(const char* FileName,
		VECTOR pos,
		VECTOR rot = VGet(0.0f, 0.0f, 0.0f));

	virtual ~EffectNormal();

	void Update() override final;
	void Play() override final;

private:
	VECTOR m_pos;
	VECTOR m_rot;
};

