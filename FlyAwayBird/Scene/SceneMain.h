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
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:	// 関数
	void ItemInit();

	void StartUpdate(Input& input);
	void PlayUpdate(Input& input);
	void ClearUpdate(Input& input);

	void TimeDraw();
	void ItemNumDraw();

private:	// 変数
	int m_startHandle;	// スタート時の画像ハンドル
	int m_clearHandle;	// クリア時の画像ハンドル
	int m_backHandle;	// 背景のハンドル
	int m_timeFrontFontHandle;		// 秒数表示用のフォントのハンドル(前)
	int m_timeBackFontHandle;	// 秒数表示用のフォントのハンドル(後)
	int m_itemFrontFontHandle;	// アイテム表示用のフォントのハンドル(前)
	int m_itemBackFontHandle;	// アイテム表示用のフォントのハンドル(後)
	int m_timeFrame;	// 経過フレーム
	int m_time;			// 経過秒数
	int m_clearTime;	// クリア時の秒数
	int m_itemNum;		// とったアイテム数
	int m_fadeAlpha;	// フェードイン・アウトの濃さ
	bool m_isStart;		// スタート画面かどうか
	bool m_isPlay;		// プレイ画面かどうか
	bool m_isClear;		// ゴール画面かどうか

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
	/*秒数の表示位置*/
	static constexpr int kTimePosX = 600;			// 秒数のX位置
	static constexpr int kTimePosY = 40;			// 秒数のY位置
	static constexpr int kItemPosX = 550;			// アイテムのX位置
	static constexpr int kItemPosY = 150;			// アイテムのY位置
};