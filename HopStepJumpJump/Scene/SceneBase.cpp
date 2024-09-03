#include "SceneBase.h"
#include "DxLib.h"
#include "../Util/Game.h"
#include "../Util/Ranking.h"

namespace
{
	constexpr int kFadeSpeed = 8;	// �t�F�[�h�̑��x
}

SceneBase::SceneBase():
	m_fadeColor(0xffffff),
	m_fadeBright(255),
	m_fadeSpeed(-kFadeSpeed),
	m_transition(Transition::Delete)
{
	m_pRanking = std::make_shared<Ranking>();
}

SceneBase::~SceneBase()
{
	/*��������*/
}

void SceneBase::Init()
{
	/*��������*/
}

std::shared_ptr<SceneBase> SceneBase::Update(Input& input)
{
	return shared_from_this();
}

void SceneBase::Draw()
{
	/*��������*/
}

void SceneBase::End()
{
	/*��������*/
}

void SceneBase::UpdateFade()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		if (m_fadeSpeed > 0)
		{
			m_fadeSpeed = 0;
		}
	}
	if (m_fadeBright <= 0)
	{
		m_fadeBright = 0;
		if (m_fadeSpeed < 0)
		{
			m_fadeSpeed = 0;
		}
	}
}

void SceneBase::DrawFade()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneBase::SkipFadeIn()
{
	m_fadeBright = 0;
	m_fadeSpeed = kFadeSpeed;
}

void SceneBase::SkipFadeOut()
{
	m_fadeBright = 255;
	m_fadeSpeed = -kFadeSpeed;
}

bool SceneBase::IsFadeIn() const
{
	return m_fadeSpeed < 0;
}

bool SceneBase::IsFadeOut() const
{
	return m_fadeSpeed > 0;
}

void SceneBase::StartFadeOut()
{
	m_fadeSpeed = kFadeSpeed;
}
