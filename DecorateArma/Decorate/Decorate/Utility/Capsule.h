#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// �����蔻��p�̃J�v�Z��
/// </summary>
class Capsule
{
private:	// �\����
	/// <summary>
	/// �����蔻��p���
	/// </summary>
	struct CollInfo
	{
		VECTOR topPos;			// ����n�_
		VECTOR bottomPos;		// ����I�_
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="topPos">����n�_</param>
	/// <param name="bottomPos">����I�_</param>
	/// <param name="radius">���a</param>
	Capsule(const VECTOR topPos, const VECTOR bottomPos, float radius);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Capsule();

	/// <summary>
	/// �����蔻��̃f�o�b�O�\��
	/// </summary>
	/// <param name="color">�J�v�Z���̐F</param>
	void DebugDraw(unsigned int color);

	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="target">����̓����蔻��̃J�v�Z��</param>
	/// <returns>�������Ă��邩�ǂ���</returns>
	bool IsCollide(const std::shared_ptr<Capsule> target) const;

	/// <summary>
	/// �J�v�Z���̓����蔻��p���̎擾
	/// </summary>
	/// <returns>�����蔻��p���</returns>
	const CollInfo& GetCollInfo()const { return m_collInfo; }

	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <returns>���a</returns>
	float GetRadius()const { return m_radius; }


private:
	float m_radius;				// ���a
	CollInfo m_collInfo;		// �����蔻��p���
};