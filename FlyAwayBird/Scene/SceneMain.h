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

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input, HandleManager& handle);
	virtual void Draw(HandleManager& handle);
	virtual void End();

private:	// 関数
	void ItemInit();

	void StartUpdate(Input& input, HandleManager& handle);
	void PlayUpdate(Input& input, HandleManager& handle);
	void ClearUpdate(Input& input, HandleManager& handle);

	void StartDraw(HandleManager& handle);
	void PlayDraw(HandleManager& handle);
	void ClearDraw(HandleManager& handle);

	void TimeDraw(HandleManager& handle);
	void ItemNumDraw(HandleManager& handle);

private:	// 変数
	int m_timeFrame;	// 経過フレーム
	int m_time;			// 経過秒数
	int m_clearTime;	// クリア時の秒数
	int m_itemNum;		// とったアイテム数
	int m_fadeAlpha;	// フェードイン・アウトの濃さ
	bool m_isStart;		// スタート画面かどうか
	bool m_isPlay;		// プレイ画面かどうか
	bool m_isClear;		// ゴール画面かどうか
	bool m_isSe;		// SEがなったかどうか

	/*ポインタ*/
	shared_ptr<Player> m_pPlayer;
	shared_ptr<Camera> m_pCamera;
	//shared_ptr<RecoveredItem> m_pItem;
	vector<shared_ptr<RecoveredItem>> m_pItem;

private:	 // 定数
	static constexpr float kWallZ = 30;				// z軸の壁
	static constexpr float kWallX = 50;				// x軸の壁
	static constexpr int kItemNum = 20;				// アイテムの数
	static constexpr int kBgmVolume = 130;			// BGMの音量
	static constexpr int kSeVolume = 255;			// SEの音量
	static constexpr int kFadeSpeed = 4;			// フェードのスピード
	static constexpr float kGroundModelScale = 20;	// 地面モデルのスケール
	static constexpr float kGroundPosY = -1.2;		// 地面のY位置
	/*秒数の表示位置*/
	static constexpr int kTimePosX = 600;			// 秒数のX位置
	static constexpr int kTimePosY = 40;			// 秒数のY位置
	static constexpr int kItemPosX = 550;			// アイテムのX位置
	static constexpr int kItemPosY = 150;			// アイテムのY位置
	static constexpr int kClearTimePosX = 500;		// クリアタイムのX位置
	static constexpr int kClearTimePosY = 120;		// クリアタイムのY位置
	static constexpr int kBackFontShiftPosX = 10;		// 後ろのフォントをずらす位置
	/*クリア時のタイム*/
	static constexpr int kClearFastTime = 30;
	static constexpr int kClearSlowTime = 50;
};