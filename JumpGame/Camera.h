#pragma once
#include "DxLib.h"

class Player;

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Camera();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Camera();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="playr">�v���C���[�̃N���X</param>
	void Update(const Player& playr);

	/// <summary>
	/// �|�W�V������getter/setter
	/// </summary>
	/// <returns>�|�W�V����</returns>
	const VECTOR& GetPos()const { return m_pos; }

private:
	VECTOR m_pos;	// �|�W�V����
};

