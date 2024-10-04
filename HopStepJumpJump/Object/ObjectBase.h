#pragma once
#include "DxLib.h"
#include "../Util/CharacterData.h"

#include <array>
#include <memory>

class Model;
class ObjectManager;
class ToonShader;
class ShadowMapShader;

namespace ColInfo
{
	constexpr int kMaxColHitPolyNum = 2000;		// 最大当たり判定ポリゴン数
	constexpr int kMaxColHitTryNum = 16;		// 壁押し出し処理の最大試行回数
	constexpr float kColHitSlideLength = 1.0f;	// 壁押し出し時にスライドさせる距離
}

class ObjectBase
{
public:	// 列挙体

	/// <summary>
	/// 当たり判定の種類
	/// </summary>
	enum class ColType
	{
		None,		// 無し
		Player,		// プレイヤー
		Enemy,		// エネミー
		Field,		// フィールド
		Item,		// アイテム
	};

public:	// 関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ObjectBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="pToonShader">トゥーンシェーダ</param>
	virtual void Draw(std::shared_ptr<ToonShader> pToonShader) = 0;

	/// <summary>
	/// 影の描画
	/// </summary>
	/// <param name="pShadoeMapShader">シャドウマップシェーダポインタ</param>
	virtual void ShadowMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader);

	/// <summary>
	/// 2Dの描画
	/// </summary>
	virtual void Draw2D() {/*処理無し*/ };

	/// <summary>
	/// ステージクリア時
	/// </summary>
	virtual void StageClear() {/*処理無し*/ };

	/// <summary>
	///	ステージ終了時
	/// </summary>
	virtual void StageEnd() {/*処理無し*/ };

	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void OnAttack() {/*処理無し*/ };

	/// <summary>
	/// メインポインタの設定
	/// </summary>
	/// <param name="objectManager">オブジェクトマネージャーポインタ</param>
	void SetMain(ObjectManager* objectManager) { m_pObjectManager = objectManager; }

	/// <summary>
	/// モデルハンドルの設定
	/// </summary>
	/// <param name="handle">モデルハンドル</param>
	void SetModelHandle(int handle) { m_modelH = handle; }

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// モデルクラスの取得
	/// </summary>
	/// <returns>モデルクラス</returns>
	const std::shared_ptr<Model> GetModel() const { return m_pModel;}

	/// <summary>
	/// キャラクター情報の取得
	/// </summary>
	/// <returns>キャラクター情報</returns>
	const CharacterData::CharacterInfo GetInfo() const { return m_info; }

	/// <summary>
	/// 自信の当たり判定の情報
	/// </summary>
	/// <returns>当たり判定情報</returns>
	virtual ColType GetColType() const { return ColType::None; }

	/// <summary>
	/// ステージ終了時の処理が終わっているか
	/// </summary>
	/// <returns>ステージ終了時の処理が終わっているか</returns>
	bool IsStageEnd()const { return m_isStageEnd; }

	/// <summary>
	/// ダメージを受けているか
	/// </summary>
	/// <returns>ダメージを受けているか</returns>
	bool IsDamage() const { return m_isDamage; }

	/// <summary>
	/// 当たり判定を考慮しての移動更新
	/// </summary>
	/// <param name="pField">フィールドポインタ</param>
	void MoveCollFieldUpdate(ObjectBase* pField);

protected:	// 変数
	int m_modelH;								// モデルハンドル
	float m_objSize;							// オブジェクトサイズ
	float m_angle;								// キャラクターの向き
	float m_moveSpeed;							// 移動スピード
	bool m_isDamage;							// 攻撃を受けたか
	bool m_isStageEnd;							// ステージ終了時の処理が終わってるかどうか
	std::shared_ptr<Model> m_pModel;			// モデルクラスポインタ
	ObjectManager* m_pObjectManager;			// オブジェクトマネージャーポインタ
	CharacterData::CharacterInfo m_info;		// キャラクター情報	

private:	// 関数
	/// <summary>
	/// チェックしたポリゴンが壁ポリゴンか床ポリゴンか
	/// 判断して保存する
	/// </summary>
	void CheckWallAndFloor();

	/// <summary>
	/// 壁ポリゴンとの当たり判定をチェックして移動させる
	/// </summary>
	void FixPosWithWall();

	void FixPosWithWallInternal();

	/// <summary>
	/// 床ポリゴンとの当たり判定をチェックして移動させる
	/// </summary>
	void FixPosWithFloor();

private:	// 変数
	int m_wallNum;			// 壁と判断されたポリゴン数
	int m_floorNum;			// 床と判断されたポリゴン数
	bool m_isMove;			// 移動したかどうか
	bool m_isHit;			// ポリゴンに当たったかどうか
	VECTOR m_oldPos;		// 移動前の座標
	VECTOR m_nextPos;		// 移動後の座標

	MV1_COLL_RESULT_POLY_DIM m_hitDim{};								// 当たり判定結果構造体
	MV1_COLL_RESULT_POLY* m_pWallPoly[ColInfo::kMaxColHitPolyNum]{};	// 壁ポリゴンと判断されたポリゴンのアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_pFloorPoly[ColInfo::kMaxColHitPolyNum]{};	// 壁ポリゴンと判断されたポリゴンのアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_pPoly;										// ポリゴンの構造体にアクセスするために使用するポインタ
	HITRESULT_LINE m_lineRes{};											// 線分とポリゴンとの当たり判定の結果を代入する構造体
};

