#include "ItemBase.h"

#include "../Player/Player.h"

#include "../ObjectBase.h"
#include "../Model.h"
#include "../Circle.h"

#include "../../Util/Time.h"
#include "../../Util/SoundManager.h"

#include "../../Shader/ToonShader.h"

#include "../../Effect/Effekseer3DManager.h"

#include <assert.h>

using namespace CharacterData;

namespace
{
	constexpr int kDeadExistTime = 60;		// 死んでから完全に消えるまでの時間
	constexpr float kColHeight = -10.0f;	// 当たり判定の高さ
}

ItemBase::ItemBase():
	m_moveDirectionVec{0,0,0},
	m_colHeight(kColHeight)
{
	// 情報の初期化
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;
	m_statusData.spd = 0.0f;
	m_objSize = 0.0f;
}

ItemBase::ItemBase(VECTOR pos):
	m_moveDirectionVec{ 0,0,0 },
	m_colHeight(kColHeight)
{
	// 情報の初期化
	m_info.pos = pos;
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.modelH = -1;
	m_info.isExist = true;
	m_statusData.spd = 0.0f;
	m_objSize = 0.0f;
}

ItemBase::~ItemBase()
{
	/*処理無し*/
}

void ItemBase::Init()
{
	/*処理無し*/
}

void ItemBase::Update()
{
	// 移動ベクトルの計算
	m_info.vec = MoveUpdate();

	// モデル更新
	m_pModel->Update();

	// 移動ベクトルを現在座標に足す
	m_info.pos = VAdd(m_info.pos, m_info.vec);

	// 座標の設定
	m_pModel->SetPos(m_info.pos);
}

void ItemBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	// モデルの描画
	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// 頂点タイプ取得
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);

		// シェーダの設定
		pToonShader->SetShader(shaderType);
		// 描画
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// シェーダを使わない設定に戻す
	pToonShader->ShaderEnd();

	// 当たり判定の描画
	m_pCircle->DebugDraw();
}

void ItemBase::OnGet()
{
	// エフェクトを流す
	Effekseer3DManager::GetInstance().Add("ItemGet",
		Effekseer3DManager::PlayType::Normal, this, m_info.pos);
	// アイテムの取得音を鳴らす
	SoundManager::GetInstance().Play("ItemGet");
	// 死亡フラグを立てる
	m_isDead = true;
	// 存在を消す
	m_info.isExist = false;
}

void ItemBase::StageEnd()
{
	// ゲームの終了フラグを立てる
	m_isStageEnd = true;
}

void ItemBase::InitMoveSpeed(float moveSpeed)
{
	// 移動速度の初期化
	m_moveData.walkSpeed = moveSpeed;
	m_moveData.runSpeed = 0.0f;
	m_moveData.acceleration = 0.0f;
}

void ItemBase::MoveDirectionUpdate()
{
	/*処理無し*/
}

VECTOR ItemBase::MoveUpdate()
{
	/*処理無し*/
	return VGet(0.0f,0.0f,0.0f);
}
