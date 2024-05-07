#pragma once
#include <memory>

class WorldSprite;
class Player;

using namespace std;

/// <summary>
/// 収集用アイテムクラス
/// </summary>
class RecoveredItem
{
public:
	RecoveredItem(shared_ptr<Player> pPlayer);
	~RecoveredItem();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(float x, float z);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	
	void CollisionToPlayer(VECTOR pVec, float pRad);

	/// <summary>
	/// 存在しているかどうか
	/// </summary>
	/// <returns>存在フラグ</returns>
	bool IsExist() { return m_isExist; }

private:	// 変数
	VECTOR m_pos;	// 位置
	int m_modelHandle;	// モデルハンドル
	int m_chatchSeHandle;	// アイテム取得時のSE
	/*画像のサイズ*/
	int m_w;	// 横
	int m_h;	// 縦

	bool m_isExist;	// 存在フラグ

	float m_sinCount;	// 移動の際のSinカウント
	float m_sinPosY;	// 位置の計算に使うSin

	shared_ptr<Player> m_pPlayer;

private:	// 定数
	static constexpr float kSize = 2;	// 画像の全体的なサイズ

	static constexpr float kRadius = 0.8f;	// 半径
	static constexpr float kUpPosY = 2.0f;	// 上にいるときの位置
	static constexpr float kDownPosY = 1.0f;	// 下にいるときの位置
	static constexpr float kScale = 1.5f;			// 拡大率

	static constexpr float kSinSpeed = 0.05f;	// 移動スピード
	static constexpr float kMoveSwing = 0.01f;	// 移動幅
	static constexpr int kSeVolume = 130;		// SEの音量
};

