#pragma once
#include "DxLib.h"
#include <memory>

using namespace std;

class Input;

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
	void Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw()const;
	
	/// <summary>
	/// �ʒu���擾����
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR& GetPos()const;
	/// <summary>
	/// ���a���擾����
	/// </summary>
	/// <returns>���a</returns>
	const float GetRad()const { return m_rad; }

private:	// �֐�
	/// <summary>
	/// �W�����v����
	/// </summary>
	/// <param name="input">����</param>
	void Jump(Input& input);

	/// <summary>
	/// �d�͂̏����ƒn�ʂ̏���
	/// </summary>
	void GravityAndGround();

private:	// �ϐ�
	VECTOR m_pos;		// �ʒu
	VECTOR m_move;		// �ړ���

	int m_modelHandle;	// 3D���f��

	float m_rad;		// ���a

	float m_jumpPower;	// �W�����v��
	bool m_isJump;		// �W�����v�����ǂ���
	int m_jumpSe;		// �W�����v����SE

private:	// �萔
	static constexpr float kSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);	// ���x
	static constexpr float kScale = 0.002f;												// �X�P�[��
	static constexpr float kRadius = 0.3f;												// �����蔻��p�̔��a
	static constexpr float kGravity = 0.025f;											// �d��
	static constexpr float kJumpHeight = 0.5f;											// �W�����v��
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;							// Y�������̌���
	static constexpr float kGroundPosY = 0.4f;											// �n�ʂ�Y�ʒu
};

