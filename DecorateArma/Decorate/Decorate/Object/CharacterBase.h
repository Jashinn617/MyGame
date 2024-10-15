#pragma once
#include "ObjectBase.h"

class Circle;

/// <summary>
/// �I�u�W�F�N�g�̒��ł��L�����N�^�[�̊��N���X
/// </summary>
class CharacterBase : public ObjectBase
{
public:	// �\����

	/// <summary>
	/// �X�e�[�^�X���
	/// </summary>
	struct StatusData
	{
		float spd = 0.0f;	// ���x
	};

	/// <summary>
	/// �ړ��p�X�e�[�^�X���
	/// </summary>
	struct MoveStatusData
	{
		float walkSpeed = 0.0f;		// �������x
		float runSpeed = 0.0f;		// ���葬�x
		float acceleration = 0.0f;	// �����x
		float rotSpeed = 0.0f;		// ��]���x
	};

	/// <summary>
	/// �A�j���[�V�������
	/// </summary>
	struct AnimData
	{
		int8_t idle = 0;		// �ҋ@
		int8_t walk = 0;		// ����
		int8_t run = 0;			// ����
		int8_t jumpStart = 0;	// �W�����v�n��
		int8_t jumpIdle = 0;	// �W�����v��
		int8_t Damage = 0;		// �_���[�W
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharacterBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() override = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override = 0;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pToonShader">�g�D�[���V�F�[�_�|�C���^</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader)override = 0;



protected:	// �֐�
	/// <summary>
	/// �p�x�����炩�ɕω�������֐�
	/// </summary>
	/// <param name="nowAngle">���݂̊p�x</param>
	/// <param name="nextAngle">�ڕW�p�x</param>
	void SmoothAngle(float& nowAngle, float nextAngle);

protected:	// �ϐ�
	bool m_isDead;						// ���񂾂��ǂ���
	std::shared_ptr<Circle> m_pCircle;	// �����蔻��p�̉~�̃|�C���^

	StatusData m_statusData{};			// �X�e�[�^�X���
	MoveStatusData m_moveData{};		// �ړ����
	AnimData m_animData{};				// �A�j���[�V�������
};