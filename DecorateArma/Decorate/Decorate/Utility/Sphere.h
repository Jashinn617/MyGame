#pragma once
#include "DxLib.h"

#include <memory>

/// <summary>
/// �����蔻��p�̋�
/// </summary>
class Sphere
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="center">���S���W</param>
	/// <param name="radius">���a</param>
	/// <param name="height">����</param>
	Sphere(const VECTOR& center, float radius, float height);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Sphere();

	/// <summary>
	/// �����蔻��̃f�o�b�O�\��
	/// </summary>
	/// <param name="color">���̐F</param>
	void DebugDraw(unsigned int color);

	/// <summary>
	/// �Փ˔���
	/// </summary>
	/// <param name="target">����̓����蔻��̋�</param>
	/// <returns>�������Ă��邩�ǂ���</returns>
	bool IsCollide(const std::shared_ptr<Sphere> target) const;

	/// <summary>
	/// ���̒��S���W�̎擾
	/// </summary>
	/// <returns>�~�̒��S</returns>
	const VECTOR& GetCenter() const { return *m_center; }

	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <returns>���a</returns>
	float GetRadius()const { return m_radius; }

private:	// �ϐ�
	const float m_radius;	// ���a
	const float m_height;	// ����
	const VECTOR* m_center;	// ���S���W
};

