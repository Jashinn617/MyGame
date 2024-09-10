#include "Collision.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Item/ItemBase.h"
#include "../Object/Camera.h"

#include <array>

Collision::Collision()
{
	/*��������*/
}

Collision::~Collision()
{
	/*��������*/
}

void Collision::Init()
{
	/*��������*/
}

void Collision::Update(ObjectBase* my, ObjectBase* target)
{
	// ���݂��Ȃ����͓̂�����Ȃ�
	if (!my->GetInfo().isExist) return;
	// �t�B�[���h�ɂ͓�����Ȃ�
	if (!target->GetInfo().isExist && target->GetColType() != ObjectBase::ColType::Field) return;
	// None�ɂ͉��ɂ��Ԃ���Ȃ�
	if (my->GetColType() == ObjectBase::ColType::None) return;

	// �I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Player)
	{
		// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���t�B�[���h�̏ꍇ
		if (target->GetColType() == ObjectBase::ColType::Field)
		{
			dynamic_cast<Player*>(my)->GetCamera()->ColUpdate(target);
			my->MoveCollFieldUpdate(target);
			return;
		}

		// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���G�l�~�[�̏ꍇ
		if (target->GetColType() == ObjectBase::ColType::Enemy)
		{
			// �v���C���[���_���[�W���󂯂Ă����ԂłȂ����
			if (!my->IsDamage())
			{
				dynamic_cast<CharacterBase*>(my)->AttackPlayerCollEnemy(dynamic_cast<CharacterBase*>(target));
				return;		
			}
			else
			{
				dynamic_cast<CharacterBase*>(my)->MoveCollCharacterUpdate(dynamic_cast<CharacterBase*>(target));
				return;
			}
		}

		// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���A�C�e���̏ꍇ
		if (target->GetColType() == ObjectBase::ColType::Item)
		{
			dynamic_cast<CharacterBase*>(my)->PlayerToItem(dynamic_cast<CharacterBase*>(target));
			return;
		}
	}

	// �I�u�W�F�N�g�^�C�v���G�l�~�[�̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Enemy)
	{
			// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���t�B�[���h�̏ꍇ
			if (target->GetColType() == ObjectBase::ColType::Field)
			{

				my->MoveCollFieldUpdate(target);

				return;
			}

			// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
			if (target->GetColType() == ObjectBase::ColType::Player)
			{
				if (!target->IsDamage())
				{
					dynamic_cast<CharacterBase*>(my)->AttackEnemyCollPlayer(dynamic_cast<CharacterBase*>(target));
					return;
				}
				else
				{
					dynamic_cast<CharacterBase*>(my)->MoveCollCharacterUpdate(dynamic_cast<CharacterBase*>(target));
					return;
				}
				
			}
	}

	// �I�u�W�F�N�g�^�C�v���A�C�e���̏ꍇ
	if (my->GetColType() == ObjectBase::ColType::Item)
	{
		// �^�[�Q�b�g�̃I�u�W�F�N�g�^�C�v���t�B�[���h�̏ꍇ
		if (target->GetColType() == ObjectBase::ColType::Field)
		{
			my->MoveCollFieldUpdate(target);
			return;
		}
	}
}