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

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <returns>���݂̃V�[��</returns>
	virtual shared_ptr<SceneBase> Update(Input& input);
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �V�[���I�����̏���
	/// </summary>
	virtual void End();

private:	// �֐�
	/// <summary>
	/// �b���̌o�߂�m�点��SE��炷
	/// </summary>
	void NoticeSeRing();
	/// <summary>
	/// �b���̌o�߂�m�点��e�L�X�g�̓_�ŏ���
	/// </summary>
	void NoticeBlinking();
	/// <summary>
	/// �b���̕`��
	/// </summary>
	void TimeDraw();
	/// <summary>
	/// �b���̌o�߂�m�点��e�L�X�g�̕`��
	/// </summary>
	void NoticeDraw();
	/// <summary>
	/// �w�i�̕`��
	/// </summary>
	void BackDraw();

private:	// �ϐ�

	VECTOR m_bgPos;				// �w�i�̕\���ʒu
	int m_bgHandle;				// �w�i�摜

	int m_noticeLogoHandle1;	// 20�b�̌o�߂�m�点��e�L�X�g
	int m_noticeLogoHandle2;	// 40�b�̌o�߂�m�点��e�L�X�g
	int m_noticeLogoHandle3;	// 60�b�̌o�߂�m�点��e�L�X�g
	int m_noticeLogoHandle4;	// 80�b�̌o�߂�m�点��e�L�X�g
	int m_tutorialHandle;		// �`���[�g���A���̃e�L�X�g

	int m_bgmHandle;			// BGM�̃n���h��
	int m_clearSeHandle;		// �N���A����SE�̃n���h��
	int m_noticeSeHandle;		// �b���o�߂�m�点��SE�̃n���h��
	int m_missSeHandle;			// �~�X����������SE�̃n���h��

	int m_timeFontHandle;		// �b���\���p�̃t�H���g�̃n���h��(�O)
	int m_timeBackFontHandle;	// �b���\���p�̃t�H���g�̃n���h��(��)
	
	int m_timeFrame;			// �o�߃t���[��
	int m_time;					// �o�ߕb��

	int m_blinkingNoticeFrame;	// �b���ʒm�̓_�Ńt���[��
	bool m_isNotice;			// �b���ʒm���\������Ă��邩

	struct BgSize				// �w�i�摜�̃T�C�Y
	{
		int width;	// ��
		int height;	// �c
	};

	/*�|�C���^�̎擾*/
	shared_ptr<Player> m_pPlayer;		// �v���C���[	
	shared_ptr<Camera> m_pCamera;		// �J����
	shared_ptr<Map> m_pMap;				// �}�b�v	
	shared_ptr<EnemyManager> m_pEnemy;	// �G�L�����N�^�[

private:	// �萔
	static constexpr float kBgScale = 0.5f;		// �w�i�摜�̃X�P�[���T�C�Y
	static constexpr float kBgSpeed = -1.0f;	// �w�i�̈ړ��X�s�[�h

	/*�w�i�̕`��ʒu*/
	static constexpr float kBgPosX = 0.0f;		// X�ʒu
	static constexpr float kBgPosY = 0.0f;		// Y�ʒu
	static constexpr float kBgPosZ = 200.0f;	// Z�ʒu

	static constexpr int kBgmVolume = 130;		// BGM�̉���
	static constexpr int kSeVolume = 255;		// SE�̉���

	static constexpr int kScreenWidth = 1600;	// ��ʂ̉��T�C�Y
	static constexpr int kScreenHeight = 900;	// ��ʂ̏c�T�C�Y

	static constexpr int kFadeSpeed = 3;		// �t�F�[�h�̃X�s�[�h

	static constexpr int kNoticeBlinkingSpeed = 30;		// �b���ʒm�̓_�ő��x
	static constexpr int kNoticeBlinkingFrequency = 20; // �b���ʒm�̓_�ŕp�x

	/*�b���ʒm�̕`��ʒu*/
	static constexpr float kNoticePosX = 850;		// X�ʒu
	static constexpr float kNoticePosY = 400;		// Y�ʒu
	static constexpr double kNoticeExtRate = 0.3;	// �g�嗦

	/*�b���̕\���ʒu*/
	static constexpr int kTimePosX = 750;			// X�ʒu
	static constexpr int kTimePosY = 80;			// Y�ʒu

	/*�b���ʒm������Ԋu*/
	static constexpr int kTimeInterval1 = 20;
	static constexpr int kTimeInterval2 = kTimeInterval1 + 20;
	static constexpr int kTimeInterval3 = kTimeInterval2 + 20;
	static constexpr int kTimeInterval4 = kTimeInterval3 + 20;

	static constexpr int kNoticeDisplayTime = 3;	//�b���ʒm��\������b��
	static constexpr int kClearTime = 90;			// �N���A�^�C��
};

