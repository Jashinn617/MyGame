#pragma once
#include "DxLib.h"

/// <summary>
/// �Q�[���S�̂Ŏg�p����萔���`����namespace
/// </summary>
namespace Game
{
	constexpr int kScreenWidth = 1920;	// ��ʉ��T�C�Y
	constexpr int kScreenHeight = 1080;	// ��ʏc�T�C�Y

	constexpr int kColorDepth = 32;		// �J���[�r�b�g��
	
	constexpr VECTOR kLightPos = { -1000.0f,2000.0f,-1000.0f };		// ���C�g�̈ʒu
	constexpr VECTOR kLightDir = { -1.0f, 2.0f, -1.0f };			// ���C�g�̌���

	// �X�e�[�W��
	enum class Stage
	{
		Stage1,
		Stage2,
		Trutorial,
		StageSelect,
		StageName,
	};
}
