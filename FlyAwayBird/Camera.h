#pragma once
#include "DxLib.h"

class Player;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player">�v���C���[�ւ̎Q��</param>
	void Update(const Player& player);

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR GetPos()const { return m_pos; }

private:	// �ϐ�
	VECTOR m_pos;	// �ʒu
};

