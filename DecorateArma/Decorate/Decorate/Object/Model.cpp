#include "Model.h"

#include <cassert>

Model::Model(const char* fileName):
	m_modelH(-1),
	m_animFrame(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(0),
	m_isUseCol(false),
	m_isUpdateCol(false),
	m_pos{0.0f,0.0f,0.0f}
{
	// 非同期読み込み設定に変更する
	SetUseASyncLoadFlag(true);
	// モデルのロード
	m_modelH = MV1LoadModel(fileName);
	// モデルのロードに失敗したら止まる
	assert(m_modelH != -1);
	// 非同期読み込み設定を解除する
	SetUseASyncLoadFlag(false);	

	// アニメーション情報のクリア
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::Model(int modelH):
	m_modelH(-1),	// モデルのコピー
	m_animFrame(0),
	m_animChangeFrame(0),
	m_animChangeFrameTotal(0),
	m_animChangeSpeed(0),
	m_colFrameIndex(0),
	m_isUseCol(false),
	m_isUpdateCol(false),
	m_pos{ 0.0f,0.0f,0.0f }
{
	// 非同期読み込み設定に変更する
	SetUseASyncLoadFlag(true);
	// モデルのロード
	m_modelH = MV1DuplicateModel(modelH);
	// モデルのロードに失敗したら止まる
	assert(m_modelH != -1);
	// 非同期読み込み設定を解除する
	SetUseASyncLoadFlag(false);

	// アニメーション情報のクリア
	ClearAnimData(m_prevAnim);
	ClearAnimData(m_nextAnim);
}

Model::~Model()
{
	// 当たり判定情報を使用していた場合
	if (m_isUseCol)
	{
		// 当たり判定の情報を削除する
		MV1TerminateCollInfo(m_modelH, -1);
		// 当たり判定情報を使用しない設定にする
		m_isUseCol = false;
	}
}

void Model::Update()
{
	// アニメーションを進める
	m_animFrame++;

	// アニメーションが一周した場合
	if (m_animFrame >= m_animChangeFrameTotal)
	{
		// アニメーションの更新をする
		UpdateAnim(m_prevAnim);
		UpdateAnim(m_nextAnim);
		// フレームをリセットする
		m_animFrame = 0;
	}

	/*指定フレームかけてアニメーションを変更する*/
	// アニメーションの切り替えを進める
	m_animChangeFrame++;
	// 切り替えフレームが総フレーム数に達した場合
	if (m_animChangeFrame > m_animChangeFrameTotal)
	{
		// 切り替えフレーム数が総フレーム数を越さないようにする
		m_animChangeFrame = m_animChangeFrameTotal;
	}
	// アニメーションのブレンド率の設定
	UpdateAnimBlendRate();

	// 当たり判定データの更新
	if (m_isUseCol && m_isUpdateCol)
	{
		// コリジョン情報の構築
		MV1RefreshCollInfo(m_modelH, m_colFrameIndex);
	}
}

void Model::Draw()
{
	// モデルの描画
	MV1DrawModel(m_modelH);
}

void Model::SetPos(VECTOR pos)
{
	// 位置情報の設定
	m_pos = pos;
	MV1SetPosition(m_modelH, m_pos);
}

void Model::SetScale(VECTOR scale)
{
	// スケールの設定
	MV1SetScale(m_modelH, scale);
}

void Model::SetRot(VECTOR rot)
{
	// 回転の設定
	MV1SetRotationXYZ(m_modelH, rot);
}

void Model::SetAnim(int animNo, bool isLoop, bool isForceChange)
{
	/* 指定されたアニメーションと同じアニメーションが再生中だった場合は
	 再生をしない設定だったかつ、既に同じアニメーションが再生されていた場合は
	 何もしない*/
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// アニメーションが残っていた場合
	if (m_prevAnim.attachNo != -1)
	{
		// そのアニメーションを終了する
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	// アニメーションが残っていた場合
	if (m_nextAnim.attachNo != -1)
	{
		// そのアニメーションを終了する
		MV1DetachAnim(m_modelH, m_nextAnim.attachNo);
		ClearAnimData(m_nextAnim);
	}

	// 新しくアニメーションを設定する
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// 変更にかけるフレーム数を設定する
	m_animChangeFrameTotal = 1;
	m_animChangeFrame = 1;	
}

void Model::ChangeAnim(int animNo, int changeFrameNum, bool isLoop, bool isForceChange)
{
	/* 指定されたアニメーションと同じアニメーションが再生中だった場合は
	 再生をしない設定だったかつ、既に同じアニメーションが再生されていた場合は
	 何もしない*/
	if ((!isForceChange) && (m_nextAnim.animNo == animNo))return;

	// アニメーションが残っていた場合は終了する
	if (m_prevAnim.attachNo != -1)
	{
		MV1DetachAnim(m_modelH, m_prevAnim.attachNo);
		ClearAnimData(m_prevAnim);
	}
	// 現在再生中のアニメーションを古いものにする
	m_prevAnim = m_nextAnim;

	// 新しくアニメーションを設定する
	m_nextAnim.animNo = animNo;
	m_nextAnim.attachNo = MV1AttachAnim(m_modelH, animNo, -1, false);
	m_nextAnim.totalTime = MV1GetAttachAnimTotalTime(m_modelH, m_nextAnim.attachNo);
	m_nextAnim.isLoop = isLoop;

	// 変更にかけるフレーム数を設定する
	m_animChangeFrameTotal = changeFrameNum;
	m_animChangeFrame = 0;

	// アニメーションのブレンド率の設定
	UpdateAnimBlendRate();
}

bool Model::IsAnimEnd()
{
	// ループするアニメーションの場合はfalseで返す
	if (m_nextAnim.isLoop)return false;

	// 現在のアニメーションの再生
	float time = MV1GetAttachAnimTime(m_modelH, m_nextAnim.attachNo);

	/*現在のアニメーションの再生時間がアニメーションの総再生時間よりも
	大きかったらtrue返す*/
	if (time >= m_nextAnim.totalTime)return true;
	
	// そうでなければfalseを返す
	return false;
}

void Model::ClearAnimData(AnimData& anim)
{
	// アニメーション情報を初期化する
	anim.animNo = -1;
	anim.attachNo = -1;
	anim.totalTime = 0.0f;
	anim.isLoop = false;
}

void Model::UpdateAnim(AnimData anim, float animSpeed)
{
	// アニメーションが何も設定されていなければ何もしない
	if (anim.animNo == -1)return;

	// アニメーションの更新
	float nowFrame = MV1GetAttachAnimTime(m_modelH, anim.attachNo);
	nowFrame += animSpeed;
	// 現在のフレーム数が総再生時間よりも大きかった場合
	if (nowFrame > anim.totalTime)
	{
		// アニメーションをループさせる
		nowFrame -= anim.totalTime;
	}
	// アニメーションの再生時間の設定
	MV1SetAttachAnimTime(m_modelH, anim.attachNo, nowFrame);
}

void Model::UpdateAnimBlendRate()
{
	// アニメーション変化のフレーム数に応じたブレンド率を計算する
	float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	// ブレンド率が1以上にならないようにする
	if (rate > 1.0f)rate = 1.0f;

	/*ブレンド率の設定*/
	// rateが進むにつれ前のアニメーションのブレンド率が減っていく
	MV1SetAttachAnimBlendRate(m_modelH, m_prevAnim.attachNo, 1.0f - rate);
	MV1SetAttachAnimBlendRate(m_modelH, m_nextAnim.attachNo, rate);
}
