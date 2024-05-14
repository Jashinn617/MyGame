#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class RecoveredItem;

/// <summary>
/// メインシーンクラス
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="handle">ハンドル</param>
	virtual void Init(HandleManager& handle);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	/// <returns>シーンポインタ</returns>
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
	virtual void Draw(HandleManager& handle);
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End();

private:	// 関数
	/// <summary>
	/// アイテムの初期化
	/// </summary>
	/// <param name="handle">ハンドル</param>
	void ItemInit(HandleManager& handle);

	/// <summary>
	/// スタート画面の更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	void StartUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// カウントダウンの更新
	/// </summary>
	/// /// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	void CountdownUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// プレイ画面の更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	void PlayUpdate(Input& input, HandleManager& handle);
	/// <summary>
	/// クリア画面の更新
	/// </summary>
	/// <param name="input">入力</param>
	/// <param name="handle">ハンドル</param>
	void ClearUpdate(Input& input, HandleManager& handle);

	/// <summary>
	/// スタート画面の描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
	void StartDraw(HandleManager& handle);
	/// <summary>
	/// プレイ画面の描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
	void PlayDraw(HandleManager& handle);
	/// <summary>
	/// クリア画面の描画
	/// </summary>
	/// <param name="handle">ハンドル</param>
	void ClearDraw(HandleManager& handle);

private:	// 変数
	int m_shadowMapHandle;	// シャドウマップのハンドル
	int m_timeFrame;		// 経過フレーム
	int m_time;				// 経過秒数
	int m_clearTime;		// クリア時の秒数
	int m_itemNum;			// とったアイテム数
	int m_fadeAlpha;		// フェードイン・アウトの濃さ
	int m_countdownFrame;	// カウントダウンの経過フレーム
	bool m_isStart;			// スタート画面かどうか
	bool m_isCountdown;		// カウントダウン中かどうか
	bool m_isPlay;			// プレイ画面かどうか
	bool m_isClear;			// ゴール画面かどうか
	bool m_isSe;			// SEがなったかどうか

	/*ポインタ*/
	shared_ptr<Player> m_pPlayer;					// プレイヤーのポインタ
	shared_ptr<Camera> m_pCamera;					// カメラのポインタ
	vector<shared_ptr<RecoveredItem>> m_pItem;		// アイテムのポインタ

private:	 // 定数
	static constexpr float kWallZ = 30;				// z軸の壁
	static constexpr float kWallX = 50;				// x軸の壁
	static constexpr int kItemNum = 20;				// アイテムの数
	static constexpr int kFadeSpeed = 2;			// フェードのスピード
	static constexpr float kGroundModelScale = 20;	// 地面モデルのスケール
	static constexpr float kGroundPosY = -1.2f;		// 地面のY位置
	static constexpr float kCountdownTime = 3 * 60;	// カウントダウンをする秒数
	/*秒数の表示位置*/
	static constexpr int kTimePosX = 600;			// 秒数のX位置
	static constexpr int kTimePosY = 40;			// 秒数のY位置
	static constexpr int kItemPosX = 550;			// アイテムのX位置
	static constexpr int kItemPosY = 150;			// アイテムのY位置
	static constexpr int kClearTimePosX = 500;		// クリアタイムのX位置
	static constexpr int kClearTimePosY = 120;		// クリアタイムのY位置
	static constexpr int kBackFontShiftPosX = 10;	// 後ろのフォントをずらす位置
	/*クリア時のタイム*/
	static constexpr int kClearFastTime = 35;		// 速いクリア
	static constexpr int kClearSlowTime = 55;		// 遅いクリア
	/*シャドウマップ*/
	static constexpr int kShadowMapSizeX = 1024;							// シャドウマップのサイズX
	static constexpr int kShadowMapSizeY = 1024;							// シャドウマップのサイズY
	static constexpr VECTOR kShadowMapRangeMin = { -100.0f,-1.2f,-100.0f };	// シャドウマップを描画する最大範囲
	static constexpr VECTOR kShadowMapRangeMax = { 100.0f,50.0f,100.0f };	// シャドウマップを描画する最小範囲
	static constexpr VECTOR kShadowMapLightDir = { 0.01f, -0.5f, 0.0f };		// シャドウマップが想定するライトの方向
	
	static constexpr VECTOR kLightDir = { 0.0f,-0.5f,0.0f };					// ライトの方向
};