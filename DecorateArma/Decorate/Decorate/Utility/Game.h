#pragma once
#include "DxLib.h"

/// <summary>
/// �Q�[���S�̂Ŏg���萔���`���邵�Ă���namespace
/// </summary>
namespace Game
{
	const char* const kTitleText = "Temporary";			// �E�B���h�E��

#ifdef _DEBUG
	constexpr bool kWindowMode = true;					// �E�B���h�E���[�h�ɂ���
#else
	constexpr bool kWindowMode = false;					// �t���X�N���[��
#endif // _DEBUG

	constexpr int kScreenWidth = 1920;					// ��ʉ��T�C�Y
	constexpr int kScreenHeight = 1080;					// ��ʏc�T�C�Y
	constexpr int kClorDepth = 32;						// �J���[�r�b�g��

	constexpr float kStandardTimePer1Frame = 16666.6f;				// 1�t���[��������̕W������(����60fps)
	constexpr float kFov = 60.0f * DX_PI_F / 180.0f;				// �J�����̎���p
	constexpr float kAspect = static_cast<float>(kScreenWidth) / static_cast<float>(kScreenHeight);	// �A�X�y�N�g��
	
	constexpr VECTOR kLightPos = { -1000.0f,2000.0f,-1000.0f };		// ���C�g���W
	constexpr VECTOR kLightDirection = { -1.0f,-1.0f,-1.0f };		// ���C�g����

	/*�X�e�[�W�̎��*/
	enum class StageKind
	{
		StageTest,		// �e�X�g�p�X�e�[�W
		Stage1,		// �X�e�[�W1

		StageNum,	// �X�e�[�W��
	};
}