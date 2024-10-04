#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"

class ItemBase : public CharacterBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemBase();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期座標</param>
	ItemBase(VECTOR pos);

	/// <summary>
	///	デストラクタ
	/// </summary>
	virtual ~ItemBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();
	
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader);

	/// <summary>
	/// 存在するかどうか
	/// </summary>
	/// <returns>存在フラグ</returns>
	bool GetExist()const { return m_info.isExist; }

	/// <summary>
	/// 取得処理
	/// </summary>
	void OnGet();

	/// <summary>
	/// 自身の当たり判定情報
	/// </summary>
	/// <returns>当たり判定情報</returns>
	virtual ColType GetColType()const { return ColType::Item; }

	/// <summary>
	/// ゲーム終了時処理
	/// </summary>
	void StageEnd() override final;

protected:
	/// <summary>
	/// 移動速度の初期化
	/// </summary>
	/// <param name="moveSpeed">移動速度</param>
	void InitMoveSpeed(float moveSpeed);

	/// <summary>
	/// 移動方向の更新
	/// </summary>
	virtual void MoveDirectionUpdate();

	/// <summary>
	/// 移動更新
	/// </summary>
	/// <returns>移動ベクトル</returns>
	virtual VECTOR MoveUpdate();



protected:	// 変数
	float m_colHeight;					// 当たり判定の高さをモデルの中心にする
	VECTOR m_moveDirectionVec;			// 移動方向ベクトル
};