#pragma once
#include "DxLib.h"
#include <vector>

class EnemyBase
{
public:
	EnemyBase(int modelHandle);
	virtual ~EnemyBase();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw();

	const VECTOR GetPos() const { return m_pos; }
	const float GetRad() const { return m_rad; }
	void SetPos(const VECTOR pos) { m_pos = pos; }

protected:	// 関数
	int GetModelHandle()const { return m_modelHandle; }

	/// <summary>
	/// モデルの位置調整
	/// </summary>
	void AdjustmentModelPos()const;

	// 角度の更新
	void UpdateAngle();

protected:	// 変数
	int m_modelHandle;	// モデルハンドル
	std::vector<int> m_psHs;		// ピクセルシェーダハンドル
	std::vector<int> m_vsHs;		// 頂点シェーダハンドル
	std::vector<int> m_pixelShaderNumbers;	// どのピクセルシェーダを使うか
	std::vector<int> m_vertexShaderNumbers;	// どの頂点シェーダを使うか
	float m_rad;		// 半径
	float m_scale;		// スケール
	VECTOR m_pos;		// 位置
	float m_angle;		// 角度
	VECTOR m_targetDir;	// 向きたい方向のベクトル
};

