#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

#include "../Util/Game.h"
#include "../Util/Input.h"
#include "../Util/Pad.h"

#include "../Object/SkyDome.h"
#include "../Object/Camera.h"

namespace
{
	const char* const kTitleLogoImg = "Data/Img/Title/Logo.png";
	const char* const kPressAnyButtonImg = "Data/Img/Title/PressAnyButton.png";

	/*タイトルロゴ画像の初期座標*/
	constexpr int kStartTitleLogoPosY = -1200;
	/*タイトルロゴ画像の座標*/
	constexpr int kTitleLogoPosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kTitleLogoPosY = static_cast<int>(Game::kScreenHeight * 0.5f);	// Y
	/*プレスボタンの画像の座標*/
	constexpr int kPressAnyButtonPosX = static_cast<int>(Game::kScreenWidth * 0.5f);	// X
	constexpr int kPressAnyButtonPosY = static_cast<int>(Game::kScreenHeight * 0.5f);	// Y

	constexpr int kTitleFallSpeed = 30;	// タイトルが落ちてくる速度
}

SceneTitle::SceneTitle():
	m_H1(-1),
	m_H2(-1),
	m_TitlePosY(kStartTitleLogoPosY)
{
	/*画像のロード*/
	m_H1 = LoadGraph(kTitleLogoImg);
	m_H2 = LoadGraph(kPressAnyButtonImg);
}

SceneTitle::~SceneTitle()
{
	/*画像のデリート*/
	DeleteGraph(m_H1);
	DeleteGraph(m_H2);
}

void SceneTitle::Init()
{
}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_TitlePosY += kTitleFallSpeed;
	m_TitlePosY = min(m_TitlePosY, kTitleLogoPosY);

	// タイトルが落ちた後に何かしらのボタンが押されていたら次のシーンに遷移する
	if (CheckHitKeyAll() && m_TitlePosY >= kTitleLogoPosY)
	{
		return make_shared<SceneSelect>();
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG   

	// タイトル画像の描画
	DrawRotaGraph(kTitleLogoPosX, m_TitlePosY,
		1.0f, 0.0f,
		m_H1, true);

	// タイトルがおりきってなかった場合は表示しない
	if (m_TitlePosY < kTitleLogoPosY) return;

	DrawRotaGraph(kPressAnyButtonPosX, kPressAnyButtonPosY,
		1.0f, 0.0f,
		m_H2, true);
}

void SceneTitle::End()
{
}
