#include "EnemyBase.h"
#include <assert.h>
#include <math.h>

namespace
{
	constexpr float kAngleSpeed = 0.2f;	// 回転速度
	constexpr float kScale = 0.05f;		// スケール
}


EnemyBase::EnemyBase(int modelHandle):
	m_modelHandle(-1),
	m_rad(4),
	m_scale(1),
	m_pos{0,0,0},
	m_angle(-1),
	m_targetDir{0,0,0}
{
	// モデルの読み込み
	m_modelHandle = MV1DuplicateModel(modelHandle);
	assert(m_modelHandle != -1);
	// シェーダのロード
	m_psHs.push_back(LoadPixelShader("MV1PixelShader.pso"));
	assert(m_psHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader4Frame.vso"));
	assert(m_vsHs.back() != -1);
	m_vsHs.push_back(LoadVertexShader("MV1VertexShader8Frame.vso"));
	assert(m_vsHs.back() != -1);

	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));

	// モデルのトライアングルリスト毎に対応するシェーダを設定する
	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		switch (MV1GetTriangleListVertexType(m_modelHandle,i))
		{
		case DX_MV1_VERTEX_TYPE_4FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(0);
		case DX_MV1_VERTEX_TYPE_8FRAME:
			m_pixelShaderNumbers.push_back(0);
			m_vertexShaderNumbers.push_back(1);
		default:
			m_pixelShaderNumbers.push_back(-1);
			m_vertexShaderNumbers.push_back(-1);
			break;
		}
	}
}

EnemyBase::~EnemyBase()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void EnemyBase::Draw()
{
	// 当たり判定のデバッグ表示
#ifdef _DEBUG
	VECTOR pos = VAdd(MV1GetPosition(m_modelHandle), VGet(0, m_rad, 0));
	VECTOR overheadPos = VAdd(pos, VGet(0, 2, 0));

	DrawSphere3D(pos, m_rad, 32, 0xff0000, 0xff00000, false);
	DrawSphere3D(overheadPos, 3, 32, 0x0000ff, 0xff000ff, false);
#endif // _DEBUG

	auto num = MV1GetTriangleListNum(m_modelHandle);
	for (int i = 0; i < num; i++)
	{
		if (m_vertexShaderNumbers[i] && m_pixelShaderNumbers[i] == -1)
		{
			MV1SetUseOrigShader(false);
			SetUseVertexShader(-1);
			SetUsePixelShader(-1);
		}
		else
		{
			MV1SetUseOrigShader(true);
			SetUseVertexShader(m_vsHs[m_vertexShaderNumbers[i]]);
			SetUsePixelShader(m_psHs[m_pixelShaderNumbers[i]]);
		}
		MV1DrawTriangleList(m_modelHandle, i);
	}
}

void EnemyBase::AdjustmentModelPos() const
{
	// モデルの位置設定
	MV1SetPosition(m_modelHandle, m_pos);
}

void EnemyBase::UpdateAngle()
{
	float targetAngle;	// 目標角度
	float difference;	// 目標角度と現在の角度の差

	targetAngle = static_cast<float>(atan2(m_targetDir.x, m_targetDir.z));

	difference = targetAngle - m_angle;

	// ある方向からある方向差が180°以上になることは無い
	// そのため、差の値が180°以上になっていたら修正しておく
	if (difference < -DX_PI_F)// -180以下だったら360を足す
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)// 180以上だったら360を引く
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差を0に近づける
	if (difference > 0.0f)// 差がプラスの場合は引く
	{
		difference -= kAngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else// 差がマイナスの場合は足す
	{
		difference += kAngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// 角度を更新する
	m_angle = targetAngle - difference;
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}