#include "EnemyBee.h"


namespace
{
	constexpr float kPlayAnimSpeed = 0.5f;	// アニメーション速度
	constexpr int kAnimNum = 2;				// アニメーション番号
}

EnemyBee::EnemyBee(int modelHandle) :
	EnemyBase(modelHandle),
	m_currentAnimNo(-1),
	m_isTurn(false)
{
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Init()
{
	MV1SetPosition(m_modelHandle, m_pos);
	// アニメーションの設定
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, kAnimNum, -1, false);
}

void EnemyBee::Update()
{
	// アニメーションの更新
	UpdateAnim(m_currentAnimNo);

	// 角度の更新
	UpdateAngle();
}

bool EnemyBee::UpdateAnim(int attachNo)
{
	bool isLoop = false;

	/*アニメーションを進行させる*/
	// 現在の再生カウント
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);
	// アニメーションを進める
	now += kPlayAnimSpeed;
	// 現在再生中のアニメーションの総カウント
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);

	// アニメーションをループさせる
	while (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	// アニメーションを進めた時間に設定する
	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void EnemyBee::Move()
{

}

