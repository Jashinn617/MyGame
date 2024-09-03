#pragma once
#include "DxLib.h"

/// <summary>
/// �Q�[���S�̂Ŏg�p����萔���`����namespace
/// </summary>
namespace Game
{
	const char* const kTitleText = "HOP!STEP!JUMP��JUMP!!";		// �E�B���h�E��

#ifdef _DEBUG
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif // _DEBUG

	/*�E�B���h�E�T�C�Y*/
	constexpr int kScreenWidth = 1920;	// ��ʉ��T�C�Y
	constexpr int kScreenHeight = 1080;	// ��ʏc�T�C�Y

	constexpr int kColorDepth = 32;		// �J���[�r�b�g��
	
	constexpr VECTOR kLightPos = { -1000.0f,2000.0f,-1000.0f };		// ���C�g�̈ʒu
	constexpr VECTOR kLightDir = { -1.0f, -1.0f, -1.0f };			// ���C�g�̌���

	constexpr float kFov = 60.0f * DX_PI_F / 180.0f;			// �J�����̎���p
	constexpr float kAspect = static_cast<float>(kScreenWidth) / static_cast<float>(kScreenHeight);	// �A�X�y�N�g��


	// �X�e�[�W��
	enum class Stage
	{
		Test,
		Stage1,
		Stage2,
		Tutorial,
		StageNum,
	};
}
