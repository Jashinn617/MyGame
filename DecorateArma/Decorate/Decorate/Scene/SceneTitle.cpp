#include "SceneTitle.h"

#include "SceneSelect.h"

#include "../Utility/Game.h"
#include "../Utility/Pad.h"

#include <string>
#include <cassert>

namespace
{
    const std::string kTitlePath = "Data/Image/Title/";               // 画像ファイルパス
    const std::string kLogoPath = kTitlePath + "TitleLogo.png";      // タイトルロゴ
    const std::string kPressPath = kTitlePath + "PressButton.png";   // プレスボタンロゴ

    constexpr int kLogoPosX = Game::kScreenWidth * 0.11f;           // ロゴX座標
    constexpr int kLogoPosY = Game::kScreenHeight * 0.2f;           // ロゴY座標
    constexpr int kPressPosX = Game::kScreenWidth * 0.22f;          // プレスX座標
    constexpr int kPressPosY = Game::kScreenHeight * 0.6f;          // プレスY座標
}

SceneTitle::SceneTitle():
    m_titleLogoH(-1)
{
    /*画像ロード*/
    m_titleLogoH = LoadGraph(kLogoPath.c_str());
    // ロードに失敗したら止める
    assert(m_titleLogoH != -1);
    m_pressTextH = LoadGraph(kPressPath.c_str());
    assert(m_pressTextH);
}

SceneTitle::~SceneTitle()
{
    /*画像デリート*/
    DeleteGraph(m_titleLogoH);
    DeleteGraph(m_pressTextH);
}

void SceneTitle::Init()
{
    /*処理無し*/
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
    // Aボタンが押されたらセレクト画面に遷移する
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        return std::make_shared<SceneSelect>();
    }

    return shared_from_this();
}

void SceneTitle::Draw()
{

    // ロゴ描画
    DrawGraph(kLogoPosX, kLogoPosY, m_titleLogoH, true);

    // プレスボタン描画
    DrawGraph(kPressPosX, kPressPosY, m_pressTextH, true);

#ifdef _DEBUG
    DrawFormatString(0, 0, 0xffffff, "Title");
#endif // _DEBUG
}

void SceneTitle::End()
{
    /*処理無し*/
}