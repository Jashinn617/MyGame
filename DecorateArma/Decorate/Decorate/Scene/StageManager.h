#pragma once
#include "../Utility/Game.h"

#include <memory>

/// <summary>
/// �e�X�e�[�W���Ǘ�����N���X
/// </summary>
class StageManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stageKind">�X�e�[�W�̎��</param>
	StageManager(Game::StageKind stageKind);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~StageManager();

	/// <summary>
	/// ������
	/// </summary>
	void  Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};