#include "ItemBase.h"

#include "../Player/Player.h"

#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"

#include "../../Util/Time.h"
#include "../../Util/Input.h"

#include "../../Shader/ToonShader.h"

#include <assert.h>

using namespace CharacterData;

namespace
{
	constexpr int kDeadExistTime = 60;	// 死んでから完全に消えるまでの時間
	constexpr float kColHeight = 20.0f;	// 当たり判定の高さ
}

ItemBase::ItemBase():
	m_moveDirectionVec{0,0,0},
	m_createTime(0),
	m_colHeight(kColHeight)
{
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 10;

	m_objSize = 0.0f;

	m_updateFunc = &ItemBase::IdleStateUpdate;

	// 死んでからの時間
	m_deadTime = std::make_shared<Time>(kDeadExistTime);

	// 死亡時シェーダ
}

ItemBase::ItemBase(VECTOR pos):
	m_moveDirectionVec{ 0,0,0 },
	m_createTime(0),
	m_colHeight(kColHeight)
{
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;

	m_statusData.spd = 10;

	m_objSize = 0.0f;

	m_updateFunc = &ItemBase::IdleStateUpdate;

	// 死んでからの時間
	m_deadTime = std::make_shared<Time>(kDeadExistTime);

	// 死亡時シェーダ
}

ItemBase::~ItemBase()
{
	/*処理無し*/
}

void ItemBase::Init()
{
}

void ItemBase::Update(Input& input)
{
	// 状態に合わせて更新処理をする
	StateTransitionUpdate();
	(this->*m_updateFunc)();

	// 移動ベクトルと回転行列をかけ、回転に伴った移動ベクトルを取得する
	m_info.vec = MoveUpdate();
	GravityUpdate();

	// 座標の設定
	m_pModel->SetPos(m_info.pos);

	// 角度の設定
	m_pModel->SetRot(VGet(0.0f, m_angle + DX_PI_F, 0.0f));

	// シェーダ更新
}

void ItemBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		pToonShader->SetShader(shaderType);
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	pToonShader->ShaderEnd();
}

void ItemBase::Draw2D()
{
}

void ItemBase::OnGet()
{
	m_isDead = true;
}

void ItemBase::StageClear()
{
	m_updateFunc = &ItemBase::DeadStateUpdate;
}

void ItemBase::InitMoveSpeed(float moveSpeed)
{
	// 移動速度の初期化
	m_moveData.walkSpeed = moveSpeed;
	m_moveData.runSpeed = 0.0f;
	m_moveData.acceleration = 0.0f;
}

void ItemBase::AngleUpdate()
{
	// 向きたい方向
	float nextAngle = atan2(m_moveDirectionVec.x, m_moveDirectionVec.z);

	// 滑らかに方向を向く
	SmoothAngle(m_angle, nextAngle);
}

void ItemBase::MoveDirectionUpdate()
{
}

VECTOR ItemBase::MoveUpdate()
{
	return VECTOR();
}

void ItemBase::StateTransitionUpdate()
{
}

bool ItemBase::StateTransitionMove()
{
	m_updateFunc = &ItemBase::MoveStateUpdate;

	return true;
}

bool ItemBase::StateTransitionDead()
{
	m_updateFunc = &ItemBase::DeadStateUpdate;

	return true;
}

void ItemBase::IdleStateUpdate()
{

}

void ItemBase::MoveStateUpdate()
{
	// 移動速度の計算
	m_moveSpeed = min(m_moveSpeed + m_moveData.acceleration, m_moveData.walkSpeed);
}

void ItemBase::DeadStateUpdate()
{
	m_moveSpeed = 0.0f;

	static int DeadTime = 0;
	
	// 既定の時間を超えたら存在を消す
	if (m_deadTime->Update()) m_info.isExist = false;
}
