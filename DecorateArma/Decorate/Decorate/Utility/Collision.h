#pragma once

class ObjectBase;

/// <summary>
/// �����蔻��p�N���X
/// </summary>
class Collision
{
public:	// �֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Collision();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Collision();

	/// <summary>
	/// �����蔻��X�V����
	/// </summary>
	/// <param name="my">���g</param>
	/// <param name="target">����</param>
	void UpdateCollision(ObjectBase* my, ObjectBase* target);
};

