#include "Collision.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Camera.h"

Collision::Collision()
{
	/*��������*/
}

Collision::~Collision()
{
	/*��������*/
}

void Collision::UpdateCollision(ObjectBase* my, ObjectBase* target)
{
	// ���݂��Ȃ����͓̂�����Ȃ�
	if (!my->GetInfo().isExist && !target->GetInfo().isExist) return;
	// ��ނ��ݒ�ݒ肳��ĂȂ���΂ɂ͉����Ԃ���Ȃ�
	if (my->GetColType() == ObjectBase::ColType::None) return;

	// �I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Player)
	{
		// �^�[�Q�b�g�̃I�u�W�F�N�g���t�B�[���h�̏ꍇ
		if (target->GetColType() == ObjectBase::ColType::Field)
		{
			// �J�������t�B�[���h�ɂ߂荞�܂Ȃ��悤�ɂ���
			dynamic_cast<Player*>(my)->GetCamera()->ColUpdate(target);
			my->MoveCollField(target);
			return;
		}
	}

	// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���G�l�~�[�̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Enemy)
	{

	}

	// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���A�C�e���̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Item)
	{

	}
}
