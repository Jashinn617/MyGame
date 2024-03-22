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

	const VECTOR& GetPos()const { return m_pos; }
	const VECTOR& GetDir()const { return m_dir; }

private:
	// �ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_velocity;
	// ��]����
	VECTOR m_dir;
	// 3D���f��
	int m_modelHandle;

};

