#pragma once
#include "DxLib.h"
#include <memory>

using namespace std;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const;

	/// <summary>
	/// ���f���n���h���̎擾
	/// </summary>
	/// <returns></returns>
	int GetModelHandle()const { return m_modelHandle; }

	const VECTOR& GetPos()const;
	const VECTOR& GetDir()const { return m_dir; }
	const float GetRad()const { return m_rad; }

private:
	// �ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_move;

	// �ړ���
	VECTOR m_velocity;
	// ��]����
	VECTOR m_dir;
	// 3D���f��
	int m_modelHandle;
	// ���a
	float m_rad;
	// �W�����v��
	float m_jumpPower;
	// �W�����v�����ǂ���
	bool m_isJump;

private:	// �萔
	static constexpr float kGravity = 0.025f;	// �d��
	static constexpr float kJumpHeight = 0.5f;	// �W�����v��
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;	// Y�������̌���


};

