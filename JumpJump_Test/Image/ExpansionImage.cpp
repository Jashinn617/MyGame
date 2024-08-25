#include "ExpansionImage.h"

namespace
{
	constexpr int kFadeSpeed = 6;
	constexpr double kChangeSizeSpeed = 0.02f;
	constexpr double kMaxChangeSizeSpeed = 0.1f;
	constexpr double kInitSize = 1.4f;	// �����摜�T�C�Y
	constexpr double kMinSize = 0.8f;	// �ŏ��摜�T�C�Y
	constexpr double kNormalSize = 1.0f;	// �ʏ�摜�T�C�Y
}

ExpansionImage::ExpansionImage():
	m_alpha(0),
	m_size(kInitSize),
	m_changeSizeSpeed(0.0f),
	m_isExpanding(false),
	m_isChangeEnd(false),
	m_updateFunc(&ExpansionImage::FadeInUpdate)
{
}

ExpansionImage::~ExpansionImage()
{
	// �摜�̃f���[�g
	DeleteGraph(m_H);
}

void ExpansionImage::Update()
{
	// ��Ԃɍ��킹�čX�V�������s��
	(this->*m_updateFunc)();
}

void ExpansionImage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawRotaGraph(static_cast<int>(m_center.x), 
		static_cast<int>(m_center.y), 
		m_size,0.0f,m_H, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ExpansionImage::FadeInUpdate()
{
	m_alpha = min(m_alpha + kFadeSpeed, 255);

	//�g�咆�ł͂Ȃ��ꍇ
	if (!m_isExpanding)
	{
		m_changeSizeSpeed = max(m_changeSizeSpeed - kChangeSizeSpeed, -kMaxChangeSizeSpeed);
		m_size = max(m_size + m_changeSizeSpeed, kMinSize);
		if (m_size <= kMinSize)
		{
			m_isExpanding = true;
		}
	}
	//�g�咆�̏ꍇ
	else if (m_isExpanding)
	{
		m_changeSizeSpeed = min(m_changeSizeSpeed + kChangeSizeSpeed, kMaxChangeSizeSpeed);
		m_size = min(m_size + m_changeSizeSpeed, kNormalSize);
	}

	//�g�咆���A�����x��255���傫�����A�ʏ�T�C�Y�ɂȂ����ꍇ
	if (m_size >= kNormalSize && m_alpha >= 255 && m_isExpanding)
	{
		m_updateFunc = &ExpansionImage::NormalUpdate;
		m_isChangeEnd = true;
	}
}

void ExpansionImage::NormalUpdate()
{
}
