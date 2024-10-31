#include "Collision.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
#include "../Object/Player/Shot.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Camera.h"

Collision::Collision()
{
	/*処理無し*/
}

Collision::~Collision()
{
	/*処理無し*/
}

void Collision::UpdateCollision(ObjectBase* my, ObjectBase* target)
{
	// 存在しない物体は当たらない
	if (!my->GetInfo().isExist && !target->GetInfo().isExist) return;
	// 種類が設定設定されてなければには何もぶつからない
	if (my->GetColType() == ObjectBase::ColType::None) return;

	// オブジェクトタイプがプレイヤーの場合
	if (my->GetColType() == ObjectBase::ColType::Player)
	{
		// ターゲットのオブジェクトがフィールドの場合
		if (target->GetColType() == ObjectBase::ColType::Field)
		{
			// カメラがフィールドにめり込まないようにする
			dynamic_cast<Player*>(my)->GetCamera()->ColUpdate(target);
			my->MoveCollField(target);
			return;
		}

		// ターゲットのオブジェクトがエネミーの場合
		if (target->GetColType() == ObjectBase::ColType::Enemy)
		{
			// キャラクター同士衝突判定
			dynamic_cast<CharacterBase*>(my)->MoveCollCharacter(dynamic_cast<CharacterBase*>(target));
			// ショット衝突判定
			dynamic_cast<Player*>(my)->GetShot()->OnAttack(dynamic_cast<CharacterBase*>(target));
			// 攻撃衝突判定
			dynamic_cast<Player*>(my)->OnAttack(dynamic_cast<CharacterBase*>(target));
			// 強攻撃衝突判定
			dynamic_cast<Player*>(my)->OnHardAttack(dynamic_cast<CharacterBase*>(target));

			return;
		}
	}

	// オブジェクトタイプがエネミーの場合
	if (my->GetColType() == ObjectBase::ColType::Enemy)
	{
		// ターゲットのオブジェクトがフィールドの場合
		if (target->GetColType() == ObjectBase::ColType::Field)
		{
			my->MoveCollField(target);
			return;
		}

		// ターゲットのオブジェクトがプレイヤーの場合
		if (target->GetColType() == ObjectBase::ColType::Player)
		{
			// キャラクター同士衝突判定
			dynamic_cast<CharacterBase*>(my)->MoveCollCharacter(dynamic_cast<CharacterBase*>(target));
			// 索敵範囲衝突判定
			dynamic_cast<EnemyBase*>(my)->IsSearchRange(dynamic_cast<CharacterBase*>(target));

			return;
		}
	}

	// オブジェクトタイプがアイテムの場合
	if (my->GetColType() == ObjectBase::ColType::Item)
	{

	}
}
