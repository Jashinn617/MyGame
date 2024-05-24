#include "DxLib.h"
#include "Camera.h"
#include "Util/Input.h"
#include "Player.h"
#include "Stage/StageTest.h"

void Camera::Init()
{
	m_angle = DX_PI_F;

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

	// カメラの注視点の設定
	// ターゲットよりも少し高い位置を注視点にする
	m_targetpos = VAdd(player.GetPos(), VGet(0.0f, kTargetH, 0.0f));

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
		m_pos = VAdd(VTransform(VGet(-CameraToTargetDir, 0.0f, 0.0f), RotY));

		/*ステージとの当たり判定*/
		// 後でやる
		// 関数化するのはこの部分だけかもしれない

	}

	// カメラの位置を設定する
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetpos);

}
