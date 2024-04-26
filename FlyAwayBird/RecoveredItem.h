#pragma once
#include <memory>

class WorldSprite;

using namespace std;

/// <summary>
/// 収集用アイテムクラス
/// </summary>
class RecoveredItem
{
public:
	RecoveredItem();
	~RecoveredItem();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:	// 変数
	VECTOR m_pos;	// 位置
	int m_handle;	// 画像のハンドル
	/*画像のサイズ*/
	int m_w;	// 横
	int m_h;	// 縦

	float m_sinCount;	// 移動の際のSinカウント
	float m_sinPosY;	// 位置の計算に使うSin

	shared_ptr<WorldSprite> m_pSprite;	// スプライト

private:	// 定数
	int kSize = 2;	// 画像の全体的なサイズ

	static constexpr float kRadius = 0.8f;	// 半径
	static constexpr float kUpPosY = 2.0f;	// 上にいるときの位置
	static constexpr float kDownPosY = 1.0f;	// 下にいるときの位置

	static constexpr float kSinSpeed = 0.05f;	// 移動スピード
	static constexpr float kMoveSwing = 0.01f;	// 移動幅
};

