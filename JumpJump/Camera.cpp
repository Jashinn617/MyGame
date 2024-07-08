#include "DxLib.h"
#include "Camera.h"
#include "Util/Input.h"
#include "Player.h"
#include "Stage/StageTest.h"

/// <summary>
/// 定数定義
/// </summary>
namespace
{
	constexpr float kSpeed = 0.1f;				// 回転速度
	constexpr float kTargetH = 8.0f;			// ターゲットの座標から注視点までの高さ
	constexpr float kStartTargetDir = 30.0f;	// ターゲットとの初期の距離
	constexpr float kColSize = 50.0f;			// カメラ自体の当たり判定のサイズ
}

Camera::Camera():
	m_angle(-DX_PI_F/2),
	m_pos{0,0,0},
	m_targetPos{0,0,0}
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	

}

void Camera::Update(const Input& input, const Player& player, const StageTest& stage)
{
	if (input.IsPressing("R"))
	{
		m_angle -= kSpeed;

		// 角度が-180°より小さくなった場合、角度値が大きくなりすぎないように360°を足す
		if (m_angle < -DX_PI_F)
		{
			m_angle += DX_TWO_PI_F;
		}
	}
	if (input.IsPressing("L"))
	{
		m_angle += kSpeed;

		// 角度が-180°より大きくなった場合、角度値が大きくなりすぎないように360°を引く
		if (m_angle > DX_PI_F)
		{
			m_angle -= DX_TWO_PI_F;
		}
	}

	SetCameraNearFar(1.0f, 200.0f);

	// カメラの注視点の設定
	// ターゲットよりも少し高い位置を注視点にする
	m_targetPos = VAdd(player.GetPos(), VGet(0.0f, kTargetH, 0.0f));

	// カメラの座標を設定する
	/*後で関数化したい*/
	{
		MATRIX RotY;				// カメラの回転に使う行列
		float CameraToTargetDir;	// カメラとターゲットの距離

		// カメラのY軸回転の取得
		RotY = MGetRotY(m_angle);

		// カメラからターゲットまでの初期の距離
		CameraToTargetDir = kStartTargetDir;

		// カメラ座標の計算
		m_pos = VAdd(VTransform(VGet(-CameraToTargetDir, 15.0f, 0.0f), RotY),m_targetPos);

		/*ステージとの当たり判定*/
		// 後でやる
		// 関数化するのはこの部分だけかもしれない

	}

	// カメラの位置を設定する
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);

	DrawFormatString(0, 20, 0xffffff, "Camera:%f,y:%f,z:%f", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "CameraTarget:%f,y:%f,z:%f", m_targetPos.x, m_targetPos.y, m_targetPos.z);

}
