#pragma once
#include "DxLib.h"

#include <vector>
#include <memory>

/// <summary>
/// 3Dモデルの管理を行うクラス
/// </summary>
class Model
{
public:		// 関数
	/// <summary>
	/// コンストラクタ
	/// ファイル名を指定してロードを行う
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	Model(const char* fileName);

	/// <summary>
	/// コンストラクタ
	/// 指定したハンドルのモデルをコピーとして生成する
	/// </summary>
	/// <param name="modelH">モデルハンドル</param>
	Model(int modelH);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Model();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="animSpeed">アニメーション速度(基本は1)</param>
	void Update(int animSpeed = 1);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(VECTOR pos);

	/// <summary>
	/// スケール設定
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(VECTOR scale);

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRot(VECTOR rot);

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	VECTOR GetPos()const { return m_pos; }

	/// <summary>
	/// モデルハンドルの取得
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle() const { return m_modelH; }

	/// <summary>
	/// 当たり判定用フレームインデックスの取得
	/// </summary>
	/// <returns>当たり判定で使用するフレームのインデックス</returns>
	int GetColFrameIndex()const { return m_colFrameIndex; }

public:		// 関数(アニメーション制御)
	/// <summary>
	/// アニメーションを設定する
	/// (ブレンド率を考慮せずに切り替える)
	/// </summary>
	/// <param name="animNo">変更するアニメーション番号</param>
	/// <param name="isLoop">アニメーションがループするか</param>
	/// <param name="isForceChange">既に指定したアニメーション番号と同じアニメーションが再生されていても変更をするか</param>
	void SetAnim(int animNo, bool isLoop, bool isForceChange);

	/// <summary>
	/// アニメーションを変化させる
	/// (指定したフレームかけてアニメーションを切り替える)
	/// </summary>
	/// <param name="animNo">変更するアニメーション番号</param>
	/// <param name="changeFrameNum">アニメーションを変化させるフレーム数</param>
	/// <param name="isLoop">アニメーションがループするか</param>
	/// <param name="isForceChange">既に指定したアニメーション番号と同じアニメーションが再生されていても変更をするか</param>
	void ChangeAnim(int animNo, bool isLoop, bool isForceChange, int changeFrameNum);

	/// <summary>
	/// 現在のアニメーションが終了したかどうかの取得
	/// (Loopするアニメーションの場合はfalseを返す)
	/// </summary>
	/// <returns>アニメーションが終了したかどうか</returns>
	bool IsAnimEnd();

private:	// 構造体
	struct AnimData
	{
		int animNo;			// アニメーション番号
		int attachNo;		// アニメーションアタッチ番号
		float totalTime;	// アニメーションの総再生時間
		bool isLoop;		// アニメーションがループするかどうか
	};

private:	// 関数
	/// <summary>
	/// アニメーション情報のクリア
	/// </summary>
	/// <param name="anim">アニメーション情報</param>
	void ClearAnimData(AnimData& anim);

	/// <summary>
	/// アニメーション更新
	/// </summary>
	/// <param name="anim">アニメーション情報</param>
	/// <param name="animSpeed">アニメーション速度</param>
	void UpdateAnim(AnimData anim, float animSpeed = 1.0f);

	/// <summary>
	/// アニメーションのブレンド率を設定する
	/// </summary>
	void UpdateAnimBlendRate();

private:	// 変数
	int m_modelH;					// モデルハンドル
	int m_animFrame;				// アニメーションフレーム
	int m_animChangeFrame;			// 現在の切り替えフレーム数
	int m_animChangeFrameTotal;		// 切り替えにかける総フレーム数
	int m_animChangeSpeed;			// アニメーションの変更速度
	int m_colFrameIndex;			// 当たり判定として使用するフレームのインデックス
	bool m_isUseCol;				// 当たり判定の情報を使用するかどうか
	bool m_isUpdateCol;				// 当たり判定の情報をマイフレーム更新するかどうか
	VECTOR m_pos;					// 座標
	AnimData m_prevAnim;			// 変更前アニメーション
	AnimData m_nextAnim;			// 変更後アニメーション
};

