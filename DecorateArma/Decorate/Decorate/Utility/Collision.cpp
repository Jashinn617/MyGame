#include "Collision.h"

#include "../Object/ObjectBase.h"
#include "../Object/Player/Player.h"
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
	}

	// ターゲットのオブジェクトタイプがエネミーの場合
	if (my->GetColType() == ObjectBase::ColType::Enemy)
	{

	}

	// ターゲットのオブジェクトタイプがアイテムの場合
	if (my->GetColType() == ObjectBase::ColType::Item)
	{

	}
}
