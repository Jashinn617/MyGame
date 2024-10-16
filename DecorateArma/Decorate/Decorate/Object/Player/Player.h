#pragma once
#include "DxLib.h"

#include "../CharacterBase.h"

#include "../../Utility/CharacterData.h"

class Camera;
class PlayerState;

/// <summary>
/// �v���C���[
/// </summary>
class Player : public CharacterBase
{
public:		// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Init() override final{/*��������*/ }

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="pToonShader">�g�D�[���V�F�[�_�|�C���^</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) override final;

	/// <summary>
	/// 2D�摜�`��
	/// </summary>
	void Draw2D() override final;

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="targetPos">����̍��W</param>
	void OnDamage(VECTOR targetPos) override final;

	/// <summary>
	/// �U������
	/// </summary>
	void OnAttack() override final;

	/// <summary>
	/// �W�����v��Ԃ̏I��
	/// </summary>
	void EndJump() override final;

	/// <summary>
	/// �W�����v�͂̐ݒ�
	/// </summary>
	/// <param name="jumpPower">�W�����v��</param>
	void SetJumpPower(float jumpPower) { m_jumpPower = jumpPower; }

	/// <summary>
	/// �����蔻��̎�ނ̎擾
	/// </summary>
	/// <returns>�����蔻��̎��</returns>
	ColType GetColType()const override final { return ColType::Player; }

	/// <summary>
	/// �J�����擾
	/// </summary>
	/// <returns>�J�����|�C���^</returns>
	const std::shared_ptr<Camera> GetCamera()const { return m_pCamera; }



private:	// �֐�

	/// <summary>
	/// �p�x�X�V
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// �ړ������X�V
	/// </summary>
	void UpdateMoveDirection();

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <returns>�ړ��l</returns>
	VECTOR Move();

	/// <summary>
	/// �X�e�C�g���Ƃ̏�����
	/// </summary>
	void InitState();

	/// <summary>
	/// �X�e�C�g���Ƃ̍X�V
	/// </summary>
	void UpdateState();

private:	// �ϐ�
	std::shared_ptr<PlayerState> m_pState;	// �X�e�C�g�|�C���^
	std::shared_ptr<Camera> m_pCamera;		// �J�����|�C���^
};