#include "DxLib.h"
#include "StageTest.h"
#include "../Player.h"

#include <cassert>

/// <summary>
/// 定数定義
/// </summary>
namespace
{
	constexpr float kDefaultSize = 800.0f;		// 周囲のポリゴン検出に使用する球の初期サイズ
	constexpr float kHitWidth = 200.0f;			// 当たり判定のカプセルの横の半径
	constexpr float kHitHeight = 700.0f;		// 当たり判定のカプセルの高さ
	constexpr float kHitSlideLength = 5.0f;		// 一度の壁の押し出し処理でスライドさせる距離
	constexpr float kModelScale = 50.0f;		// モデルのスケール
	constexpr int   kHitTryNum = 16;			// 壁の押し出し処理の最大試行回数
}

StageTest::StageTest() :
	m_modelHandle(-1),
	m_vs(-1),
	m_ps(-1),
	m_wallNum(0),
	m_floorNum(0),
	m_wall{ nullptr },
	m_floor{ nullptr }
{
	/*処理無し*/
}

StageTest::~StageTest()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void StageTest::Init()
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Ground.mv1");
	assert(m_modelHandle != -1);
	// シェーダのロード
	m_vs = LoadVertexShader("VertexShader.vso");
	assert(m_vs != -1);
	m_ps = LoadPixelShader("PixelTest.pso");
	assert(m_ps != -1);

	// モデルの大きさの設定
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));

	// モデルの位置の設定(仮)
	MV1SetPosition(m_modelHandle, VGet(0, -10, 0));

	// モデル全体のコリジョン情報のセットアップ
	MV1SetupCollInfo(m_modelHandle);
}

void StageTest::Draw()
{
	// シェーダを有効にする
	MV1SetUseOrigShader(true);
	SetUseVertexShader(m_vs);
	SetUsePixelShader(m_ps);

	// モデルの描画
	MV1DrawModel(m_modelHandle);

	// シェーダを無効にする
	MV1SetUseOrigShader(false);
}

void StageTest::End()
{
	/*処理無し*/
}

VECTOR StageTest::CheckCollision(Player& player, const VECTOR& moveVector)
{
	// 移動前のプレイヤーの座標を記憶しておく
	VECTOR oldPos = player.GetPos();
	// 移動後のプレイヤーの座標の計算
	VECTOR nextPos = VAdd(oldPos, moveVector);

	// ステージポリゴンが複数ある場合はここが繰り返しの処理になる
	{
		// プレイヤーの周囲にあるステージポリゴンを取得する
		// 移動距離を考慮した範囲を取得する
		auto hitDim = MV1CollCheck_Sphere(m_modelHandle, -1, oldPos, kDefaultSize + VSize(moveVector));

		// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断して保存する
		AnalyzeWallAndFloor(hitDim, oldPos);

		// 壁ポリゴンとの当たり判定をチェックして移動ベクトルを補正する
		nextPos = CheckHitWithWall(player, nextPos);

		// 壁ポリゴンとの当たり判定をチェックして移動ベクトルを補正する
		nextPos = CheckHitWithFloor(player, nextPos);

		// 検出したプレイヤーの周囲のポリゴン情報を解放する
		MV1CollResultPolyDimTerminate(hitDim);
	}
	return nextPos;
}

void StageTest::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
	// 壁ポリゴンと床ポリゴンの数を初期化する
	m_wallNum = 0;
	m_floorNum = 0;

	// 検出されたポリゴンの数だけ繰り返す
	for (int i = 0; i < hitDim.HitNum; i++)
	{
		// XZ平面に垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
		if (hitDim.Dim[i].Normal.y<0.000001f && hitDim.Dim[i].Normal.y>-0.000001f)
		{
			// 壁ポリゴンと判断された場合でも、プレイヤーのY座標より
			// 1.0f高いポリゴンのみに当たり判定を行う
			bool isPlayerHight0 = hitDim.Dim[i].Position[0].y > checkPosition.y + 1.0f;
			bool isPlayerHight1 = hitDim.Dim[i].Position[1].y > checkPosition.y + 1.0f;
			bool isPlayerHight2 = hitDim.Dim[i].Position[2].y > checkPosition.y + 1.0f;
			if (isPlayerHight0 || isPlayerHight1 || isPlayerHight2)
			{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加する
				if (m_wallNum < kMaxHitColl)
				{
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタの配列に保存する
					m_wall[m_wallNum] = &hitDim.Dim[i];
					m_wallNum++;
				}
			}
		}
		else	// 床として処理する
		{
			// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加する
			if (m_floorNum < kMaxHitColl)
			{
				// ポリゴンの構造体のアドレスを床ポリゴンポインタの配列に保存する
				m_floor[m_floorNum] = &hitDim.Dim[i];
				m_floorNum++;
			}
		}
	}
}

VECTOR StageTest::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
	// 修正する位置の作成
	VECTOR fixedPos = checkPosition;

	// 壁の数が0だった場合は何もしない
	if (m_wallNum == 0)return fixedPos;

	// 壁からの押し出し処理を最大数まで繰り返す
	for (int k = 0; k < kHitTryNum; k++)
	{
		bool isHitWall = false;
		for (int i = 0; i < m_wallNum; i++)
		{
			// 壁ポリゴンのアドレスを配列から取得する
			auto poly = m_wall[i];

			// プレイヤーと当たっていた場合
			if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
				kHitWidth, poly->Position[0], poly->Position[1], poly->Position[2]))
			{
				// 規定距離分プレイヤーを壁の法線方向に移動させる
				// 移動後の位置を更新する
				fixedPos = VAdd(fixedPos, VScale(poly->Normal, kHitSlideLength));

				// 移動した壁ポリゴンと接触しているかどうかを判定する
				for (int j = 0; j < m_wallNum; j++)
				{
					// 当たっていたらループを抜ける
					poly = m_wall[j];
					if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
						kHitWidth, poly->Position[0], poly->Position[1], poly->Position[2]))
					{
						isHitWall = true;
						break;
					}
				}

				// 全てのポリゴンと当らなくなった場合はここでループを終了する
				if (!isHitWall)
				{
					break;
				}
			}
		}
		// 全ての壁ポリゴンと接触しなくなったらループから抜ける
		if (!isHitWall)
		{
			break;
		}
	}

	return fixedPos;
}

VECTOR StageTest::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
{
	// 修正する位置の作成
	VECTOR fixedPos = checkPosition;

	// 床の数が0だった場合は何もしない
	if (m_floorNum == 0)return fixedPos;

	// ジャンプ中で上昇中だった場合は処理を分岐する
	if (player.GetState() == Player::State::Jump && player.GetJumpPower() > 0.0f)
	{
		// 天井に頭をぶつける処理を行う
		bool isHitRoof = false;
		// 一番低い天井の判定用の変数の初期化
		float minY = 0.0f;

		// 床ポリゴンの数だけ繰り返す
		for (int i = 0; i < m_floorNum; i++)
		{
			// 床ポリゴンのアドレスの取得
			auto poly = m_floor[i];

			// 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定する
			// 線分とポリゴンの当たり判定の結果を入れる構造体
			HITRESULT_LINE lineResult;
			lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
				poly->Position[0], poly->Position[1], poly->Position[2]);

			// 接触していなかった場合
			if (lineResult.HitFlag)
			{
				// すでにポリゴンに当たっていて、今まで検出した天井ポリゴンより高かった場合は何もしない
				if (!(isHitRoof && minY < lineResult.Position.y))
				{
					// 衝突フラグを立てる
					isHitRoof = true;

					// 接触したY座標を保存する
					minY = lineResult.Position.y;
				}
			}
		}

		// 接触したポリゴンがあった場合
		if (isHitRoof == true)
		{
			// プレイヤーのY座標を当たった座標をもとに更新する
			fixedPos.y = minY - kHitHeight;
			player.OnHitRoof();
		}
	}
	// 落下中かジャンプ中じゃないときの処理
	else
	{
		bool isHitFloor = false;
		float maxY = 0.0f;

		// 床ポリゴンの数だけ繰り返す
		for (int i = 0; i < m_floorNum; i++)
		{
			// 床ポリゴンのアドレス
			auto poly = m_floor[i];

			HITRESULT_LINE lineResult;
			if (player.GetState() == Player::State::Jump)
			{
				// ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定する
				lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
					VAdd(fixedPos, VGet(0.0f, -1.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
			}
			else
			{
				// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定
				// (傾斜で落下状態にならないためにする)
				lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
					VAdd(fixedPos, VGet(0.0f, -40.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
			}

			// 既に当たったポリゴンがあり、今まで検出した床ポリゴンよりも低いは愛は何もしない
			if (lineResult.HitFlag)
			{
				if (!(isHitFloor && maxY > lineResult.Position.y))
				{
					// 接触したY座標を保持する
					isHitFloor = true;
					maxY = lineResult.Position.y;
				}
			}
		}

		// 床ポリゴンに当たった
		if (isHitFloor)
		{
			// 接触したポリゴンで一番高いY座標をプレイヤーのY座標にする
			fixedPos.y = maxY;

			// 床に当たった時
			player.OnHitFloor();
		}
		else
		{
			// 床コリジョンに当たっていなくてジャンプ状態でなかった場合は落下状態になる
			player.OnFall();
		}
	}
	return fixedPos;
}
