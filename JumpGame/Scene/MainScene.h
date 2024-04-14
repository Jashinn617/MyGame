#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class Player;
class Camera;
class Map;
class EnemyManager;
class Input;

/// <summary>
/// ���C���V�[��
/// </summary>
class MainScene:public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	void BackDraw();

	VECTOR m_bgPos;	// �w�i�̕\���ʒu
	int m_bgHandle;	// �w�i�摜
	int m_bgFrame;

	int m_noticeLogoHandle1;
	int m_noticeLogoHandle2;
	int m_noticeLogoHandle3;
	int m_noticeLogoHandle4;

	int m_tutorialHandle;

	int m_timeFrame;
	int m_time;

	int m_bgmHandle;
	int m_clearSeHandle;
	int m_noticeSeHandle;
	int m_missSeHandle;


	int m_timeFontHandle;
	int m_timeBackFontHandle;

	int m_blinkingNoticeFrame;	// �b���ʒm�̓_�Ńt���[��
	bool m_isNotice;	// �b���ʒm���\������Ă��邩

	struct BgSize	// �w�i�摜�̃T�C�Y
	{
		int width;
		int height;
	};

	/*�|�C���^�̎擾*/
	// �v���C���[
	shared_ptr<Player> m_pPlayer;
	// �J����
	shared_ptr<Camera> m_pCamera;
	// �}�b�v
	shared_ptr<Map> m_pMap;
	// �G�L�����N�^�[
	shared_ptr<EnemyManager> m_pEnemy;

private:	// �萔
	static constexpr float kBgScale = 0.5f;		// �w�i�摜�̃X�P�[���T�C�Y
	static constexpr float kBgSpeed = -1.0f;	// �w�i�̈ړ��X�s�[�h

	/*�w�i�̕`��ʒu*/
	static constexpr float kBgPosX = 0.0f;
	static constexpr float kBgPosY = 0.0f;
	static constexpr float kBgPosZ = 200.0f;

	static constexpr int kBgmVolume = 130;	// BGM�̉���
	static constexpr int kSeVolume = 255;	// SE�̉���

	static constexpr int kScreenWidth = 1600;	// ��ʂ̉��T�C�Y
	static constexpr int kScreenHeight = 900;	// ��ʂ̏c�T�C�Y

	static constexpr int kFadeSpeed = 3;	// �t�F�[�h�̃X�s�[�h

	static constexpr int kNoticeBlinkingSpeed = 30;	// �b���ʒm�̓_�ő��x
	static constexpr int kNoticeBlinkingFrequency = 20; // �b���ʒm�̓_�ŕp�x

	/*�b���ʒm�̕`��ʒu*/
	static constexpr float kNoticePosX = 850;	// X�ʒu
	static constexpr float kNoticePosY = 400;	// Y�ʒu
	static constexpr double kNoticeExtRate = 0.3;	// �g�嗦

	/*�b���̕\���ʒu*/
	static constexpr int kTimePosX = 750;
	static constexpr int kTimePosY = 80;

	/*�b���ʒm������Ԋu*/
	static constexpr int kTimeInterval1 = 20;
	static constexpr int kTimeInterval2 = kTimeInterval1 + 20;
	static constexpr int kTimeInterval3 = kTimeInterval2 + 20;
	static constexpr int kTimeInterval4 = kTimeInterval3 + 20;

	/*�b���ʒm��\������b��*/
	static constexpr int kNoticeDisplayTime = 3;

	static constexpr int kClearTime = 90;	// �N���A�^�C��

};

