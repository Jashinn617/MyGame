#include "Collision.h"
#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Camera.h"

#include <array>

Collision::~Collision()
{
}

void Collision::Init()
{
}

void Collision::Update(ObjectBase* my, ObjectBase* target)
{
	// 存在しない物体は当たらない
	if (!my->GetInfo().isExist) return;
	// フィールドには当たらない
	if (!target->GetInfo().isExist && target->GetColType() != ObjectBase::ColType::Field) return;
	// Noneには何にもぶつからない
	if (my->GetColType() == ObjectBase::ColType::None) return;

	// オブジェクトタイプがプレイヤーの場合
	if (my->GetColType() == ObjectBase::ColType::Player)
	{
		// ターゲットのオブジェクトタイプがフィールドの場合
		if (my->GetColType() == ObjectBase::ColType::Field)
		{
			dynamic_cast<Player*>(my)->GetCamera()->ColUpdate(target);
			my->MoveCollFieldUpdate(target);
			return;
		}

		// ターゲットのオブジェクトタイプがエネミーの場合
		if (target->GetColType() == ObjectBase::ColType::Enemy)
		{
			dynamic_cast<CharacterBase*>(my)->MoveCollCharacterUpdate(dynamic_cast<CharacterBase*>(target));
			dynamic_cast<CharacterBase*>(my)->AttackPlayerCollEnemy(dynamic_cast<CharacterBase*>(target));
			return;
		}

		// ターゲットのオブジェクトタイプがアイテムの場合
		if (target->GetColType() == ObjectBase::ColType::Item)
		{
			return;
		}
	}

	// オブジェクトタイプがエネミーの場合
	if (my->GetColType() == ObjectBase::ColType::Enemy)
	{
		// ターゲットのオブジェクトタイプがフィールドの場合
		if (my->GetColType() == ObjectBase::ColType::Field)
		{
			my->MoveCollFieldUpdate(target);
			return;
		}

		// ターゲットのオブジェクトタイプがプレイヤーの場合
		if (target->GetColType() == ObjectBase::ColType::Player)
		{
			dynamic_cast<CharacterBase*>(my)->MoveCollCharacterUpdate(dynamic_cast<CharacterBase*>(target));
			dynamic_cast<CharacterBase*>(my)->AttackEnemyCollPlayer(dynamic_cast<CharacterBase*>(target));
			return;
		}

		// ターゲットのオブジェクトタイプがエネミーの場合
		if (target->GetColType() == ObjectBase::ColType::Enemy)
		{
			dynamic_cast<CharacterBase*>(my)->MoveCollCharacterUpdate(dynamic_cast<CharacterBase*>(target));
			return;
		}
	}

	// オブジェクトタイプがアイテムの場合
	if (my->GetColType() == ObjectBase::ColType::Item)
	{
		// ターゲットのオブジェクトタイプがフィールドの場合
		if (my->GetColType() == ObjectBase::ColType::Field)
		{
			my->MoveCollFieldUpdate(target);
			return;
		}
	}
}